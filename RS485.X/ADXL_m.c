#include "ADXL_m.h"
#include "ADXL_cfg.h"
#include "system.h"

void I2C_IDLE(void);

void ACC_vidInit(void)
{
    I2C_Master_Init();
    
    I2C_Start();
    I2C_Write(ACCEL_ADDRESS);
    I2C_Write(0x0D);
    I2C_Write(0x08);
    I2C_Stop();

    I2C_Start();
    I2C_Write(ACCEL_ADDRESS);
    I2C_Write(0x31);
    I2C_Write(0x08);
    I2C_Stop();

    I2C_Start();
    I2C_Write(ACCEL_ADDRESS);
    I2C_Write(0x0C);
    I2C_Write(0x09);
    I2C_Stop();
}


void I2C_IDLE(void)
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Init(void)
{
    SSPCON = 0x28;  // enable I2C pins SCL and SDA for serial communication
    SSPCON2 = 0x00; 
    SSPSTAT = 0x80;  //slew rate enables for high speed control
    SSPADD = ((_XTAL_FREQ/4)/I2C_SPEED) - 1;
    TRISC3 = 1;  //Set as a digital input 
    TRISC4 = 1;  //Set as a digital input 
}

void I2C_Start(void)
{
    I2C_IDLE();
    SSPCON2bits.SEN = 1;  // initial start condition on SDA line
}

void I2C_Stop(void)
{
    I2C_IDLE();
    SSPCON2bits.PEN = 1; // Initiate Stop condition on SDA and SCL pins
}

void I2C_Restart(void)
{
    I2C_IDLE();
    SSPCON2bits.RSEN = 1; // Initiate Repeated Start condition on SDA and SCL pins.
}

void I2C_ACK(void)
{
    I2C_IDLE();
    SSPCON2bits.ACKDT = 0; //Acknowledge Data bit  
    SSPCON2bits.ACKEN = 1;  // Acknowledge Sequence Enable bit(
}
void I2C_NACK(void)
{
    I2C_IDLE();
    SSPCON2bits.ACKDT = 1; 
    SSPCON2bits.ACKEN = 1; 
}

unsigned char I2C_Write(unsigned char Data)
{
    I2C_IDLE();   // wait untill I2C_Bus of PIC18F4550 microcontroller becomes free 
    SSPBUF = Data; // store data inside SSPBUF register of PIC18F4550 microcontroller
    I2C_Wait();  
    return ACKSTAT; //return status of data or address transmission
}

unsigned char I2C_Read_Byte(void)
{
    SSPCON2bits.RCEN = 1; // Enable & Start Reception
    while(!SSPIF); // Wait Until Completion
    SSPIF = 0; // Clear The Interrupt Flag Bit
    return SSPBUF; // Return The Received Byte
}

void I2C_Wait(void)
{
    while(!SSPIF);
    SSPIF = 0;
}