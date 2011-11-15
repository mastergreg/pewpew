/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.h

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Mon 24 Oct 2011 03:52:36 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef SOUNDS_H
#define SOUNDS_H

//#ifdef __linux__

//#include <OpenAL/al.h>
#include "alut.h"

//#endif

#include <iostream>
#include <cstdlib>
#include "game_state.h"

#define SOUNDS 2

extern game_state gs;

enum {PEW,BLAST};
class sound_player
{
  private:
    unsigned int buffers[SOUNDS];
    unsigned int sources[SOUNDS];
  public:
    void play(int sound);
    sound_player();
};






#endif
