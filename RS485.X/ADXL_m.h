/* 
 * File:   ADXL_m.h
 * Author: khalid
 *
 * Created on May 15, 2020, 2:17 PM
 */

#ifndef ADXL_M_H
#define	ADXL_M_H

#include "ADXL_cfg.h"

void ACC_vidInit(void);

void I2C_Master_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Wait(void);
unsigned char I2C_Write(unsigned char Data);
unsigned char I2C_Read_Byte(void);


#endif	/* ADXL_M_H */

