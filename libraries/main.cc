#include <iostream>
#include "parser.hh"
#include "session.hh"
#include <sys/types.h>
#include <signal.h>

#include <assert.h>

int launch();

using namespace std;

int	main(int argc,
	     char **argv)
{
  configuration::SessionInfo conf;
  bool r = configuration::CreateConfiguration(argv[1], conf);
  assert(r);

  int pid = fork();
  if (pid == 0)
    {
      while (1)
	{
	  printf("i am the child\n");
	  sleep(1);
	}
    }
  else
    {
      printf("i am the parent !\n");
      sleep(5);
      kill(pid, 9);
      //launch();
    }
  //Session s(conf);
}

