/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : sounds.cpp

* Purpose :

* Creation Date : 23-10-2011

* Last Modified : Tue 15 Nov 2011 01:31:24 PM EET

* Created By : Greg Liras <gregliras@gmail.com>

_._._._._._._._._._._._._._._._._._._._._.*/


#include "sounds.h"
unsigned int myAlutCreateBufferFromFile(ALbyte *filename)
{
  unsigned int buffer;
  ALsizei size, freq;
  ALenum format;
  ALvoid *data;
  alutLoadWAVFile(filename, &format, &data, &size, &freq);
  alBufferData(buffer, format, data, size, freq);
  alutUnloadWAV(format, data, size, freq);
  return buffer;
}
sound_player::sound_player()
{
  alutInit(NULL,NULL);

  buffers[PEW] = myAlutCreateBufferFromFile((ALbyte*)"sounds/pew.wav");
  buffers[BLAST] = myAlutCreateBufferFromFile((ALbyte*)"sounds/blast.wav");

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
