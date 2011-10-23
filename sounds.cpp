/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.cpp

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Sun 23 Oct 2011 10:00:34 PM EEST

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/


#include "sounds.h"

sound_player::sound_player()
{
  alutInit(NULL,NULL);
  pew_buffer = alutCreateBufferFromFile("sounds/pew.wav");
  blast_buffer = pew_buffer = alutCreateBufferFromFile("sounds/blast.wav");

  alGenSources(1,&pew_source);
  alGenSources(1,&blast_source);

  alSourcei(sources[PEW],AL_BUFFER,pew_buffer);
  alSourcei(sources[PEW],AL_LOOPING,AL_FALSE);

  alSourcei(sources[BLAST],AL_BUFFER,blast_buffer);
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
