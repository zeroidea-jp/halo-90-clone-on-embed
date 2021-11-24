/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

// #include "DigitalInOut.h"
#include "mbed.h"

// Prototypes
//uint16_t readMic();
void setLed(uint8_t led);
void ledHigh(uint8_t led);
void ledLow(uint8_t led);

// Global previousLed
volatile uint8_t prevLed = 0; // originally 0, in halo-90.c
//int8_t rotationCenter = 45;
//int8_t rotDir = 1;
volatile uint8_t patternNum = 0;
//volatile uint8_t sleep = 0;

// Values & Functions for Test Environment
void led_pattern_handler(uint8_t patternNum) ;
void button_handler();
uint8_t colMax = 5;
uint8_t rowMax = colMax - 1;
uint8_t lMax = colMax * rowMax;

#define WAIT_TIME_MS 20

DigitalInOut pin0(ARDUINO_UNO_A0);
DigitalInOut pin1(ARDUINO_UNO_A1);
DigitalInOut pin2(ARDUINO_UNO_A2);
DigitalInOut pin3(ARDUINO_UNO_A3);
DigitalInOut pin4(ARDUINO_UNO_A4);
// DigitalInOut pin5(ARDUINO_UNO_A5);

DigitalInOut* p_pN[] = {
    &pin0,
    &pin1,
    &pin2,
    &pin3,
    &pin4
}; 

// DigitalOut led1(LED1);
InterruptIn tactile0(BUTTON1);
InterruptIn tactile1(ARDUINO_UNO_D0);
// InterruptIn* tactile[]{
//     &tactile0, 
//     &tactile1
// };


int main()
{

    printf("This is the bare metal charlieplexing example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    tactile0.rise(&button_handler);
    tactile1.rise(&button_handler);
    while (true)
    {
        // led1 = tactile0;
        // uint8_t led;
        // for(led = 0; led < lMax; led ++){
        //     setLed(led);
        //     thread_sleep_for(WAIT_TIME_MS);
        // }
        led_pattern_handler(patternNum);

    }
}


void button_handler(){
    patternNum = (patternNum + 1 )%2;
}

void led_pattern_handler(uint8_t patternNum) {
    switch(patternNum){
    case 0:
      // Halo
        setLed((prevLed + 13)%lMax); // 13 for 90 LEDs. c.f. 13x7 = 91.
    break;

    case 1:
      // Sparkle
        rand()%15 ? ledLow(prevLed) : setLed(rand() % lMax);
        thread_sleep_for(WAIT_TIME_MS); // use when led_pattern = 2 (Sparkle)
    break;

    default:
    break;
  }
}

void setLed(uint8_t led){
  ledLow(prevLed);
  ledHigh(led);
  prevLed = led;
}

void ledHigh(uint8_t led){
    // printf("LedHigh Setting... at LED = %d)\n", led);

    uint8_t col = led / rowMax;
    uint8_t topElements = rowMax - col;
    uint8_t row = rowMax - (led % rowMax); // to fit the LED number defined on the halo-90.kicad_sch
    if (topElements <= (rowMax - row)) {
        row--; // to shift the coordinate, where no LED exist (at row == col), to the next row
    }
    // printf("Corresponding pins numbers are (row,col) = (%d,%d)\n", row,col);

    (*p_pN[col]).output();
    *p_pN[col] = 1; 
    (*p_pN[row]).output();   
    *p_pN[row] = 0;        
}

void ledLow(uint8_t led){
    // printf("LedHigh Setting... at LED = %d)\n", led);
    uint8_t col = led / rowMax;
    uint8_t topElements = rowMax - col;
    uint8_t row = rowMax - (led % rowMax); // to fit the LED number defined on the halo-90.kicad_sch
    if (topElements <= (rowMax - row)) {
        row--; // to shift the coordinate, where no LED exist (at row == col), to the next row
    }
    // printf("Corresponding pins numbers are (row,col) = (%d,%d)\n", row,col);

    (*p_pN[col]).input();
    (*p_pN[row]).input();      

}

