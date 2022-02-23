//Song.h
//data structure to hold a song
#include "stdint.h"
#include "stdio.h"

struct Note{
	//half note, quarter note, etc.
	uint32_t duration;
	//Do, Re, Mi, etc.
	uint32_t pitch;
};


struct Song{
	uint32_t numberNotes;
	struct Note music[];
};