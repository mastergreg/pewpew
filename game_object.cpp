#include "game_object.h"
game_object::game_object()
:position(0,0,0,0)
{
  radius=0;
  life=10;
}

game_object::game_object(vector2D pos)
:position(pos)
{
  radius=0;
  life=10;
}
void game_object::die()
{
  life=-1;
}
int game_object::get_life()
{
  return life;
}
void game_object::set_life(int new_life)
{
  life=new_life;
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

