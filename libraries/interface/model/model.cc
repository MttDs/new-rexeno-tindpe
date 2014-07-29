#include "model.hh"


Model::Model(SessionInfo *si)
{
  sessionInfo = si;
  _recorder = NULL;
}

Model::~Model()
{

}

bool
Model::_isValid()
{
  vector<TrialInfo> trials, trials2;
  trials = trials2 = sessionInfo->trials;
  TrialInfo trial, trial2;
  
  vector<ShapeInfo> shapes;
  ShapeInfo shape, shape2;

  vector<string> trialName;
  vector<string> parentName;
  vector<string> tmp;

  int ii, jj, kk, ll;
  ii = jj = kk = ll = 0;

  foreach(trial, trials)
    {
      foreach(trial2, trials2)
	{
	  if (trial.name==trial2.name && ii!=jj)
	    {
	      trialName.push_back(trial.name);
	    }
	  jj++;
	}
      jj=0;
      ii++;

      shapes = trial.shapes;
      foreach(shape, shapes)
	{
	  foreach(shape2, shapes)
	    {
	      if (shape.attributes[0]==shape2.attributes[0] && kk!=ll)
		{
		  parentName.push_back(trial.name);
		}
	      ll++;
	    }
	  ll=0;
	  kk++;
	}
      kk=0;
    }

  string test, test1;
  vector<string>::iterator it, it2;
  bool b = true;
  for(it=trialName.begin();it!=trialName.end(); ++it)
    {
      for (it2=tmp.begin(); it2!=tmp.end(); ++it2)
	{
	  if (*it2==*it)
	    {
	      b = false;
	      break;
	    }
	}
      if (b)
	{
	  tmp.push_back(*it);
	}
      b=true;
    }
  trialName = tmp;
  /* std::cout << "1 >"<< std::endl;
     foreach(test1, trialName)
     {
     std::cout << test1 << ", ";
     }
     std::cout << std::endl;*/

  tmp.clear();
  b = true;
  for(it=parentName.begin();it!=parentName.end(); ++it)
    {
      for (it2=tmp.begin(); it2!=tmp.end(); ++it2)
	{
	  if (*it2==*it)
	    {
	      b = false;
	      break;
	    }
	}
      if (b)
	{
	  tmp.push_back(*it);
	}
      b=true;
    }
  parentName = tmp;
  /* std::cout << "2 >"<< std::endl;

     foreach(test, parentName)
     {
     std::cout << test << ", ";
     }
     std::cout << std::endl;*/
  string str = "";
  b = true;
  if (parentName.size()!=0)
    {
      str += "\n Des formes ont le même nom dans le(s) session(s): ( ";
      foreach(test, parentName)
	{
	  str += (test + " ");
	}
      str += ").";
      b = false;
    }
  if (trialName.size()!=0)
    {
      str += "\n Des sessions ont le même nom: ( ";
      foreach(test1, trialName)
	{
	  str += test1 + " ";
	}
      str += ").";
      b = false;
       
    }
  _message = "Impossible: "+ str;
  return b;
}
void
Model::save()
{

  _recorder = new Recorder("files/", 0);

  _recorder->AddFile("definition.txt");

  _recorder->Save("frequency= "+ lexical_cast<string>(sessionInfo->frequency), "definition.txt");
  _recorder->Save("width= "+ lexical_cast<string>(sessionInfo->width), "definition.txt");
  _recorder->Save("height= "+ lexical_cast<string>(sessionInfo->height), "definition.txt");
  _recorder->Save("nb_screens= "+ lexical_cast<string>(sessionInfo->nb_screens), "definition.txt");
  _recorder->Save("nb_trials= "+ lexical_cast<string>(sessionInfo->nb_trials), "definition.txt");
  _recorder->Save("shuffle= "+ lexical_cast<string>(sessionInfo->shuffle), "definition.txt");
  if (sessionInfo->save != "")
    {
      _recorder->Save("save= " + sessionInfo->save, "definition.txt");
    }
  TrialInfo ti;
  ShapeInfo si;
  ShapeListener sl;

  vector<string>::iterator it;
  bool first;
  string str = "";
  foreach (ti, sessionInfo->trials)
    {
      _recorder->Save("| "+
		      ti.name+" "+
		      ti.attributes[0]+" "+
		      ti.attributes[1]+" "+
		      ti.attributes[2]+" "+
		      ti.attributes[3]+" "+
		      ti.attributes[4]+" "+
		      ti.attributes[5]+" "+
		      ti.attributes[6]+" "+
		      ti.attributes[7]+" "+
		      ti.attributes[8]
		      , "definition.txt");
      foreach (si, ti.shapes)
	{
	  //Shape
	  first = true;
	  str = "";
	  for (it = si.attributes.begin(); it != si.attributes.end(); ++it)
	    {
	      if (first)
		{
		  first = false;
		  str += "> "+ si.name + " " + (*it);
		}
	      else
		{
		  str += " " + (*it) + " ";
		}
	    }
	  _recorder->Save(str, "definition.txt");

	  //Event

	  foreach(sl, si.listeners)
	    {
	      stringstream ss (stringstream::in | stringstream::out);
	      ss << sl.coef;
	      _recorder->Save("+ "
			      + lexical_cast<string>(sl.key) + 
			      " "
			      + ss.str() +
			      " "
			      + lexical_cast<string>(sl.gain)+ 
			      " ", "definition.txt");
	    }
	}
      _recorder->Save(";", "definition.txt");
    }
  QMessageBox::information(0, "Information", QString::fromUtf8("Fichier enregistré dans le dossier 'files/'"));

}

void
Model::checkAndSave()
{

  if (_isValid())
    {
      save();
    }
  else
    {
      QMessageBox::warning(0, "Warning!", QString::fromUtf8(_message.c_str()));
    }
}
