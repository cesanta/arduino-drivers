/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino Adafruit_BME280 library API wrapper
 */

#include "Adafruit_BME280.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MGOS_BME280_RES_FAIL -10000

// Initialize Adafruit_BME280 library.
// Return value: OneWire handle opaque pointer.
Adafruit_BME280 *mgos_bme280_init();

// Close Adafruit_BME280 handle. Return value: none.
void mgos_bme280_close(Adafruit_BME280 *bme);

// Initialize the sensor with given parameters/settings.
// Returns 0 if the sensor not plugged or a checking failed,
// i.e. the chip ID is incorrect.
// Returns 1 otherwise.
int mgos_bme280_begin(Adafruit_BME280 *bme, uint8_t addr);

// Take a new measurement (only possible in forced mode).
void mgos_bme280_take_forced_measurement(Adafruit_BME280 *bme);

// Returns the temperature from the sensor in degrees C * 100
// or MGOS_BME280_RES_FAIL if an operation failed.
int mgos_bme280_read_temperature(Adafruit_BME280 *bme);

// Returns the pressure from the sensor in hPa * 100
// or MGOS_BME280_RES_FAIL if an operation failed.
int mgos_bme280_read_pressure(Adafruit_BME280 *bme);

// Returns the humidity from the sensor in %RH * 100
// or MGOS_BME280_RES_FAIL if an operation failed.
int mgos_bme280_read_humidity(Adafruit_BME280 *bme);

// Returns the altitude in meters * 100 calculated from the specified
// atmospheric pressure (in hPa), and sea-level pressure (in hPa * 100)
// or MGOS_BME280_RES_FAIL if an operation failed.
// http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf, P.16
int mgos_bme280_read_altitude(Adafruit_BME280 *bme, int seaLevel);

// Returns the pressure at sea level in hPa * 100
// calculated from the specified altitude (in meters * 100),
// and atmospheric pressure (in hPa * 100)
// or MGOS_BME280_RES_FAIL if an operation failed.
// http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf, P.17
int mgos_bme280_sea_level_for_altitude(Adafruit_BME280 *bme,
                                       int altitude,
                                       int pressure);
#ifdef __cplusplus
}
#endif  /* __cplusplus */
