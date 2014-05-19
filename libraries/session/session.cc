#include "session.hh"
#include "parser.hh"
#include "trial.hh"
#include "setup.hh"

#include "driver.hh"
#include "order_parser.hh"

using namespace configuration;

Session* Session::_instance = NULL;

int mainWindow;

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
  : _trialsOrder(o.getOrder()){

  Trial* t = NULL;
  vector<TrialInfo>::iterator it;

  for (it = s.trials.begin(); it != s.trials.end(); ++it)
    {
      t = new Trial(*it);
      _trialsDefinitions.push_back(t);
    }
  _frequency = s.frequency;
  _currentTrial = _trialsOrder.begin();
  beforeTrial = NULL;
  afterTrial = NULL;
  _inputData.resize(8);

  recorder = new Recorder(s.save, s.traceLevel);
  recorder->AddFile("results.txt");
  recorder->AddFile("trials.txt");
  
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
  
  _windowWidth = s.width;
  _windowHeight = s.height;

  stringstream ss;
  
  ss << _windowWidth 
     << "x" 
     << _windowHeight 
     << ":32@" 
     << s.frequency;

  _gameMode = ss.str();
  _nbScreen = s.nb_screens;
  _lP[0] = 0.0f; _lP[1] = 1.0f; _lP[2] = 0.4f;  _lP[3] = 0.0f; 
  _lA[0] = 0.5f; _lA[1] = 0.5f; _lA[2] = 0.5f;  _lA[3] = 2.0f; 
  _lD[0] = 1.0f ;_lD[1] = 1.0f; _lD[2] = 1.0f;  _lD[3] = 1.0f;
  _RGB[0] = 0.0f; _RGB[1] = 0.51; _RGB[2] = 0.73;

#ifdef DEBUG
  __debug_FrameNumber = 0;
#endif

  recorder->Save(s.name, "general.txt");
  recorder->Save(s.traceLevel, "general.txt");

#ifdef XENO
  _driver = new XenoDriver();
#else
  _driver = new DummyDriver();
#endif
}

/** 
 * Destructor : cleans everything up
 * TODO : this destructor is stupid and
 * probably not even called (program exited before)
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
  delete _instance;
  _instance = NULL;
  delete setup;
  setup = NULL;
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
void processNormalKeys(unsigned char key, int x, int y)
{
  Setup::keys[key] = true;
  Setup::key = key;
  if (key == 27)
    {
      exit(0);
    }
}

/**
 * Reshape the window's size
 */
void
reshape(int width, int height){
  if (height==0){
    height=1;
  }
  float ratio = 0.0;
  if (width >= height){
    ratio = float (width/height);
  }
  else{
    ratio = float (height/width);
  }
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
      glBegin(GL_QUADS);
      glColor3ub(255, 155, 255);    
      glVertex2d(-0.1, -0.1);
      glVertex2d(-0.1, 0.1);
      glVertex2d(0.1, -0.1);
      glVertex2d(0.1, 0.1);
      glEnd();

      glutSwapBuffers();
      glutPostRedisplay();
      glClear(GL_COLOR_BUFFER_BIT);

      if (nbInitFrames() < nbFrame4init())
	{
	  ++_nbInitFrames;
	}
      else
	{
	  _initialized = true;
	}
    }   
  else{
 				
    int window_height =  glutGet(GLUT_WINDOW_HEIGHT);
    int window_width = glutGet(GLUT_WINDOW_WIDTH);

    float ratio = 0.0;

    if (window_width >= window_height){
      ratio = float (window_width/window_height);
    }
    else{
      ratio = float (window_height/window_width);
    }

    glClear (GL_COLOR_BUFFER_BIT);

        glLightfv(GL_LIGHT0, GL_AMBIENT, _lA);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, _lD);
        glLightfv(GL_LIGHT0, GL_POSITION, _lP);
    if (getNbScreen()==2){
      for (int loop=0; loop<2; loop++){

	if (loop==0){

	  glViewport(0,0,window_width/2, window_height); 
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(90, ratio, 1.0f, 2000.0f); 
	  glMatrixMode(GL_MODELVIEW);
	}
	if (loop==1){
	  glViewport(window_width/2,0,window_width/2, window_height);
	  glMatrixMode(GL_PROJECTION); 
	  glLoadIdentity(); 
	  gluPerspective(90, ratio, 1.0f, 2000.0f); 
	  glMatrixMode(GL_MODELVIEW);
	}

	glMatrixMode (GL_MODELVIEW);		
	glLoadIdentity ();							
	glClear (GL_DEPTH_BUFFER_BIT);	

	if (loop==0){					
	  displayFrame(1);
	}
	if (loop==1){
	  displayFrame(2);
	}
	glutPostRedisplay();	 
      }
    }
    else{
      glViewport(0,0,window_width, window_height); 
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(90, ratio, 1.0f, 2000.0f); 
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity ();							
      glClear (GL_DEPTH_BUFFER_BIT);
      
      displayFrame(1);
      
      glutPostRedisplay();
    }
  }
  glutSwapBuffers();
}



GLvoid
Session::InitGL(){
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
  // configuration::SessionInfo& s;

  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(_windowWidth,_windowHeight);
  glutInitWindowPosition(0, 0);
  mainWindow = glutCreateWindow((char*)"Time in Dynamic Perspective");

  glutGameModeString(_gameMode.c_str());
  //glutEnterGameMode();
  //glutFullScreen();
  glutSetCursor(GLUT_CURSOR_NONE);
  glutReshapeFunc(&reshape);
  glutDisplayFunc (displayRexeno);
  glutKeyboardFunc(processNormalKeys);
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
  // PDEBUG("Session::displayFrame ", __debug_FrameNumber << "/" << _trialsOrder.size() << " trials in this session");
#endif
  
  if (_currentTrial != _trialsOrder.end())
    {
      //  PDEBUG("Session::displayFrame", " trial frame ");
      Trial* t = _trialsDefinitions[*_currentTrial];
      if (t->atStart() && beforeTrial)
	{
	  beforeTrial(t->name(), t->variables);
	};
      t->setIdScreen(idScreen);
      int b = t->displayFrame(_driver);
   
      if (b != RUNNING)
	{

	  // PDEBUG("Session::displayFrame", " end of trial : " << t->name() << " (trial number " << *_currentTrial << " )");
	  if (idScreen==1){
	  ms displayTime = _driver->GetTime();
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
