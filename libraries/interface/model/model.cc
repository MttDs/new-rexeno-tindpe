#include "model.hh"


Model::Model(SessionInfo *si)
{
  sessionInfo = si;
  _recorder = NULL;
}

Model::~Model()
{

}
/**
   note: Verifie si chacune des sessions porte un nom !=
   et si chacune des formes (de chaque session) porte un 
   nom !=
 **/

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

  string test, test1;
  vector<string>::iterator it, it2;
  bool b = true;

  // Recherche si deux sessions ont le meme nom
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

      // Recherche si deux formes ont le meme nom

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

  // Enleve les redondances (vecteur nom des sessions)

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
  tmp.clear();

  b = true;
  
  // Enleve les redondances (vecteur nom des parent ayant une ou
  // plusieurs formes avec le meme nom

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

  // Prepare le message

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

/**
   note: Note dans le fichier "definition" la configuration
 **/
void
Model::save()
{

  _recorder = new Recorder("files/", 0);

  _recorder->AddFile("definition");

  _recorder->Save("frequency= "+ lexical_cast<string>(sessionInfo->frequency), "definition");
  _recorder->Save("width= "+ lexical_cast<string>(sessionInfo->width), "definition");
  _recorder->Save("height= "+ lexical_cast<string>(sessionInfo->height), "definition");
  _recorder->Save("nb_screens= "+ lexical_cast<string>(sessionInfo->nb_screens), "definition");
  _recorder->Save("nb_trials= "+ lexical_cast<string>(sessionInfo->nb_trials), "definition");
  _recorder->Save("shuffle= "+ lexical_cast<string>(sessionInfo->shuffle), "definition");
  if (sessionInfo->save != "")
    {
      _recorder->Save("save= " + sessionInfo->save, "definition");
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
		      , "definition");
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
	  _recorder->Save(str, "definition");

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
			      " ", "definition");
	    }
	}
      _recorder->Save(";", "definition");
    }
  QMessageBox::information(0, "Information", QString::fromUtf8("Fichier enregistré dans le dossier 'files/'"));

}
/**
   note: Note dans le fichier "definition" la configuration 
   apres avoir verifie la validité de la configuration
 **/
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
