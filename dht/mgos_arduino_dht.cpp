/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino Adafruit DHT library API wrapper
 */

#include <math.h>
#include "mgos_arduino_dht.h"

#define MGOS_DHT_RES_FAIL -12700

DHT *mgos_dht_init(uint8_t pin, uint8_t type) {
  return new DHT(pin, type, 0);
}

void mgos_dht_close(DHT *dht) {
  if (dht != nullptr) {
    delete dht;
    dht = nullptr;
  }
}

void mgos_dht_begin(DHT *dht) {
  if (dht == nullptr) return;
  dht->begin();
}

int mgos_dht_read_temperature(DHT *dht, int s, int f) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  float res = dht->readTemperature(s, f);
  return isnan(res) ? MGOS_DHT_RES_FAIL : round(res * 100.0);
}

int mgos_dht_convert_ctof(DHT *dht, int tc) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  return round(dht->convertCtoF(tc / 100.0) * 100.0);
}

int mgos_dht_convert_ftocC(DHT *dht, int tf) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  return round(dht->convertFtoC(tf / 100.0) * 100.0);
}

int mgos_dht_compute_heat_index(DHT *dht, int t, int h, int f) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  return round(dht->computeHeatIndex(t / 100.0, h / 100.0, f) * 100.0);
}

int mgos_dht_read_humidity(DHT *dht, int f) {
  if (dht == nullptr) return MGOS_DHT_RES_FAIL;
  float res = dht->readHumidity(f);
  return isnan(res) ? MGOS_DHT_RES_FAIL : round(res * 100.0);
}
