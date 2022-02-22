/**
 * @file Lab5.c
 * @author your name (you@domain.com), Jonathan Valvano, Matthew Yu
 *    <TA NAME and LAB SECTION # HERE>
 * @brief
 *    An empty main file for running lab5.
 *    Feel free to edit this to match your specifications.
 *
 *    For this lab, the team must implement an audio player. The audio player
 *    must interface with (at minimum) two switches and the TLV5616 SPI DAC. The
 *    audio player must be able to play, pause, and rewind music, and should
 *    have extra functionality defined by the user in the requirements document.
 *    The LCD and other hardware may be used.
 * 
 *    Starter code includes the function definitions for the TLV5616 SPI
 *    DAC. The team must implement this driver and the driver must be written at
 *    a low level without calling TivaWare or ValvanoWare driver code. See
 *    lib/TLV5616.h for more details.
 * 
 *    The TA (Matthew) suggests the students consider the data structure design
 *    and abstractions required to play songs. What is a song? What is a note?
 *    What is a rest? How can one play chords? How can one queue songs?
 * 
 *    Other than the TLV5616 driver, this assignment is open ended, so teams
 *    must architect features of this audio player beyond the base requirements
 *    and design the relevant drivers. Feel free to use drivers made from
 *    previous labs (or build off of Lab 3 and 4). 
 * 
 *    Good luck!
 * 
 * @version 0.1
 * @date 2022-02-11 <REPLACE WITH DATE OF LAST REVISION>
 *
 * @copyright Copyright (c) 2022
 * @note Potential Pinouts:
 *    Backlight (pin 10) connected to +3.3 V
 *    MISO (pin 9) unconnected
 *    SCK (pin 8) connected to PA2 (SSI0Clk)
 *    MOSI (pin 7) connected to PA5 (SSI0Tx)
 *    TFT_CS (pin 6) connected to PA3 (SSI0Fss)
 *    CARD_CS (pin 5) unconnected
 *    Data/Command (pin 4) connected to PA6 (GPIO)
 *    RESET (pin 3) connected to PA7 (GPIO)
 *    VCC (pin 2) connected to +3.3 V
 *    Gnd (pin 1) connected to ground
 * 
 *    Center of 10k-ohm potentiometer connected to PE2/AIN1
 *    Bottom of 10k-ohm potentiometer connected to ground
 *    Top of 10k-ohm potentiometer connected to +3.3V 
 *
 *    Warning. Initial code for the RGB driver creates bright flashing lights. Remove this code
 *    and do not run if you have epilepsy.
 */

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2021

 Copyright 2022 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

/** File includes. */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

/* Register definitions. */
#include "./inc/tm4c123gh6pm.h"
/* Port F switch and LED control. */
#include "./inc/LaunchPad.h"
/* Clock delay and interrupt control. */
#include "./inc/CortexM.h"
/* External debug monitor stuff. */
#include "./inc/TExaS.h"

/* ST7735 display. */
#include "./inc/ST7735.h"
/* Add whatever else you need here! */
#include "./lib/RGB/RGB.h"


/** MMAP Pin definitions. */
#define PF0   (*((volatile uint32_t *)0x40025004)) // Left Button
#define PF1   (*((volatile uint32_t *)0x40025008)) // RED LED
#define PF2   (*((volatile uint32_t *)0x40025010)) // BLUE LED
#define PF3   (*((volatile uint32_t *)0x40025020)) // GREEN LED
#define PF4   (*((volatile uint32_t *)0x40025040)) // Right Button

int main(void) {
    DisableInterrupts();

    /* TExaS Debug modes:
       SCOPE,           // PD3
       LOGICANALYZER,   // ???
       SCOPE_PD2,       // PD2
       SCOPE_PE2,       // PE3
       SCOPE_PB5        // PB5
     */
    TExaS_Init(SCOPE);
    LaunchPad_Init();
    
    // WARNING! BRIGHT FLASHING COLORS. DO NOT RUN IF YOU HAVE EPILEPSY.
    // RGBInit();

    EnableInterrupts();
    while(1) {
        WaitForInterrupt();
    }
    return 1;
}
