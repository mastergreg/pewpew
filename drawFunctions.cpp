#include "drawFunctions.h"
void drawEnemyList(std::list<game_ship *> lst)
{
  std::list<game_ship*>::iterator p=lst.begin();
  while(p != lst.end())
  {  
    (*p)->draw();
    p++;
  }
}

void drawDrawableList(std::list<game_object *> lst)
{
  std::list<game_object *>::iterator p=lst.begin();
  while(p != lst.end())
  {  
    (*p)->draw();
    p++;
  }
}
