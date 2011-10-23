/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.cpp

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Sun 23 Oct 2011 08:15:49 PM EEST

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

  alSourcei(pew_source,AL_BUFFER,pew_buffer);
  alSourcei(pew_source,AL_LOOPING,AL_TRUE);

  alSourcei(blast_source,AL_BUFFER,blast_buffer);
  alSourcei(blast_source,AL_LOOPING,AL_FALSE);
  sources[PEW]=pew_source;
  sources[BLAST]=blast_source;
  if (sounds_on == 1)
  {
    alSourcePlay(sources[PEW]);
  }
}

void sound_player::play(int sound)
{
  if (sounds_on == 1)
  {
    switch(sound)
    {
      case BLAST:
        alSourceStop(sources[PEW]);
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
