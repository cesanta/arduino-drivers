/*
 * Arduino like DS18B20 temperature sensor very simple driver
 * Datasheet: http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 * 
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include "DS18B20.h"

DS18B20::DS18B20(OneWire *one_wire)
  : ow(one_wire), rom(NULL) {
}

unsigned int DS18B20::search(unsigned char addr[][ROM_SIZE], const unsigned int n) {
  if (ow == NULL || addr == NULL || n == 0) return 0;

  unsigned int i = 0;

  // Setup the search to find the device type 'DS18B20' (0x28) if it is present
  ow->target_search(FAMILY_CODE);
  while(ow->search(addr[i]) && i < n) {
    // If no devices of the desired family are currently on the bus, 
    // then another type will be found. We should check it.
    if (addr[i][ROM_FAMILY_CODE] != FAMILY_CODE) {
      ow->reset_search();
      return 0;
    }
    i++;
  }

  return i;
}

bool DS18B20::select(const unsigned char addr[ROM_SIZE]) {
  if (ow == NULL || addr == NULL || addr[0] != FAMILY_CODE) return false;

  bool res = false;
  byte rom[ROM_SIZE];

  DS18B20::rom = NULL;

  // Setup the search to find the device type 'DS18B20' (0x28) if it is present
  ow->target_search(FAMILY_CODE);
  while(ow->search(rom)) {
    // If no devices of the desired family are currently on the bus, 
    // then another type will be found. We should check it.
    if (rom[ROM_FAMILY_CODE] != FAMILY_CODE) {
      ow->reset_search();
      return false;
    }
    res = true;
    for (int i = 0; i < ROM_SIZE; i++) {
      if (addr[i] != rom[i]) {
        res = false;
        break;
      }
    }
    if (res) break; // Sensor found
  }

  // Store ROM
  if (res) DS18B20::rom = (unsigned char *)addr;

  return res;
}

float DS18B20::getTemp() {
  if (ow == NULL || rom == NULL) return -127;

  byte data[DATA_SCRATCHPAD_SIZE];
  int16_t raw;
  byte cfg;

  ow->reset();
  ow->select(rom);
  ow->write(CMD_CONVERT_T);

  delay(750);

  ow->reset();
  ow->select(rom);    
  ow->write(CMD_READ_SCRATCHPAD);

  for (int i=0; i<DATA_SCRATCHPAD_SIZE; i++) data[i] = ow->read();

  raw = (data[DATA_TEMP_MSB] << 8) | data[DATA_TEMP_LSB];
  cfg = (data[DATA_REG_CONFIG] & REG_CONFIG_RESOLUTION_MASK);
  
  if (cfg == REG_CONFIG_RESOLUTION_9BIT) raw = raw & ~7;
  else if (cfg == REG_CONFIG_RESOLUTION_10BIT) raw = raw & ~3;
  else if (cfg == REG_CONFIG_RESOLUTION_11BIT) raw = raw & ~1;
  // Default resolution is 12 bit

  return (float)raw / 16.0;
}
