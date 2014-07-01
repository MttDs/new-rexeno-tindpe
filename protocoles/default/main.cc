#include <iostream>
// #include <GL/glut.h>
#include <stdlib.h>     /* srand, rand */
#include <rexeno.hh>
#include <cstdlib>
//#include <rexeno/dummyDriver.hh>

using namespace std;


void		GO_Target1(VariableManager& TM)
{
 /* Variable	*fixation_duration = TM.getVariable("Fixation_Duration");
  // Variable	*fixation_duration = new Variable(0);
  Variable	*end_fixation = TM.getVariable("End_Fixation");
  Variable	*end_target = TM.getVariable("End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  //end_fixation->value = fixation_duration->value;
  end_fixation->value = 1000;
  end_target->value = end_fixation->value + 60;*/
}

void		GO_Target2(VariableManager& TM)
{
 /* Variable	*fixation_duration = TM.getVariable("Fixation_Duration");
  // Variable	*fixation_duration = new Variable(0);
  Variable	*end_fixation = TM.getVariable("End_Fixation");
  Variable	*end_target = TM.getVariable("End_Target");

  
  fixation_duration->value = rand() % 30 + 30; // Un nombre random entre 30 et 60
  //end_fixation->value = fixation_duration->value;
  end_fixation->value = 1000;
  end_target->value = end_fixation->value + 60;*/
}


void		InterTrial_CTM(std::string &name,
                               VariableManager& TM)
			       //int r) // Sera executée à chaque intertrial !
{
 /* //std::cout << "REDO ? " << r << std::endl;
  // if (r == 1)
  //   {
  //     std::cout << "Send Pulse" << std::endl;
  //   }

 GO_Target1(TM);
 GO_Target2(TM);
  //Variable* start = TM.getVariable("Start_Correct");
  Variable* end = TM.getVariable("End_Target");
  //start->value = 1160;
  end->value = 1160;*/
}




int	main(int argc,
	     char **argv)
{
  configuration::SessionInfo conf;
  //bool r = configuration::CreateConfiguration("../../protocoles/DevTests/conf", conf);
  bool r = configuration::CreateConfiguration("definition", conf);
  Order o("order", conf);
  o.parse();
  
  std::string name = "";
  std::string block = "";

  std::cout << "Subject's name => ";
  cin >> name;
  std::cout << "Block num1ber => ";
  cin >> block;

  conf.name = name;
  conf.block = block;

  Setup* setup = new Setup(conf);
  Session* session = Session::getInstance(conf, o);
  session->setup = setup;
  session->beforeTrial = &InterTrial_CTM;
  session->run(argc, argv);
  
  delete session;
  session = NULL;

  exit(EXIT_SUCCESS);
}
