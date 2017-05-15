/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino Adafruit DHT library API wrapper
 */

#include "DHT.h"

#ifdef __cplusplus
extern "C"
{
#endif

DHT *mgos_dht_init(uint8_t pin, uint8_t type);
void mgos_dht_close(DHT *dht);
void mgos_dht_begin(DHT *dht);
int mgos_dht_read_temperature(DHT *dht, int s, int f);
int mgos_dht_convert_ctof(DHT *dht, int tc);
int mgos_dht_convert_ftocC(DHT *dht, int tf);
int mgos_dht_compute_heat_index(DHT *dht, int t, int h, int f);
int mgos_dht_read_humidity(DHT *dht, int f);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
