//Song.h
//data structure to hold a song
#include "stdint.h"
#include "stdio.h"

typedef struct Note{
	//half note, quarter note, etc.
	//this is basically the period
	uint32_t duration;
	//Do, Re, Mi, etc. This will be the period reload values
	uint32_t pitch;
} Note;


typedef struct Song{
	uint32_t numberNotes;
	Note music[];
} Song;


//loads the song into 
Song loadSong(Note* music);

void Note_Play(Note note);