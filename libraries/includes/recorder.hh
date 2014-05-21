#ifndef RECORDER_HH_
# define RECORDER_HH_

#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Recorder
{
public:
  Recorder();
  Recorder(std::string folder,
           int traceLevel);
  ~Recorder();

  void AddFile(std::string filename);
  void Save(string data,
            string filename);
  void Save(string data,
            string filename,
            int traceLevel);

  void Save(std::vector<float>* data,
            string filename);

  void Save(double value,
            string filename);
  void Save(std::vector<pair<double, double> >* data,
            string filename);
  void Save(pair<double, double>* data,
            string filename);
  void SetFolder(std::string	f);
  std::string GetFolder();

  vector<pair<string, ofstream*> >* fichiers;

  bool in_trial;
private:
  std::string _folder;
  int _traceLevel;

  std::string _getCurrentDateTime();
};


#endif
