/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.cpp

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Sun 23 Oct 2011 10:13:37 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/


#include "sounds.h"

sound_player::sound_player()
{
  alutInit(NULL,NULL);
  buffers[PEW] = alutCreateBufferFromFile("sounds/pew.wav");
  buffers[BLAST] = alutCreateBufferFromFile("sounds/blast.wav");

  //alGenSources(1,&source);
  alGenSources(SOUNDS,sources);

  alSourcei(sources[PEW],AL_BUFFER,buffers[PEW]);
  alSourcei(sources[PEW],AL_LOOPING,AL_FALSE);

  alSourcei(sources[BLAST],AL_BUFFER,buffers[BLAST]);
  alSourcei(sources[BLAST],AL_LOOPING,AL_FALSE);
}

void sound_player::play(int sound)
{
  if (sounds_on == 1)
  {
    switch(sound)
    {
      case PEW:
        alSourcePlay(sources[PEW]);
        break;
      case BLAST:
        alSourcePlay(sources[BLAST]);
        break;
      default:
        break;
    }
  }
  else
  {
    alSourceStop(sources[PEW]);
    alSourceStop(sources[BLAST]);
  }
}
