#ifndef MODEL_HH_
# define MODEL_HH_

# include <vector>
# include <string>
# include <set>

class Model
{
public:
  Model();
  ~Model();
  
  void fillAlreadyExistingTrials(const std::string& confFile);
  const std::vector<std::string>& availableTrials() {return _availableTrials;}
  std::set<std::string>& trialsInSession() {return _trialsInSession;}

  void AddTrial(std::string);
private:

  std::vector<std::string> _availableTrials;
  std::set<std::string> _trialsInSession;
};


#endif /* MODEL_HH_ */
