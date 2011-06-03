#include "game_object.h"
game_object::game_object()
:position(0,0,0,0,0)
{
}

game_object::game_object(vector pos)
:position(pos)
{
}
void game_object::die()
{
}
int game_object::get_life()
{
  return life;
}
void game_object::draw() {}
bool game_object::collides(game_object *test)
{
  double dist = position.distance(test->position);
  if(dist<(radius+test->radius))
  {
    return true;
  }
  else
  {
    return false;
  }
}
