#include "trial.hh"
#include "driver.hh"
#include "setup.hh"

#include <boost/foreach.hpp>

Trial::Trial(TrialInfo& ti)
  : _curFrameId(0),
    _nbFrames(1),
    _name(ti.name),
    _logged(false),
    _start(true),
    _subjectResponse(false)
{
  _session = NULL;

  assert(ti.attributes.size() == 10);

  variables.addVariable(_time = new Variable(ti.attributes[0]));
  variables.addVariable(_cameraVeloX = new Variable(ti.attributes[1]));
  variables.addVariable(_cameraVeloY = new Variable(ti.attributes[2]));
  variables.addVariable(_cameraVeloZ = new Variable(ti.attributes[3]));
  variables.addVariable(_eyeX = new Variable(ti.attributes[4]));
  variables.addVariable(_eyeY = new Variable(ti.attributes[5]));
  variables.addVariable(_eyeZ = new Variable(ti.attributes[6]));
  variables.addVariable(_centerX = new Variable(ti.attributes[7]));
  variables.addVariable(_centerY = new Variable(ti.attributes[8]));
  variables.addVariable(_centerZ = new Variable(ti.attributes[9]));

  _initCamera.push_back(_eyeX->value);
  _initCamera.push_back(_eyeY->value);
  _initCamera.push_back(_eyeZ->value);
  _initCamera.push_back(_centerX->value);
  _initCamera.push_back(_centerY->value);
  _initCamera.push_back(_centerZ->value);
  
  _data.resize(8); // 8 channels
  vector<channel>::iterator dataIt;
  // _data.resize(8 * 20); // 8 channels x 20 samples (20 > 16.666)
  for (dataIt = _data.begin(); dataIt != _data.end(); ++dataIt)
    {
      (*dataIt) = vector<Element>(20); // 20 samples per channel
    }
  
  vector<ShapeInfo>::iterator it;

  for (it = ti.shapes.begin(); it != ti.shapes.end(); ++it)
    {
      Shape *newShape = NULL;

      if (it->name == "Square")
	newShape = new Square(*it, variables, this);
      if (it->name == "Cross")
	newShape = new Cross(*it, variables, this);
      if (it->name == "WrongWindow")
	newShape = new WrongWindow(*it, variables, this);
      if (it->name == "CorrectWindow")
	newShape = new CorrectWindow(*it, variables, this);
      if (it->name == "NeutralWindow")
	newShape = new NeutralWindow(*it, variables, this);
      if (it->name == "FixationWindow")
	newShape = new FixationWindow(*it, variables, this);
      if (it->name == "Sphere")
	newShape = new Sphere(*it, variables, this);
      if (it->name == "Plan")
	newShape = new Plan(*it, variables, this);
      if (it->name == "Rectangle3d")
	newShape = new Rectangle3d(*it, variables, this);
      if (it->name == "Aircraft")
	newShape = new Aircraft(*it, variables, this);

      if (newShape)
	{
	  _shapes.push_back(newShape);
	  if (newShape->frameEnd() > _nbFrames)
	    _nbFrames = newShape->frameEnd();
	}
    }

  _status[RUNNING] = true;
  _status[PAUSE] = false;
  _status[WRONG_REDO] = false;
  _status[WRONG_NEXT] = false;
  _status[CORRECT] = false;
  _status[WAITING_FIXATION] = false;
  _status[NEUTRAL] = false;

  _ttl = new vector<TtlEvent*>;
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );
  _ttl->push_back( new TtlEvent() );

}

Trial::~Trial()
{
  vector<Shape*>::iterator it;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
    {
      Shape *curShape = *it;

      delete curShape;
    }
}

int
Trial::displayFrame(Driver* driver)
{

  if (_session == NULL){
    _session = Session::getInstance();
  }
  int fps = _session->getFrequency();

  _eyeX->value = _eyeX->value+(_cameraVeloX->value/fps);
  _centerX->value = _centerX->value+(_cameraVeloX->value/fps);
  _eyeY->value = _eyeY->value+(_cameraVeloY->value/fps);
  _centerY->value = _eyeY->value+(_cameraVeloY->value/fps);
  _eyeZ->value = _eyeZ->value+(_cameraVeloZ->value/fps);
  _centerZ->value = _centerZ->value+(_cameraVeloZ->value/fps);

  gluLookAt(_eyeX->value,
	    _eyeY->value,
	    _eyeZ->value, 
	    _centerX->value,
	    _centerY->value,
	    _centerZ->value, 
	    0,1,0);
 
  vector<Shape*>::iterator it;
  vector<Sphere*> spheres;

  bool canAnswer = false;
  int nbSphereEnd = 0, nbSphere = 0;

  vector<Adapt*> adapts;
  vector<Adapt*>*pAdapts = &adapts;
  for (it = _shapes.begin(); it != _shapes.end(); ++it)
    {
      Shape *curShape = *it;
      glPushMatrix();

      if (curShape->id()==7){
	nbSphere++;
	if (!curShape->Displayable(_curFrameId)){
	  nbSphereEnd++;
	}
      }

      curShape->setAdapts(pAdapts);
 
      if (curShape->Displayable(_curFrameId)){
    	curShape->Display();
      }

      glPopMatrix();
    }
 
  if (nbSphere==nbSphereEnd){
    canAnswer = true;
  }

  // PDEBUG("Trial::displayFrame", " displayed frame " << _curFrameId);

  _sendTtls(driver);

  driver->React2input();
  driver->AnalogIn(_data);    
  ms displayTime = driver->GetTime();
 
  if((_curFrameId == 0) && (_start)){
    string str;
    ostringstream ostr;
    ostr << _name 
	 << " Camera Velo [" 
	 << _cameraVeloX->value << "," << _cameraVeloY->value << "," << _cameraVeloZ->value
	 << "] Camera Eye ["
	 << _eyeX->value << "," << _eyeY->value << "," << _eyeZ->value
	 << "]";
    str = ostr.str();
    _session->recorder->Save(str,"trials.txt");

    for (it = _shapes.begin(); it != _shapes.end(); ++it)
      {
	Shape *curShape = *it;

	if ((_curFrameId == 0) && (!_logged))
	  {
	    _session->recorder->Save(curShape->getAttrsToString() ,"trials.txt");
	  }

      }
    _start = false;
    _session->recorder->Save("" ,"trials.txt");
  }
  
  if ((_curFrameId == 0) && (!_logged))
    {
      _session->recorder->Save("TrialStart_ " + lexical_cast<string>(displayTime), "events.txt");
      _session->recorder->Save(_name + ' ' + lexical_cast<string>(displayTime), "events.txt");

      _logged = true;
    }

  if (canAnswer){

    vector<Adapt*>::iterator aIt;

    Shape* parent  = NULL;
    bool submit = false;
    for (aIt = (*pAdapts).begin(); aIt != (*pAdapts).end(); aIt++){

      if ((*aIt)->key()->value == Setup::key){
	parent = (*aIt)->parent();
	
	if (true){
	  parent->updateVelo((*aIt)->coef()->value);
	}
	submit = true;
      }
    } 

    if ((submit) && (!_subjectResponse)){
	
      std::cout << "Reponse => " << Setup::key << endl;

      ostringstream ostr;
      ostr << "Response "
	   << lexical_cast<string>(displayTime) 
	   << " : " << Setup::key;

      _session->recorder->Save(ostr.str(), "events.txt");
      _subjectResponse = true;
      
      _status[CORRECT] = true;
    }
  }
  else{
    Setup::key = -1;
  }

  for (it = _shapes.begin(); it != _shapes.end(); ++it)
    {
      Shape *curShape = *it;

      if ((_curFrameId == 0) && (!_logged))
	{
	  _session->recorder->Save(curShape->getAttrsToString() ,"events.txt");
	}

      //PDEBUG("Trial::displayFrame ", curShape->name() << " f " << curShape->frameStart() << " t " << curShape->frameEnd() << " d " << curShape->Displayable(_curFrameId));
      if (curShape->Displayable(_curFrameId)){
	curShape->React2input(_status, _data, _curFrameId, driver->GetTime());

      }
    }

  //  Setup::reset();
  return (_react2status());
}

void
Trial::_sendTtls(Driver* d)
{
  vector<TtlEvent*>::iterator it;
  for (it = _ttl->begin(); it != _ttl->end(); ++it)
    {
      if ((*it)->value != 0)
	d->TtlPulse((*it)->value, (*it)->delay);
    }
}

int
Trial::_react2status()
{
  if (_status[CORRECT] == true)
    {

      PDEBUG("Trial::_react2status ", "CORRECT");
      return (CORRECT);
    }

  if (!_status[NEUTRAL])
    {
      if (_status[WRONG_NEXT] == true)
	{
	  PDEBUG("Trial::_react2status ", "WRONG_NEXT");
	  return (WRONG_NEXT);
	}

      if (_status[WRONG_REDO] == true)
	{
	  PDEBUG("Trial::_react2status ", "WRONG_REDO");
	  return (WRONG_REDO);
	}
    }
  if (_status[PAUSE] == true)
    {
      PDEBUG("Trial::_react2status ", "PAUSE");
      return (PAUSE);
    }

  if (_status[WAITING_FIXATION] == true)
    {
      _curFrameId++;
      PDEBUG("Trial::_react2status ", "WAITING_FIXATION");
      return (RUNNING);
    }

  if (_status[RUNNING] == true)
    {
      _curFrameId++;
      // PDEBUG("Trial::_react2status ", "RUNNING");
      return (RUNNING);
    }
  PDEBUG("Trial::_react2status ", "bug here");
  return (WRONG_NEXT); // should not get here (this line is to avoid a compiler warning)
}

void
Trial::adjustNbFrames()
{
  vector<Shape*>::iterator it;

  for (it = _shapes.begin(); it != _shapes.end(); ++it)
    {
      double curEndFrame = (*it)->frameEnd();

      if (curEndFrame > _nbFrames)
	_nbFrames = curEndFrame;
    }
}

bool
Trial::finished()
{
  return (_curFrameId > _nbFrames);
}

bool
Trial::atStart()
{
  return (_curFrameId == 0);
}

void
Trial::Reset(Driver *d)
{
  //  PDEBUG("Trial::Reset ", "start")
  _curFrameId = 0;
  _logged = false;
  _subjectResponse = false;
  Status::iterator it;
  for (it = _status.begin(); it != _status.end(); ++it)
    {
      it->second = false;
    }

  Shapes::iterator shapesIterator;
  for (shapesIterator = _shapes.begin(); shapesIterator != _shapes.end(); ++shapesIterator)
    {
      (*shapesIterator)->Reset();
    }
  
  _eyeX->value = _initCamera.at(0);
  _eyeY->value = _initCamera.at(1);
  _eyeZ->value = _initCamera.at(2);

  _centerX->value = _initCamera.at(3);
  _centerY->value = _initCamera.at(4);
  _centerZ->value = _initCamera.at(5);
  
  Setup::reset();
}

bool
Trial::status(int key)
{
  return _status[key];
}
