#include <wordexp.h>
#include "model.hh"
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

using namespace std;

Model::Model()
{
  wordexp_t exp_result;
  wordexp("~/.rexeno", &exp_result, 0);
  const string confDir(exp_result.we_wordv[0]);

  fillAlreadyExistingTrials(confDir);
}

Model::~Model()
{

}

void
Model::fillAlreadyExistingTrials(const string& confDir)
{
  namespace fs = boost::filesystem;
  fs::path someDir(confDir + "/trial_types/");
  fs::directory_iterator end_iter;

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

void
Model::AddTrial(std::string s)
{
  _trialsInSession.insert(s);
}
