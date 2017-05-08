/*
 * Arduino like DS18B20 temperature sensor very simple driver
 * Datasheet: http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 * 
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef DS18B20_H_
#define DS18B20_H_

#include <OneWire.h>

class DS18B20 {
 private:
  enum {
    FAMILY_CODE = 0x28  // DS18B20
  };

  enum {
    ROM_FAMILY_CODE = 0,
    ROM_SIZE = 8
  };

  enum {
    DATA_TEMP_LSB = 0,
    DATA_TEMP_MSB = 1,
    DATA_REG_CONFIG = 4,
    DATA_SCRATCHPAD_SIZE = 9
  };

  enum {
    REG_CONFIG_RESOLUTION_9BIT = 0x00,
    REG_CONFIG_RESOLUTION_10BIT = 0x20,
    REG_CONFIG_RESOLUTION_11BIT = 0x40,
    REG_CONFIG_RESOLUTION_MASK = 0x60
  };

  enum {
    CMD_CONVERT_T = 0x44,
    CMD_READ_SCRATCHPAD = 0xBE
  };

  // The OneWire handle
  OneWire *ow;
  // ROM-number - the 64-bit unique registration number
  // in read-only memory (ROM). If NULL - a sensor not found.
  unsigned char* rom;

 public:
  DS18B20(OneWire *one_wire);

  // Search DS18B20 sensors (max n) on a 1-Wire bus and 
  // store addresses in addr
  unsigned int search(unsigned char addr[][ROM_SIZE], const unsigned int n);
  // Search the device with ROM-number passed in addr
  bool select(const unsigned char addr[ROM_SIZE]);
  // This function reads temperature from the selected sensor
  float getTemp();
};

#endif /* DS18B20_H_ */
