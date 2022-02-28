//Switch.h

#include "stdint.h"
#include "stdio.h"

//initializes Switches on Port F
void SwitchInit();

//plays audio
void Play(void);

//rewinds audio to beginning
void Rewind();

//pauses audio
void Pause();