/*
 * Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

#include <sselog.h>
#include <drTsController.h>
#include <i2c_stub.h>
#include <stringl.h>
#include "focaltech_ts.h"
#include "focaltech_ts_i2c.h"

#define MAX_NUMBER_OF_FINGERS   2
#define FT_META_REGS            3   
#define FT_ONE_TCH_LEN          6  
#define FT_TCH_LEN(x)          (FT_META_REGS + FT_ONE_TCH_LEN * x)
#define FT_TCH_LEN_TO_READ     (FT_META_REGS + FT_ONE_TCH_LEN * MAX_NUMBER_OF_FINGERS) 

#define FT_PRESS        0x7F
#define FT_MAX_ID       0x0F
#define FT_TOUCH_X_H_POS    3 
#define FT_TOUCH_X_L_POS    4 
#define FT_TOUCH_Y_H_POS    5 
#define FT_TOUCH_Y_L_POS    6  
#define FT_TD_STATUS        2  
#define FT_TOUCH_EVENT_POS  3 
#define FT_TOUCH_ID_POS     5  
#define FT_TOUCH_DOWN       0 
#define FT_TOUCH_UP         1 
#define FT_TOUCH_CONTACT    2 

#define FT_STATUS_NUM_TP_MASK   0x0F

/* register address*/
#define FT_REG_DEV_MODE     0x00  

#define MASK_8BIT           0xFF
/*Events according to the application*/
#define APP_TOUCH_EVENT_NONE  0
#define APP_TOUCH_EVENT_DOWN  1
#define APP_TOUCH_EVENT_MOVE  2
#define APP_TOUCH_EVENT_UP    4

static struct i2cFunc g_i2cFunc = {
  focaltech_i2cReadReg,
  NULL,
  focaltech_i2cOpen,
  focaltech_i2cClose
};

struct ftFingers{
  uint32_t code[MAX_NUMBER_OF_FINGERS];
  uint32_t x[MAX_NUMBER_OF_FINGERS];
  uint32_t y[MAX_NUMBER_OF_FINGERS];
};

//global variables
//To know the current state of i2c
static uint32_t i2c_opened = 0;

// local functions for reading/writing in to the register using i2c
static int32_t ftReadRegister(uint16_t address, uint8_t * buffer, uint16_t noOfBytes){
  int32_t rv = 0;
  uint8_t offset;
  LOG_D("Reading register 0x%04X, %u bytes", address, noOfBytes);
  offset  = (address & MASK_8BIT);

  // read the register
  rv = g_i2cFunc.i2cReadReg( offset,
                   buffer,
                   noOfBytes);
  return rv;
}

/*
* In this function we read the values of X and Y from
*the focaltech touch controller.
*/

static uint32_t ftReadFingers(struct ftFingers *fingers)
{
  int32_t rv = 0;
  uint32_t touchCount = 0,id ,status; /* number of touch points */
  uint8_t reg;
  int i,num_touches;
  uint8_t data[FT_TCH_LEN_TO_READ] = {0};
  struct ftFingers *buf;
  /*
   * Read touch data start from register FT_REG_DEV_MODE.
   * The touch x/y value start from FT_TOUCH_X_H/L_POS and
   * FT_TOUCH_Y_H/L_POS in buf.
   */
  reg = FT_REG_DEV_MODE;
  rv = focaltech_i2cReadReg(reg,&data,FT_TCH_LEN_TO_READ);
  if (rv) {
  LOG_E("I2C Read Error while fetching touch data from the chip %d ", rv);
  EXITV(0);
  }
  
  touchCount = data[FT_TD_STATUS] & FT_STATUS_NUM_TP_MASK;
  if(!touchCount)
  {
    return touchCount;
  }
 
  for (i = 0; i < MAX_NUMBER_OF_FINGERS; i++) {
  
    /*
    *Getting the touch ID of the finger in case of multiple touch events
    */
     id = (data[FT_TOUCH_ID_POS + FT_ONE_TCH_LEN * i])>> 4;
     if (id >= FT_MAX_ID)
     {
         break;
     } 
     fingers->x[i] = (data[FT_TOUCH_X_H_POS + FT_ONE_TCH_LEN * i] & 0x0F) << 8 |
          (data[FT_TOUCH_X_L_POS + FT_ONE_TCH_LEN * i]);
     fingers->y[i] = (data[FT_TOUCH_Y_H_POS + FT_ONE_TCH_LEN * i] & 0x0F) << 8 |
          (data[FT_TOUCH_Y_L_POS + FT_ONE_TCH_LEN * i]);

     LOG_E("Touch co-ordinates for id %d are  X %d and Y %d \r\n",id, fingers->x[i],fingers->y[i]);
     
     status = data[FT_TOUCH_EVENT_POS + FT_ONE_TCH_LEN * i] >> 6;

    /* invalid combination */
    if (!touchCount && !status && !id)
    {
         break;
    }    
     if(status == FT_TOUCH_DOWN)
     {
         fingers->code[i] = APP_TOUCH_EVENT_DOWN;
     }
     else if(status == FT_TOUCH_CONTACT)
     {
         fingers->code[i] = APP_TOUCH_EVENT_MOVE;
     }
     else if(status == FT_TOUCH_UP)
     {
         fingers->code[i] = APP_TOUCH_EVENT_UP;
     }
     else{
         fingers->code[i] = APP_TOUCH_EVENT_NONE;
     }
    
    }
   
  touchCount = data[FT_TD_STATUS] & FT_STATUS_NUM_TP_MASK;
  return touchCount;
}

uint32_t focalTech_drTsOpen(const uint32_t width, const uint32_t height)
{
  int32_t rv = 0;
  
  ENTER;
  
  do {
    rv = g_i2cFunc.i2cOpen();
    if (rv != 0) {
      LOG_E("Error opening the I2C bus: 0x%08X", rv);
      break;
    }
    LOG_E("Successfull in opening i2c bus, drtsOpen \r\n");
    i2c_opened = 1;
} while (0);

  if (i2c_opened && (rv != 0)) {
    g_i2cFunc.i2cClose();
    i2c_opened = 0;
  }
  EXITV((uint32_t)rv);
}

/** Release the I2C bus
 */
uint32_t focalTech_drTsClose(void)
{
  int32_t rv = 0;
  ENTER;
  do {
    if (!i2c_opened) {
      LOG_E("Device not opened.");
      rv = -1;
      break;
    }
    rv = g_i2cFunc.i2cClose();
    if (rv != 0) {
      LOG_E("Error closing the I2C bus: 0x%08X", rv);
      break;
    }
  } while (0);
  EXITV((uint32_t)rv);
}

/** Process all available touch events
 */
uint32_t focalTech_drTsProcessEvents(void)
{
  int32_t rv = 0;
  int32_t touchCount = 0;
  struct ftFingers fingers = {0};

  ENTER;
  do {
    if (!i2c_opened) {
      LOG_E("Device not opened.");
      rv = -1;
      break;
    }
    do {
      touchCount = ftReadFingers(&fingers);
      if (touchCount == 0) {
        LOG_E("No touch data avaliable");
        //rv = -1;
        break;
      } else {
        for (size_t i=0; i<MAX_NUMBER_OF_FINGERS; i++) {
          if (fingers.code[i] != TOUCH_EVENT_NONE) {
            drNotifyEvent(fingers.x[i], fingers.y[i], fingers.code[i], i);
          }
        }
      }
    } while (0);
    if (rv) {
      LOG_E("Failed to read data from the TS controller: 0x%08X");
      break;
    }
  } while (0);
  EXITV((uint32_t)rv);
}




