/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino Adafruit_BME280 library API wrapper
 */

#include <math.h>
#include "mgos_arduino_bme280.h"

Adafruit_BME280 *mgos_bme280_create() {
  return new Adafruit_BME280();
}

void mgos_bme280_close(Adafruit_BME280 *bme) {
  if (bme != nullptr) {
    delete bme;
    bme = nullptr;
  }
}

int mgos_bme280_begin(Adafruit_BME280 *bme, int addr) {
  if (bme == nullptr) return 0;
  return bme->begin(addr);
}

void mgos_bme280_take_forced_measurement(Adafruit_BME280 *bme) {
  if (bme == nullptr) return;
  bme->takeForcedMeasurement();
}

int mgos_bme280_read_temperature(Adafruit_BME280 *bme) {
  if (bme == nullptr) return MGOS_BME280_RES_FAIL;
  return round(bme->readTemperature() * 100.0);
}

int mgos_bme280_read_pressure(Adafruit_BME280 *bme) {
  if (bme == nullptr) return MGOS_BME280_RES_FAIL;
  return round(bme->readPressure() * 100.0);
}

int mgos_bme280_read_humidity(Adafruit_BME280 *bme) {
  if (bme == nullptr) return MGOS_BME280_RES_FAIL;
  return round(bme->readHumidity() * 100.0);
}
        
int mgos_bme280_read_altitude(Adafruit_BME280 *bme, int seaLevel) {
  if (bme == nullptr) return MGOS_BME280_RES_FAIL;
  return round(bme->readAltitude(seaLevel / 100.0) * 100.0);
}

int mgos_bme280_sea_level_for_altitude(Adafruit_BME280 *bme, 
                                       int altitude,
                                       int pressure) {
  if (bme == nullptr) return MGOS_BME280_RES_FAIL;
  return round(bme->seaLevelForAltitude(altitude / 100.0, pressure / 100.0) * 100.0);
}
