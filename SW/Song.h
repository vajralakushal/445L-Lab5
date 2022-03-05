//Song.h
//data structure to hold a song
#include "stdint.h"
#include "stdio.h"

// define note lengths and qualities 
#define bus 200000000
//#define bus 	80000000
#define q (bus/4)
#define h (q*2)
#define w (q*4)
#define e (q/2)
#define s (q/4) 
#define g (q/10)
#define Q 0xFFFFFF				//4.7 Hz

// octave definitions
// period is halved since we went from 32-64 sine wave
#define C0  2389   // 523.3 Hz	
#define B0  2531   // 493.9 Hz	
#define BF0 2681   // 466.2 Hz	
#define A0  2841   // 440 Hz	
#define AF0 3010   // 415.3 Hz	
#define G0  3189  // 392 Hz	
#define GF0 3378   // 370 Hz	
#define F0  3579   // 349.2 Hz	
#define E0  3729   // 329.6 Hz	
#define EF0 4018   // 311.1 Hz	
#define D0  4257  // 293.7 Hz	
#define DF0 4510   // 277.2 Hz	
#define C7  4778   // 261.6 Hz	


typedef struct Note{
	//half note, quarter note, etc.
	//this is basically the period
	
	//Do, Re, Mi, etc. This will be the period reload values
	uint32_t pitch;
	uint32_t duration;
} Note;


typedef struct Song{
	uint32_t numberNotes;
	Note *music;
} Song;


//loads the song into 
Song loadSong(Note* music);

void Note_Play(Note note);

void SongInit();

void PitchHandler(void);