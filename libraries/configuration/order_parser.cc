#include "order_parser.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

# include "recorder.hh"
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace configuration;

Order::Order(std::string filename, configuration::SessionInfo& s)
  : _trialsOrder()
{

  _filename = filename;
  _nbTrials = s.trials.size();
  _nbSessions = s.nb_trials;

  switch (s.shuffle){
  case 0:
    break;
  case 1:
    _random();
    break;
  case 2:
    _pile();
    break;
  case 3:
    _oneAfterTheOther();
    break;
  }
}

Order::~Order()
{

}

vector<int>&
Order::getOrder()
{
  return (_trialsOrder);
}

void
Order::parse(){
  ifstream infile;
  string sLine;

  try
  {
    infile.open(_filename.c_str());
    while (!infile.eof())
    {
      getline(infile, sLine);
      if (sLine.length())
        _trialsOrder.push_back(boost::lexical_cast<int>( sLine ));
    }
  }
  catch(...)
  {
    cout << "ordering file : bad filename or bad content in file";
  }
  infile.close();
}

void 
Order::_random(){
  int seed = 0,  min = 0,  max = _nbTrials-1;
  Recorder* _order = new Recorder();
  _order->AddFile("order");

  for (int ii=0; ii<_nbSessions; ii++){
    seed = (int) (std::time(0)+(int)rand()); //(std::time(0)+sum);
    srand(seed);
  
    std::string val = lexical_cast<string>(rand()%((max+1) - min) + min);
    _order->Save(val, "order");
  }
}

void
Order::_pile(){
  int nb =  _nbSessions/_nbTrials;
  std::cout << nb << std::endl;
 
  Recorder* _order = new Recorder();
  _order->AddFile("order");

  for (int ii=0;ii<_nbTrials;ii++){
    for (int jj=0;jj<nb;jj++){
      std::string val = lexical_cast<string>(ii);
       _order->Save(val, "order");
    }
  }
}

void
Order::_oneAfterTheOther(){

  int jj=0, ii=0;

  Recorder* _order = new Recorder();
  _order->AddFile("order");

  bool end = false;
  while (jj<_nbSessions && end==false){
    ii=0;
    while (ii<_nbTrials && end==false){

      std::string val = lexical_cast<string>(ii);
      _order->Save(val, "order");

      jj++;
      ii++;

      if (jj==_nbSessions){
	end = true;
      }
 
    }
  }
}
