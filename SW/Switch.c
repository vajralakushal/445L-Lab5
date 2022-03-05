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
Note OneLastTime[26] = { //TODO: Populate this
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
	//{0,0}
};


Note DangerousWoman[44] = { 						//declare prototype for variable 
	{D0, q},
	{E0, q},
	{G0, q},
	{E0, (h+q)},
	{A0, h},
	{G0, q},
	{A0, q},
	{A0, q},
	{G0, q},
	{BF0, q},
	{A0, q},
	{G0, q},
	{A0, q},
	{G0, (e+h)},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{G0, q},
	{E0, (h+q)},
	{A0, h},
	{G0, q},
	{A0, q},
	{A0, q},
	{G0, q},
	{BF0, q},
	{A0, q},
	{G0, q},
	{A0, q},
	{G0, (e+h)},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{G0, q},
	{E0, w},
	//{0,0}
};

Song oneLastTime = {26, OneLastTime};
Song dangerousWoman = {44, DangerousWoman};

//enable Port F0 and F4 - SW1 and SW2
void EdgeCounterPortF_Init(void){                          
  volatile int delay;       
  SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F
  delay = 0;             // (b) initialize count and wait for clock
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AMSEL_R &= ~0x11;
	GPIO_PORTF_PCTL_R &= ~0x000F000F;
	GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4 + PF0 in (built-in button)
	GPIO_PORTF_AFSEL_R &= ~0x11;
  GPIO_PORTF_DEN_R |= 0x11;     //     enable digital I/O on PF4 + PF0 
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4 + PF0 
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4 + PF0  is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4 + PF0  is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4 + PF0  falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flag4 + flag0 
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4 + PF0 
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
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


void Play(void){
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;
	if(isPlaying){
		if(dangerousWoman.music[index].duration == 0){ //if end of dangerousWoman
			Timer0A_Stop();
			Timer1A_Stop();
			DAC_Out(0);
			isPlaying = 0;
		}else{
			Note_Play(dangerousWoman.music[index]); //pass info about pitch to timer0
			TIMER1_TAILR_R = dangerousWoman.music[index].duration; //pass new duration	
			index = (index + 1) % dangerousWoman.numberNotes;
		}
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
	Timer1A_Init(&Play, 80000000, 4);
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