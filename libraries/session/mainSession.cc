
# include <GL/glew.h>
# include <GL/freeglut.h>

# include <iostream>
# include "order_parser.hh"
# include "trial.hh"
# include "setup.hh"

# include "session.hh"
# include "dummyDriver.hh"

using namespace std;


void		GO_Target1(VariableManager& TM)
{
  // Variable	*fixation_duration = TM->GetVariable("GO_TARGET1", "Fixation_Duration");
 // Variable	*fixation_duration = new Variable(0);
  //Variable	*end_fixation = TM.getVariable("End_Fixation");
  //Variable	*end_target = TM.getVariable("End_Target");


 // fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
 // end_fixation->value = fixation_duration->value;
//  end_target->value = end_fixation->value + 60;
}
/*
void		GO_Target2(VariableManager& TM)
{
  // Variable	*fixation_duration = TM->GetVariable("GO_TARGET2", "Fixation_Duration");
  Variable	*fixation_duration = new Variable(0);
  Variable	*end_fixation = TM.getVariable("End_Fixation");
  Variable	*end_target = TM.getVariable("End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  end_fixation->value =  fixation_duration->value;
  end_target->value = end_fixation->value + 60;
}
*/

void		InterTrial_CTM(std::string &name,
                               VariableManager& TM)
			       //int r) // Sera executée à chaque intertrial !
{
  //std::cout << "REDO ? " << r << std::endl;
  // if (r == 1)
  //   {
  //     std::cout << "Send Pulse" << std::endl;
  //   }

 // GO_Target1(TM);
 // GO_Target2(TM);
  //Variable* start = TM.getVariable("Start_Correct");
/*  Variable* end = TM.getVariable("End_Target");
  //start->value = 1160;
  end->value = 10;*/
}

int	main(int argc,
	     char **argv)
{
  configuration::SessionInfo conf;

  bool r = configuration::CreateConfiguration("../testFiles/session/definition", conf);

  string t(string("../testFiles/session/order"));

  Order o(t, conf);
  o.parse();

  assert(r);
  Setup* setup = new Setup("~/.rexeno");
  Session* session = Session::getInstance(conf, o);
  // Driver* d = new DummyDriver();

  session->setup = setup;
  session->beforeTrial = &InterTrial_CTM;

  session->run(argc, argv);
  
}
