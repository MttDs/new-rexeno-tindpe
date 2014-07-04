#include "session.hh"
#include "parser.hh"
#include "trial.hh"
#include "setup.hh"

#include "driver.hh"
#include "order_parser.hh"

using namespace configuration;

Session* Session::_instance = NULL;

/** 
 * Constructor :
 * Inits all the fields automatically
 * only the _trials field will depend on
 * what information is in the SessionInfo parameter
 * 
 * @param s 
 */
Session::Session(configuration::SessionInfo& s,
                 Order& o)
  : _trialsOrder(o.getOrder())
{

  Trial* t = NULL;
  vector<TrialInfo>::iterator it;

  for (it = s.trials.begin(); it != s.trials.end(); ++it)
    {
      t = new Trial(*it);
      _trialsDefinitions.push_back(t);
    }

  _currentTrial = _trialsOrder.begin();

  beforeTrial = NULL;
  afterTrial = NULL;
  _inputData.resize(8);

  recorder = new Recorder(s.save, s.traceLevel);

  recorder->AddFile("results.txt");
  recorder->AddFile("protocole.txt");
  recorder->AddFile("events.txt");
  recorder->AddFile("X.txt");
  recorder->AddFile("id_trials.txt");
  recorder->AddFile("square_targets.txt");
  recorder->AddFile("logger.txt");
  recorder->AddFile("general.txt");
  
  _offsetVsync = -1;
  _initialized = false;
  _nbFrame4init = 120;
  _nbInitFrames = 0;
  
  _nbBlock = s.block;
  _subjectName = s.name;

  _lP[0] = 0.0f; _lP[1] = 1.0f; _lP[2] = 0.4f;  _lP[3] = 0.0f; 
  _lA[0] = 0.5f; _lA[1] = 0.5f; _lA[2] = 0.5f;  _lA[3] = 2.0f; 
  _lD[0] = 1.0f ;_lD[1] = 1.0f; _lD[2] = 1.0f;  _lD[3] = 1.0f;
  _RGB[0] = 0.0f; _RGB[1] = 0.51; _RGB[2] = 0.73;

  _initShape = false;

#ifdef DEBUG
  __debug_FrameNumber = 0;
#endif

#ifdef XENO
  _driver = new XenoDriver();
#else
  _driver = new DummyDriver();
#endif

  recorder->Save(s.name, "general.txt");
  recorder->Save(s.traceLevel, "general.txt");

}

/** 
 * Destructor : cleans everything up
 */
Session::~Session()
{
  
  vector<Trial*>::iterator it;
  for (it = _trialsDefinitions.begin(); it != _trialsDefinitions.end(); ++it)
    {
      delete (*it);
    }

  delete recorder;
  recorder = NULL;
  delete setup;
  setup = NULL;
  delete _driver;
  _driver = NULL;
  
}

/** 
 * function set as the main GLUT callback
 * 
 */
void
displayRexeno()
{
  Session* s = Session::getInstance();
  s->displayHeader();
}
/**
 * Opengl's keyboard/mouse processing callback
 *
 * @param key : id of a keyboard key that was pressed
 * @param x : horizontal position of the mouse
 * @param y : vertical position of the mouse
 */
void 
keyPressed(unsigned char key, int x, int y)
{
  Setup::keys[key] = true;
  Setup::key = key;
  if (key == 27)
    {
      glutLeaveGameMode();
      glutLeaveMainLoop();
    }
}

void 
keyUp(unsigned char key, int x, int y)
{
  Setup::keys[key] = false;
}


/**
 * Reshape the window's size
 */
void
reshape(int width, int height)
{
  if (height==0){
    height=1;
  }
  (Session::getInstance()->setup)->setScreenWidth(width);
  (Session::getInstance()->setup)->setScreenHeight(height);
  (Session::getInstance()->setup)->prepareRatio();
}

void 
Session::initShape()
{

  vector<Trial*>::iterator itTrial;
  vector<Adapt*>::iterator itAdapt;
  Shapes::iterator itShape;

  Trial* t= NULL;
  Shape* s = NULL;
  Adapt* a = NULL;

  vector<Adapt*> adapts;

  recorder->Save(lexical_cast<string>(getSubjectName()) 
		 + " " + 
		 lexical_cast<string>(getNbBlock()), "protocole.txt");

  for (itTrial = _trialsDefinitions.begin(); itTrial != _trialsDefinitions.end(); ++itTrial)
    {

      t = (*itTrial);	   
      recorder->Save(t->toString(), "protocole.txt");

      for (itShape = t->shapes()->begin(); itShape != t->shapes()->end(); ++itShape)
	{
	  s = (*itShape);

	  recorder->Save(s->toString() ,"protocole.txt");

	  adapts = s->getAdapts();

	  for (itAdapt = adapts.begin(); itAdapt != adapts.end(); ++itAdapt)
	    {
	      a = (*itAdapt);
	      recorder->Save(a->toString() ,"protocole.txt");
	    }

	  s->initTexture();
	  s->initPos();
	  s->Display(); // Load textures.
	}
    }
  _initShape = true;
  
}
/** 
 * If session is initialized : show trial
 * else : show dummy GL_QUAD to calculate displaying delay
 * 
 */
void
Session::displayHeader()
{
  if (!initialized())
    {				

      if (!_initShape)
	{
	  initShape();
	}

      glClear (GL_DEPTH_BUFFER_BIT);
      glClear(GL_COLOR_BUFFER_BIT);
      glDisable (GL_LIGHTING);
      
      glBegin(GL_QUADS);
      glColor3ub(255, 155, 255);    
      glVertex2d(-0.1, -0.1);
      glVertex2d(-0.1, 0.1);
      glVertex2d(0.1, -0.1);
      glVertex2d(0.1, 0.1);
      glEnd();

      glEnable(GL_LIGHTING);
      glutPostRedisplay();
      glutSwapBuffers();

      if (nbInitFrames() < nbFrame4init())
	{
	  ++_nbInitFrames;
	}
      else
	{
	  _initialized = true;
	}
    }   
  else
    {
 				
      int window_height =  setup->screenHeight();
      int window_width = setup->screenWidth();
    
      float ratio = setup->ratio();

      glClear (GL_COLOR_BUFFER_BIT);						
      glClear (GL_DEPTH_BUFFER_BIT);
	
      glLightfv(GL_LIGHT0, GL_AMBIENT, _lA);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, _lD);
      glLightfv(GL_LIGHT0, GL_POSITION, _lP);

      if (setup->nbScreen()==2)
	{
	  for (int loop=1; loop<=2; loop++)
	    {
	      if (loop==0){
		glViewport(0,0,window_width/2, window_height); 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90, ratio, 1.0f, 2000.0f); 
		glMatrixMode(GL_MODELVIEW);
	      }
	      if (loop==1)
		{
		  glViewport(window_width/2,0,window_width/2, window_height);
		  glMatrixMode(GL_PROJECTION); 
		  glLoadIdentity(); 
		  gluPerspective(90, ratio, 1.0f, 2000.0f); 
		  glMatrixMode(GL_MODELVIEW);
		}

	      glMatrixMode(GL_MODELVIEW);		
	      glLoadIdentity();			

	      displayFrame(loop);
	    
	      glutPostRedisplay();	 
	    }
	}
      else
	{
	  glViewport(0,0,window_width, window_height); 
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(90, ratio, 1.0f, 2000.0f); 
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity ();	
      
	  displayFrame(1);
      
	  glutPostRedisplay();

	}
    }
  glutSwapBuffers();
}



GLvoid
Session::InitGL()
{
  glEnable(GL_TEXTURE_2D);
 
  glClearColor(_RGB[0],_RGB[1],_RGB[2], 1.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glDepthFunc (GL_LEQUAL);
  glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); 
	
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
}

/**
 * Inits and launch the GLUT loop
 *
 * @param argc
 * @param argv
 */
void
Session::run(int argc,
             char** argv)
{
 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(setup->screenWidth(),setup->screenHeight());
  glutInitWindowPosition(0, 0);
  glutCreateWindow((char*)"Time in Dynamic Perspective");

  glutGameModeString(setup->gameModeString().c_str());
  //  glutEnterGameMode();
  glutFullScreen();
  glutSetCursor(GLUT_CURSOR_NONE);
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  glutReshapeFunc(&reshape);
  glutDisplayFunc (&displayRexeno);
  glutKeyboardFunc(&keyPressed);
  glutKeyboardUpFunc(&keyUp);

  InitGL();

  glutMainLoop();

}

/** 
 * displays a single frame of the Session (must return quickly in order for the GLUT loop to
 * continue smoothly)
 * 
 */
void
Session::displayFrame(int idScreen)
{
#ifdef DEBUG
  PDEBUG("Session::displayFrame ", __debug_FrameNumber << "/" << _trialsOrder.size() << " trials in this session");
#endif
  
  if (_currentTrial != _trialsOrder.end())
    {
      
      PDEBUG("Session::displayFrame", " trial frame ");
      Trial* t = _trialsDefinitions[*_currentTrial];
      if (t->atStart() && beforeTrial)
	{
	  beforeTrial(t->name(), t->variables);
	};

      t->setIdScreen(idScreen);

      int b = t->displayFrame(_driver);

      if (b != RUNNING)
	{

	  PDEBUG("Session::displayFrame", " end of trial : " << t->name() << " (trial number " << *_currentTrial << " )");

	  if (idScreen==1){
	    ms displayTime = _driver->GetTimeMilliseconds();
	    recorder->Save("EndTrial " + lexical_cast<string>(displayTime), "events.txt");
	
	    if (afterTrial)

	      afterTrial(t->name(), t->variables, b);

	    _currentTrial++;
	    t->Reset(_driver);
	  }
	 
#ifdef DEBUG
	  ++__debug_FrameNumber;
#endif
	}

    }
  else
    {
      PDEBUG("Session::displayTime", " regular exit")
	exit (0);
    }
}



/** 
 * Standard SINGLETON member
 * 
 * 
 * @return 
 */
Session*
Session::getInstance()
{
  return _instance; 
}

/** 
 * Standard SINGLETON member
 * 
 * @param s 
 * 
 * @return 
 */
Session*
Session::getInstance(configuration::SessionInfo& s,
                     Order& o)
{
  _instance = new Session(s, o);

  return (_instance);
}

ms
Session::getTime()
{
  assert (_driver);
  return _driver->GetTime();
}

bool
Session::initialized()
{
  return (_initialized);
}
