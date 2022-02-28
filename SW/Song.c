//Song.c

#include "Song.h"
#include "./inc/Timer1A.h"
#include "./inc/Timer0A.h"
#include "./inc/tm4c123gh6pm.h"




/*Song loadSong(Note* music){
	
}*/


uint32_t pitch;
uint32_t length;
void Note_Play(Note note){
	 pitch = note.pitch;
	length = note.duration;
	TIMER0_TAILR_R = pitch;  
	TIMER1_TAILR_R = note.duration;
	TIMER0_IMR_R = 0x00000001; 
	TIMER1_IMR_R = 0x00000001; 
}


