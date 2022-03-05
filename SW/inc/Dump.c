/**
 * @file Dump.c
 * @author Reva Vaidya (you@domain.com), Jonathan Valvano, Matthew Yu
 *    <TA NAME and LAB SECTION # HERE>
 * @brief 
 *    A set of debugging functions that capture data for later inspection.
 *    There are two primary methods:
 *       - DebugCapture will record data and time.
 *       - JitterMeasure will measure real time jitter.
 * @version 0.1
 * @date 2022- 02 - 02
 *
 * @copyright Copyright (c) 2022
 */

/** File includes. */
#include <stdint.h>
#include "../inc/Dump.h"
#include "../inc/tm4c123gh6pm.h"

// Global variables
uint32_t DumpTimeBuffer[DUMPBUFSIZE];
uint32_t DumpDataBuf[DUMPBUFSIZE];
uint32_t JitterBuf[DUMPBUFSIZE];
uint32_t DeltaI;
uint32_t prevTime; 
uint32_t CurrTime; //testing for deliverable 5
uint32_t DumpNum;
uint32_t MaxDeltaI;
uint32_t MinDeltaI;
uint32_t firstCall;

void Timer1_Init(void) {
    volatile uint32_t delay;
    SYSCTL_RCGCTIMER_R    |= 0x02;                // 0) activate TIMER1
    delay                  = SYSCTL_RCGCTIMER_R;  // allow time to finish activating
    TIMER1_CTL_R           = 0x00000000;          // 1) disable TIMER1A during setup
    TIMER1_CFG_R           = 0x00000000;          // 2) configure for 32-bit mode
    TIMER1_TAMR_R          = 0x00000002;          // 3) configure for periodic mode, default down-count settings
    TIMER1_TAILR_R         = 0xFFFFFFFF;          // 4) reload value
    TIMER1_TAPR_R          = 0;                   // 5) bus clock resolution
    TIMER1_CTL_R           = 0x00000001;          // 10) enable TIMER1A
}


void DumpInit(void){
    /* TODO (EE445L Lab 2): complete this. */
	DumpNum = 0; //initialize number of elem in arrary to 0
	//Timer1_Init();//call Timer1_Init here instead of JitterInit - RV
}

void DumpCapture(uint32_t data){
    /* TODO (EE445L Lab 2): complete this. */
    // Use TIMER1_TAR_R as current time
	if(DumpNum < DUMPBUFSIZE){  //if room, increment to next loc - RV
		DumpTimeBuffer[DumpNum] = TIMER0_TAR_R;  //dump time
		DumpDataBuf[DumpNum] = data; //dump data
		DumpNum++; 
	}
}

uint32_t DumpCount(void){ 
    /* TODO (EE445L Lab 2): complete this. */
    return DumpNum; //return how many elem in array
}

uint32_t* DumpData(void){ 
    return DumpDataBuf;  //look at dump data
}

uint32_t* DumpTime(void){ 
    return DumpTimeBuffer; //look at dump times
}

void JitterInit(void){
    /* TODO (EE445L Lab 2): complete this. */
	//initialzie Globals 
	MinDeltaI = 0;
	MaxDeltaI = 0;
	firstCall = 1;
}

void JitterMeasure(void){
    /* TODO (EE445L Lab 2): complete this. */
	if (firstCall == 1){
		DeltaI = TIMER0_TAR_R;  //if first call, jitter  = timer1
		prevTime = DeltaI; 
		MinDeltaI = DeltaI; //set min to first call jitter 
		firstCall = 0;
	}else{
		CurrTime = TIMER1_TAR_R;
		DeltaI = prevTime - CurrTime; //jitter = prev - current time b/c count down 
		prevTime = CurrTime;  //set prev time to current time - RV
		//check to see if this should be moved to out - RV
		if(MaxDeltaI < DeltaI){  //see if new jitter min/max 
			MaxDeltaI = DeltaI;
		}	
		if(MinDeltaI > DeltaI){
			MinDeltaI = DeltaI;
		}
	}
	/*if(DumpNum == 0){
		JitterBuf[DumpNum] = DumpTimeBuffer[DumpNum];
		
	} else{
		JitterBuf[DumpNum] = DumpTimeBuffer[DumpNum] - DumpTimeBuffer[DumpNum - 1];
	}*/
	
}

uint32_t JitterGet(void){
    /* TODO (EE445L Lab 2): complete this. */
	/*	for(uint32_t i = 0; i < DumpNum; i++){
			uint32_t DeltaI = JitterBuf[i];
			if(MaxDeltaI < DeltaI){
				MaxDeltaI = DeltaI;
			}
		
			if(MinDeltaI > DeltaI){
				MinDeltaI = DeltaI;
			}
		}*/
    return MaxDeltaI - MinDeltaI;
}




