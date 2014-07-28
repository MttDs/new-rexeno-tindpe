#include "model.hh"


Model::Model(SessionInfo *si)
{
  sessionInfo = si;
  _recorder = NULL;
}

Model::~Model()
{

}

void
Model::save()
{

  _recorder = new Recorder("../../files/", 0);

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
}

