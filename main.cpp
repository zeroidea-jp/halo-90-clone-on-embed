/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "DigitalInOut.h"
#include "mbed.h"

#define WAIT_TIME_MS 1000

// Prototypes
//uint16_t readMic();
void setLed(uint8_t led);
void ledHigh(uint8_t led);
void ledLow(uint8_t led);

// Global previousLed
volatile uint8_t prevLed = 1; // originally 0, in halo-90.c
//int8_t rotationCenter = 45;
//int8_t rotDir = 1;
volatile uint8_t patternNum = 0;
//volatile uint8_t sleep = 0;

// Values & Functions for Test Environment
void ledHighTest2(uint8_t led);
void ledLowTest2(uint8_t led);

// void led_pattern_handler(uint8_t patternNum);
uint8_t led = 0;
uint8_t rowMax = 5 ;
uint8_t colMax = rowMax -1;
uint8_t lMax = colMax * rowMax;


DigitalOut led1(LED1);

DigitalInOut pin0(ARDUINO_UNO_A0);
DigitalInOut pin1(ARDUINO_UNO_A1);
DigitalInOut pin2(ARDUINO_UNO_A2);
DigitalInOut pin3(ARDUINO_UNO_A3);
DigitalInOut pin4(ARDUINO_UNO_A4);
DigitalInOut pin5(ARDUINO_UNO_A5);

DigitalInOut* p_pN[] = {
    &pin0,
    &pin1,
    &pin2,
    &pin3,
    &pin4,
    &pin5
};


// DigitalInOut* p_ph = &pinHigh;
// DigitalInOut* p_pl = &pinLow;

int main()
{
    // printf("print pointer of object1: %d\n", p_pN[0]);
    // printf("print pointer of object2: %d\n", p_pN[1]);
    // printf("print pointer of object3: %d\n", p_pN[2]);
    // printf("print pointer of object3: %d\n", p_pN[3]);
    // printf("print pointer of object4: %d\n", p_pN[4]);

    printf("This is the bare metal charlieplexing example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
 
    while (true)
    {
        led1 = !led1;
        
        uint8_t led;
        for(led = 0; led < lMax; led ++){
            setLed(led);
            thread_sleep_for(WAIT_TIME_MS);
        }
        //led_pattern_handler(patternNum);

    }
}

void led_pattern_handler(uint8_t patternNum) {
    switch(patternNum){
    case 1:
      // Halo
      setLed((prevLed + 13)%90);
    break;

    case 2:
      // Sparkle
      rand()%15 ? ledLow(prevLed) : setLed(rand() % 90);
    break;

    default:
    break;
  }
}

void setLed(uint8_t led){
  ledLowTest2(prevLed);
  ledHighTest2(led);
  prevLed = led;
}

void ledHighTest2(uint8_t led){
    printf("LedHigh Setting... at LED = %d)\n", led);

    uint8_t col = led / colMax;
    uint8_t topElements = colMax - col;
    uint8_t row = colMax - (led % colMax); // to fit the LED number defined on the halo-90.kicad_sch
    if (topElements <= (colMax - row)) {
        row--; // to shift the coordinate, where no LED exist (at row == col), to the next row
    }
    printf("Corresponding pins numbers are (row,col) = (%d,%d)\n", row,col);

    (*p_pN[col]).output();
    *p_pN[col] = 1; 
    (*p_pN[row]).output();   
    *p_pN[row] = 0;        
}

void ledLowTest2(uint8_t led){
    printf("LedHigh Setting... at LED = %d)\n", led);
    uint8_t col = led / colMax;
    uint8_t topElements = colMax - col;
    uint8_t row = colMax - (led % colMax); // to fit the LED number defined on the halo-90.kicad_sch
    if (topElements <= (colMax - row)) {
        row--; // to shift the coordinate, where no LED exist (at row == col), to the next row
    }
    printf("Corresponding pins numbers are (row,col) = (%d,%d)\n", row,col);

    (*p_pN[col]).input();
    (*p_pN[row]).input();      

}


// Enable a specific LED
void ledHigh(uint8_t led) {
//   uint8_t col = led / colMax;
//   uint8_t topElements = colMax - col;
//   uint8_t row = colMax - (led % colMax);
//   if (topElements <= (colMax - row)) {
//     row--;
//   }

  // Set column HIGH

//  CPX_PORT[col]->DDR.byte |= CPX_PIN[col];
//  CPX_PORT[col]->CR1.byte |= CPX_PIN[col];
//  CPX_PORT[col]->ODR.byte |= CPX_PIN[col];
  // Set row LOW
//  CPX_PORT[row]->DDR.byte |= CPX_PIN[row];
//  CPX_PORT[row]->CR1.byte |= CPX_PIN[row];
//  CPX_PORT[row]->ODR.byte &= ~CPX_PIN[row];
}


// Disable a specific LED
void ledLow(uint8_t led) {
//   uint8_t col = led / colMax;
//   uint8_t topElements = colMax - col;
//   uint8_t row = colMax - (led % colMax);
//   if (topElements <= (colMax - row)) {
//     row--;
//   }

  // Set row to HI-Z
//  CPX_PORT[row]->ODR.byte |= CPX_PIN[row];
//  CPX_PORT[row]->DDR.byte &= ~CPX_PIN[row];
//  CPX_PORT[row]->CR1.byte &= ~CPX_PIN[row];
  // Set column to HI-Z
//  CPX_PORT[col]->ODR.byte &= ~CPX_PIN[col];
//  CPX_PORT[col]->DDR.byte &= ~CPX_PIN[col];
//  CPX_PORT[col]->CR1.byte &= ~CPX_PIN[col];
}