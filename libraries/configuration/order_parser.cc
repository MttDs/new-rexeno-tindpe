#include "order_parser.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;


Order::Order(string filename)
  : _trialsOrder()
{
  ifstream infile;
  string sLine;

  try
  {
    infile.open(filename.c_str());
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

Order::~Order()
{

}

vector<int>&
Order::getOrder()
{
  return (_trialsOrder);
}
