/* 
 * File:   ADXL_cfg.h
 * Author: khalid
 *
 * Created on May 15, 2020, 2:17 PM
 */
#ifndef ADXL_CFG_H
#define	ADXL_CFG_H
#include "system.h"

#define ACCEL_ADDRESS  0xA6 
/***************zone Accelemoter************/
#define ADD_X_LOW         0x32
#define ADD_X_HIG         0x33
#define ADD_Y_LOW         0x34
#define ADD_Y_HIG         0x35
#define ADD_Z_LOW         0x36
#define ADD_Z_HIG         0x37

#define ADD_POWER_CTL      0x2D
#define ADD_DATA_FORMAT    0x31
#define ADD_BW_RATE        0x2C


#define I2C_SPEED          100000


#endif	/* ADXL_CFG_H */

