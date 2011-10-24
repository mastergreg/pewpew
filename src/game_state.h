/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : game_state.h

* Purpose :

* Creation Date : 24-10-2011

* Last Modified : Mon 24 Oct 2011 03:57:53 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/
#ifndef GAME_STATE_H
#define GAME_STATE_H
class game_state
{
  public: 
  bool paused;
  unsigned int menu_page;
  bool sounds_on;
  unsigned int diffifulty_level;
  unsigned int level_type;
  unsigned int player_ship_type;
  game_state();
  void gs_run(void);
  void gs_pause(void);
  void gs_back(void);
  void gs_info_action(void);
  void gs_option_action(void);
  void gs_sound_off(void);
  void gs_sound_on(void);
};


#endif
