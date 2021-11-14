/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "DigitalInOut.h"
#include "mbed.h"

#define WAIT_TIME_MS 500 
DigitalOut led1(LED1);

DigitalInOut pin1(ARDUINO_UNO_A0);
DigitalInOut pin2(ARDUINO_UNO_A1);
DigitalInOut pin3(ARDUINO_UNO_A2);


int main()
{
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        led1 = !led1;

       
        pin1.output();
        pin1 = 1;
        pin3.output();
        pin3 = 0;
        pin2.input();

        thread_sleep_for(WAIT_TIME_MS);
        
        pin3.output();
        pin3 = 1;
        pin1.output();
        pin1 = 0;
        pin2.input();

        thread_sleep_for(WAIT_TIME_MS);

        pin3.output();
        pin3 = 1;
        pin2.output();
        pin2 = 0;
        pin1.input(); 

        thread_sleep_for(WAIT_TIME_MS);
        
        pin2.output();
        pin2 = 1;
        pin3.output();
        pin3 = 0;
        pin1.input();

        thread_sleep_for(WAIT_TIME_MS);   

        pin2.output();
        pin2 = 1;
        pin1.output();
        pin1 = 0;
        pin3.input();

        thread_sleep_for(WAIT_TIME_MS);
        
        pin1.output();
        pin1 = 1;
        pin2.output();
        pin2 = 0;
        pin3.input();
        
        thread_sleep_for(WAIT_TIME_MS);
    }
}

