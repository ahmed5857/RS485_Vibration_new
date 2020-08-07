/*
 * File:   main.c
 * Author: khalid
 *
 * Created on May 10, 2020, 12:32 PM
 */
#include "system.h"
#include "UART_m.h"

void system_init(void);


void main(void) 
{
    system_init();
    UART_vidInit();

    while(1)
    {
        Set_X_DataIntoBuffer(0x55);
        Set_Y_DataIntoBuffer(0xAA);
        Set_Z_DataIntoBuffer(0x88);
        Set_T_DataIntoBuffer(0x66);
        Set_SwitchStatus_DataIntoBuffer(1);
        Set_ID_DataIntoBuffer(0x35);
        Set_AVG_Vibration_DataIntoBuffer(0x30);
    }
}

void system_init(void)
{
    TRISC0 = 0;
    TRISA = 0xFF;
    ADCON0 = 0x00;
    ANSEL = 0x00;
}
