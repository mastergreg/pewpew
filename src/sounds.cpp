/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.cpp

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Tue 15 Nov 2011 03:19:15 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/


#include "sounds.h"


sound_player::sound_player()
{
  alutInit(NULL,NULL);
  #ifdef __APPLE__
  ALsizei size, freq;
  ALenum format;
  ALvoid *data;

  alutLoadWAVFile("sounds/pew.wav", &format, &data, &size, &freq);
  alBufferData(buffers[PEW], format, data, size, freq);
  alutUnloadWAV(format,data,size,freq);

  alutLoadWAVFile("sounds/blast.wav", &format, &data, &size, &freq);
  alBufferData(buffers[BLAST], format, data, size, freq);
  alutUnloadWAV(format,data,size,freq);

  #elif __linux__ || _WIN32 || _WIN64
  buffers[PEW] = alutCreateBufferFromFile("sounds/pew.wav");
  buffers[BLAST] = alutCreateBufferFromFile("sounds/blast.wav");
  #endif


  //alGenSources(1,&source);
  alGenSources(SOUNDS,sources);

  alSourcei(sources[PEW],AL_BUFFER,buffers[PEW]);
  alSourcei(sources[PEW],AL_LOOPING,AL_FALSE);

  alSourcei(sources[BLAST],AL_BUFFER,buffers[BLAST]);
  alSourcei(sources[BLAST],AL_LOOPING,AL_FALSE);
}

void sound_player::play(int sound)
{
  if (gs.sounds_on == 1)
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
