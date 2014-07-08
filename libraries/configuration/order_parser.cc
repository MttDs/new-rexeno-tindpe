#include "order_parser.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <stdlib.h>     /* malloc, free, rand */

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

  if (!_isValid())
    {
      std::cout << "( numbers of sessions % numbers of trials ) != 0 !" << std::endl;
      throw;
    }

  switch (s.shuffle)
    {
    case 0:
      break;
    case 1:
      _blockRandom();
      break;
    case 2:
      _random();
      break;
    case 3:
      _simpleRandom();
      break;
    case 4:
      _block();
      break;
    case 5:
      _oneAfterTheOther();
      break;
    default:
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

bool 
Order::_isValid(){
  if((_nbSessions%_nbTrials)==0)
    {
      return true;
    }
  return false;
}

void
Order::_random(){
  vector<int> order, newOrder;
  vector<int>::iterator it;

  order = _getBlocks();

  int seed = 0,  min = 0,  max = order.size()-1, ii = 0;
  std::string val = "";
  Recorder* _orderFile = new Recorder();

  _orderFile->AddFile("order");

  while (order.size()!=0)
    {
      // std::cout << order.size() << std::endl;
      max = order.size()-1;

      seed = (int) (std::time(0)+(int)rand());
      srand(seed);

      ii = rand()%(((max+1) - min) + min); 
      newOrder.push_back(order.at(ii));
      order.erase(order.begin()+(ii));
    }
  
  for(it=newOrder.begin();it!=newOrder.end();it++)
    {
      val = lexical_cast<string>(*it);
      _orderFile->Save(val, "order");
    }
  
}

vector<int>
Order::_getBlocks(){

  int nb = _nbSessions/_nbTrials;
  int ii=0, jj=0, kk=0;
  bool end = false;
  vector<int> order;

  while(ii<_nbSessions)
    {

      while (jj<nb && end == false)
	{
	  order.push_back(kk);
	  jj++;
	  ii++;

	  if (ii>=_nbSessions)
	    {
	      end = true;
	    }
	}
  
      kk++;
      jj=0;
    
      if(kk>= _nbTrials)
	{
	  kk=0;
	}
    }  
  return order;
}

void 
Order::_simpleRandom()
{
  int seed = 0,  min = 0,  max = _nbTrials-1;
  std::string val = "";
  Recorder* _order = new Recorder();

  _order->AddFile("order");

  for (int ii=0; ii<_nbSessions; ii++)
    {
      seed = (int) (std::time(0)+(int)rand()); //(std::time(0)+sum);
      srand(seed);
  
      std::string val = lexical_cast<string>(rand()%((max+1) - min) + min);
      _order->Save(val, "order");
    }
}

void
Order::_block(){

  Recorder* _order = new Recorder();
  _order->AddFile("order");

  vector<int> block = _getBlocks();
  vector<int>::iterator it;
 
  for(it=block.begin(); it!=block.end();it++){
    _order->Save(lexical_cast<string>(*it), "order");
  }
 
}

void
Order::_oneAfterTheOther()
{

  int jj=0, ii=0;
  bool end = false;
  Recorder* _order = new Recorder();

  _order->AddFile("order");

  while (jj<_nbSessions)
    {
      ii=0;
      while (ii<_nbTrials && end==false)
	{

	  _order->Save(lexical_cast<string>(ii), "order");

	  jj++;
	  ii++;

	  if (jj==_nbSessions){
	    end = true;
	  }
	}
    }
}

void 
Order::_blockRandom()
{
  int seed = 0,  min = 0, val = 0, ii;

  Recorder* _order = new Recorder();
  _order->AddFile("order");

  vector<int> block, temp;

  vector<int>::iterator it;
  unsigned int jj;
  int pp = 0;
  for (ii=0; ii<_nbTrials; ii++)
    {
      block.push_back(ii); 
    }
  
  for (ii=0; ii<(_nbSessions/_nbTrials); ii++)
    {
      temp = block;
      printf("%d\n", ii);
      for(jj = 0; jj<block.size(); jj++)
	{
	  pp = pp+1;
	  seed = (int) (std::time(0)+(int)rand());
	  srand(seed);
  
	  val = (rand()%((temp.size()) - min) + min);
	  _order->Save(lexical_cast<string>((int)temp.at(val)), "order");
	  std::cout <<pp << " => " << temp.at(val) << std::endl;
	  temp.erase(temp.begin()+(val));
	}
    }

}
