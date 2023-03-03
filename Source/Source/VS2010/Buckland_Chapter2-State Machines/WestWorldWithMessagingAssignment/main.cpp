// ∞‘¿”∞¯«–∞˙ 2018180009 ±ËΩ√¿Œ

#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Child.h"
#include "Father.h"
#include "Mother.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  std::cout << "<2018180009 ±ËΩ√¿Œ>\n";
  
  //seed random number generator
  srand((unsigned) time(NULL));

  //create a child
  Child* child = new Child(ent_Child);
  Father* father = new Father(ent_Father);
  Mother* mother = new Mother(ent_Mother);

  //create his wife
  //MinersWife* Elsa = new MinersWife(ent_Elsa);

  //register them with the entity manager
  EntityMgr->RegisterEntity(child);
  EntityMgr->RegisterEntity(father);
  EntityMgr->RegisterEntity(mother);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
      child->Update();
      father->Update();
      mother->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete father;
  delete child;
  delete mother;

  //wait for a keypress before exiting
  std::cout << "\n<2018180009 ±ËΩ√¿Œ>\n";
  PressAnyKeyToContinue();


  return 0;
}






