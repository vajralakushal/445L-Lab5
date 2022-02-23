// **************DAC_Init*********************
// Initialize 12-bit DAC 
// Input: none
// Output: none
#include <stdint.h>

void DAC_Init(void);


// **************DAC_Out*********************
// output to DAC
// Input: 12-bit data, 0 to (2^12)-1 
// Output: none
void DAC_Out(unsigned long data);