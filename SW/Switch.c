//Switch.c

#include "stdint.h"
#include "stdio.h"
#include "DAC.h"
#include "./inc/tm4c123gh6pm.h"
#include "Switch.h"
#include "math.h"
#include "Song.h"
#include "stdbool.h"
#include "./inc/Timer0A.h"
#include "./inc/Timer1A.h"



bool isPlaying;
uint32_t index;
Note OneLastTime[27] = { //TODO: Populate this
	{G0, h},
	{A0, (e+q)},
	{B0, (e+q+e)},
	{G0, e},
	{C0, q},
	{B0, q},
	{E0, (q+e)},
	{D0, e} ,
	{E0, (q+e)},
	{D0, e},
	{E0, q},
	{G0, e},
	{GF0, (e+h)},
	{G0, h},
	{A0, (e+q)},
	{B0, (e+q+e)},
	{G0, e},
	{C0, q},
	{B0, q},
	{E0, (q+e)},
	{D0, e},
	{E0, (q+e)},
	{D0, e},
	{E0, q},
	{G0, e},
	{GF0, (e+h)},
	{0,0}
};


Song song = {27, OneLastTime};

//enable Port F0 and F4 - SW1 and SW2
void EdgeCounterPortF_Init(void){                          
  SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F
  //FallingEdges = 0;            // (b) initialize counter
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  GPIO_PORTF_DIR_R |=  0x0E;    // output on PF3,2,1 
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4,0 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x1F;  //     disable alt funct on PF4,0
  GPIO_PORTF_DEN_R |= 0x1F;     //     enable digital I/O on PF4   
  GPIO_PORTF_PCTL_R &= ~0x000F000F; // configure PF4/0 as GPIO
  GPIO_PORTF_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4, PF0
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4, 0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4, 0is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4, 0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flag4, falg0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4/0*** No IME bit as mentioned in Book ***
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00200000; // (g) priority 1
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
}

void PortE_Init(void){   //initialize external button PE2
	SYSCTL_RCGCGPIO_R |= 0x10;					//turn on clock for portE
	int volatile nop;
	nop++;
//initialize falling edge interrrupt for PE1 
	GPIO_PORTE_DIR_R &= 0xFB;					//make PE2 input for external switch
	GPIO_PORTE_DEN_R |= 0x04;				//dig enable 
  GPIO_PORTE_IS_R &= ~0x04;     // (d) PE2 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x04;    //    PE2 is not both edges
  GPIO_PORTE_IEV_R &= 0xFB;    //     PE2 falling edge event
	GPIO_PORTE_ICR_R |= 0x04;      // (e) clear flag1
  GPIO_PORTE_IM_R |= 0x04;      // (f) arm interrupt on PE2
  NVIC_PRI1_R = ((NVIC_PRI1_R&0xFFFFFF00)|0x00000010); // (g) priority 1
  NVIC_EN0_R = 0x00000010;      // (h) enable interrupt 4 in NVIC
}




void SwitchInit(){
	EdgeCounterPortF_Init();
	PortE_Init();
	isPlaying = true;
	index = 0;
}


void Play(){
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;
	if(isPlaying){
		Note_Play(song.music[index]);
		TIMER1_TAILR_R = song.music[index].duration;
		index = (index + 1) & (song.numberNotes - 1);
	} else{
		Pause();
	}
}

void Pause(){
	isPlaying = false;
	DAC_Out(0);
	Timer0A_Stop();
}

void Rewind(){
	index = 0;
}

void GPIOPortF_Handler(void){
	if(GPIO_PORTF_RIS_R& 0x10){ //PF4, SW1
		GPIO_PORTF_ICR_R = 0x10;
		isPlaying = !isPlaying;
	}
	if(GPIO_PORTF_RIS_R& 0x01){ //PF0, SW2
		GPIO_PORTF_ICR_R = 0x01;
		Rewind();
	}
}