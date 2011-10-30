/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : game_state.cpp

* Purpose :

* Creation Date : 24-10-2011

* Last Modified : Mon 24 Oct 2011 03:57:41 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#include "game_state.h"

game_state::game_state()
{
  paused = true;
  menu_page = 0;
  sounds_on = true;
  diffifulty_level = 0;
  level_type = 0;
  player_ship_type = 0;
}
void game_state::gs_run(void)
{
  paused = false;
  menu_page = 0;
}
void game_state::gs_pause(void)
{
  paused = true;
  menu_page = 0;
}
void game_state::gs_info_action(void)
{
  paused = true;
  menu_page = 1;
}
void game_state::gs_option_action(void)
{
  paused = true;
  menu_page = 2;
}
void game_state::gs_sound_off(void)
{
  sounds_on = false;
}
void game_state::gs_sound_on(void)
{
  sounds_on = true;
}
void game_state::gs_back(void)
{
  menu_page/=10;
}

