#include "parser.hh"
#include "model.hh"
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

Model::Model()
{

}

void
Model::setTrialName(const string& trialName)
{
  _trialName = trialName;
}

void
Model::addShape2Trial(const string& shape)
{
  _availableShapes.push_back(shape);
}

void
Model::fillAvailableShapes(const string& confDir)
{
  string sLine;
  ifstream infile;
  infile.open ((confDir + "/shape_prototypes").c_str());
  string previousLine="";
  std::vector<std::string> strs;
  std::vector<std::string>::iterator it;
 
  while (!infile.eof())
  {
    getline(infile, sLine);
    boost::split(strs, sLine, boost::is_any_of("\t "));
    _availableShapes.push_back(strs[0]);
    cout << strs[0] << endl;
    vector<string>::const_iterator first = strs.begin() + 1;
    vector<string>::const_iterator last = strs.end();
    shapePrototypes[strs[0]] = vector<string>(first, last);
  }  
  infile.close();
  for (it = strs.begin(); it != strs.end(); ++it)
  {
    

  }
}

void
Model::fillAlreadyExistingTrials(const string& confDir)
{
  namespace fs = boost::filesystem;
  fs::path someDir(confDir + "/trial_types/");
  fs::directory_iterator end_iter;

  cout << confDir << endl;
  //typedef std::multimap<std::time_t, fs::path> result_set_t;
  //result_set_t result_set;

  if ( fs::exists(someDir) && fs::is_directory(someDir))
  {
    for( fs::directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
    {
      if (fs::is_regular_file(dir_iter->status()) )
      {
        //result_set.insert(result_set_t::value_type(fs::last_write_time(dir_iter->status()), *dir_iter));
        _availableTrials.push_back((*dir_iter).path().filename().string());
        //cout << (*dir_iter).path().filename().string() << endl;
      }
    }
  }
}

