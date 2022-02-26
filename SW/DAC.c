//DAC.c

#include "stdint.h"
#include "stdio.h"
#include "DAC.h"
#include "./inc/tm4c123gh6pm.h"

const unsigned short wave[32] = {
  8,9,11,12,13,14,14,15,15,15,14,
  14,13,12,11,9,8,7,5,4,3,2,
  2,1,1,1,2,2,3,4,5,7};

unsigned long Index;


void DAC_Init(void){

}



//outputs to the DAC
void DAC_Out(unsigned long data){
	GPIO_PORTD_DATA_R = data;
}