//Song.c

#include "Song.h"
#include "./inc/Timer1A.h"
#include "./inc/Timer0A.h"
#include "./inc/tm4c123gh6pm.h"
#include "DAC.h"



/*Song loadSong(Note* music){
	
}*/

uint32_t Index = 0;
uint32_t pitch;
uint32_t length;

void Note_Play(Note note){
	pitch = 2500000/note.pitch;
	length = note.duration;
	Index = 0; //start  from beginning of sine wave
	Timer0A_Init(&PitchHandler, pitch, 1);
}

const int SineWave[32] = {
  2048,
  2447,
  2831,
  3185,
  3495,
  3750,
  3939,
  4056,
  4095,
  4056,
  3939,
  3750,
  3495,
  3185,
  2831,
  2447,
  2048,
  1648,
  1264,
  910,
  600,
  345,
  156,
  39,
  0,
  39,
  156,
  345,
  600,
  910,
  1264,
  1648
};



void PitchHandler(void){
	DAC_Out(SineWave[Index]);    // output one value each interrupt
	Index = (Index+1)%32;      // 4,5,6,7,7,7,6,5,4,3,2,1,1,1,2,3,... 
}




