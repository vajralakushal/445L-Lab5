// **************DAC_Init*********************
// Initialize 12-bit DAC 
// Input: none
// Output: none
#include <stdint.h>

void DAC_Init(uint16_t dat);


// **************DAC_Out*********************
// output to DAC
// Input: 12-bit data, 0 to (2^12)-1 
// Output: none
void DAC_Out(uint32_t code);