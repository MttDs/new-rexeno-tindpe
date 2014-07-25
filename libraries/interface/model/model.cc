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
  std::cout << "save!" << std::endl;
  _recorder->AddFile("test.txt");

  _recorder->Save("frequency= "+ lexical_cast<string>(sessionInfo->frequency), "test.txt");
  _recorder->Save("width= "+ lexical_cast<string>(sessionInfo->width), "test.txt");
  _recorder->Save("height= "+ lexical_cast<string>(sessionInfo->height), "test.txt");
  _recorder->Save("nb_screens= "+ lexical_cast<string>(sessionInfo->nb_screens), "test.txt");
  _recorder->Save("nb_trials= "+ lexical_cast<string>(sessionInfo->nb_trials), "test.txt");
  _recorder->Save("shuffle= "+ lexical_cast<string>(sessionInfo->shuffle), "test.txt");
  _recorder->Save("save= " + sessionInfo->save, "test.txt");

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
		      , "test.txt");
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
	  _recorder->Save(str, "test.txt");

	  //Event

	  first = true;
	  str = "";

	  foreach(sl, si.listeners)
	    {
	      stringstream ss (stringstream::in | stringstream::out);

	      _recorder->Save("+ "
			      + lexical_cast<string>(sl.key) + 
			      " "
			      + ss.str() +
			      " "
			      + lexical_cast<string>(sl.gain)+ 
			      " ", "test.txt");
	    }
	  /*for (it = si.attributes.begin(); it != si.attributes.end(); ++it)
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
		}*/
	  //  _recorder->Save(str, "test.txt");
	}
      _recorder->Save(";", "test.txt");
    }
}

