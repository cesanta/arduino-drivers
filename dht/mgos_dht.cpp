/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino Adafruit DHT library API wrapper
 */

#include <math.h>

#include "DHT.h"
#include "mgos_dht.h"

#define MGOS_DHT_RES_FAIL -12700

void *mgos_dht_init(int pin, int type) {
  return new DHT(pin, type, 0);
}

void mgos_dht_close(void *dht) {
  if (dht != nullptr) {
    delete static_cast<DHT*>(dht);
    dht = nullptr;
  }
}

void mgos_dht_begin(void *dht) {
  if (dht == nullptr) return;
  static_cast<DHT*>(dht)->begin();
}

int mgos_dht_read_temperature(void *dht, int s, int f) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  float res = static_cast<DHT*>(dht)->readTemperature(s, f);
  return isnan(res) ? MGOS_DHT_RES_FAIL : round(res * 100.0);
}

int mgos_dht_convert_ctof(void *dht, int tc) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  return round(static_cast<DHT*>(dht)->convertCtoF(tc / 100.0) * 100.0);
}

int mgos_dht_convert_ftocC(void *dht, int tf) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  return round(static_cast<DHT*>(dht)->convertFtoC(tf / 100.0) * 100.0);
}

int mgos_dht_compute_heat_index(void *dht, int t, int h, int f) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  return round(static_cast<DHT*>(dht)->computeHeatIndex(t / 100.0, h / 100.0, f) * 100.0);
}

int mgos_dht_read_humidity(void *dht, int f) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  float res = static_cast<DHT*>(dht)->readHumidity(f);
  return isnan(res) ? MGOS_DHT_RES_FAIL : round(res * 100.0);
}
