/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : game_state.cpp

* Purpose :

* Creation Date : 24-10-2011

* Last Modified : Wed 02 Nov 2011 11:09:13 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "game_state.h"

game_state::game_state()
{
  paused = true;
  sounds_on = true;
  diffifulty_level = 0;
  level_type = 0;
  player_ship_type = 0;
}
void game_state::gs_run(void)
{
  paused = false;
}
void game_state::gs_pause(void)
{
  paused = true;
}
void game_state::gs_sound_off(void)
{
  sounds_on = false;
}
void game_state::gs_sound_on(void)
{
  sounds_on = true;
}
