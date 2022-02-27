//Song.c

#include "Song.h"
#include "./inc/Timer1A.h"
#include "./inc/Timer0A.h"
#include "./inc/tm4c123gh6pm.h"


/*Song loadSong(Note* music){
	
}*/

void Note_Play(Note note){
	TIMER0_TAILR_R = note.pitch;  
	TIMER1_TAILR_R = note.duration;
	TIMER0_IMR_R = 0x00000001; 
	TIMER1_IMR_R = 0x00000001; 
}


