/*
 * File:   main.c
 * Author: khalid
 *
 * Created on May 10, 2020, 12:32 PM
 */
#include "system.h"
#include "UART_m.h"
#include "ADXL_m.h"
#include "average_calculations.h"
//#include <stdio.h>
//#include <xc.h>
//#include <stdlib.h>


void UART_Write(unsigned char data)
{
  while(!TRMT);
  TXREG = data;
}

void UART_Write_String(char* buf)
{
    int i=0;
    while(buf[i] != '\0')
        UART_Write(buf[i++]);
}



void system_init(void)
{
    TRISC0 = 0;
    TRISA = 0xFF;
    ADCON0 = 0x00;
    ANSEL = 0x00;
}


void main(void) 
{
    int id, pow, bw_rate;
    signed long x,y,z;
    signed long xhi,xlo,yhi,ylo,zhi,zlo;
    signed long Xaccumulate, Yaccumulate, Zaccumulate;
    unsigned char Xaverage, Yaverage, Zaverage;
    int i;
    
   /* char buffer[40];
    int Ax,Ay,Az,T,Gx,Gy,Gz;
    float AX, AY, AZ, t, GX, GY, GZ;
    sprintf(buffer,"Ax = %f \t",AX);
    */
    
    
   
    system_init();
    UART_vidInit();
    
    // Initialize I2C Port
    I2CInit();
    // Initialize ADXL345 Accelerometer
    ini_adxl345();
    
    id = E_Read(IDDV);  // should be 229 for ADXL1345
    UART_Write(id);
    __delay_ms(10);
    pow = E_Read(0x2D);  //should be 8 to activate
    UART_Write(pow);
    __delay_ms(10);
    bw_rate = E_Read(0x2C);  //BW_RATE 0x2C is 13
    UART_Write(bw_rate);
    
    
    while(1)
    {
            Xaccumulate = Yaccumulate = Zaccumulate = 0;
        
        
        
            I2CStart();
            I2CSend(CHIP_Write);
            I2CSend(DATAX0);    // DATAX0 is the first of 6 bytes
            I2CRestart();
            I2CSend(CHIP_Read);                            //
            xlo = I2CRead();                                // read character
            I2CAck();
            xhi = I2CRead();                                // read character
            I2CAck();
            ylo = I2CRead();                                // read character
            I2CAck();
            yhi = I2CRead();                                // read character
            I2CAck();
            zlo = I2CRead();                                // read character
            I2CAck();
            zhi = I2CRead();                                // read character
            I2CNak();
            I2CStop();
 
 
            Xaccumulate += ((xhi<<8) | xlo); //Xaccumulate = Xaccumulate + (xhi*256 + xlo)
            Yaccumulate += ((yhi<<8) | ylo);
            Zaccumulate += ((zhi<<8) | zlo);
        
        
        
            Xaverage =  get_x_average(Xaccumulate);
            Yaverage =  get_y_average(Yaccumulate);
            Zaverage =  get_z_average(Zaccumulate);
            
           /* itoa(Xaccumulate,buffer,10);   // here 10 means decimal
            UART_Write_String(buffer);
            */
            
           // UART_Write(48+500);
        
        
        
        Set_X_DataIntoBuffer(Xaccumulate)
        Set_Y_DataIntoBuffer(Yaccumulate);
        Set_Z_DataIntoBuffer(Zaccumulate);
        Set_T_DataIntoBuffer(0x66);
        Set_SwitchStatus_DataIntoBuffer(1);
        Set_ID_DataIntoBuffer(0x35);
        Set_AVG_Vibration_DataIntoBuffer(0x30);
    }
}



