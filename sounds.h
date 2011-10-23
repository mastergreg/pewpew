/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.h

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Sun 23 Oct 2011 10:13:09 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef SOUNDS_H
#define SOUNDS_H

#include <AL/alut.h>
#include <iostream>
#include <cstdlib>

#define SOUNDS 2

extern int sounds_on;

enum {PEW,BLAST};
class sound_player
{
  private:
    ALuint buffers[SOUNDS];
    ALuint sources[SOUNDS];
  public:
    void play(int sound);
    sound_player();
};






#endif
