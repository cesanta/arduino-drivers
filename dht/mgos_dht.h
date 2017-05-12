/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino Adafruit DHT library API wrapper
 */

#ifdef __cplusplus
extern "C"
{
#endif

void *mgos_dht_init(int pin, int type);
void mgos_dht_close(void *dht);
void mgos_dht_begin(void *dht);
int mgos_dht_read_temperature(void *dht, int s, int f);
int mgos_dht_convert_ctof(void *dht, int tc);
int mgos_dht_convert_ftocC(void *dht, int tf);
int mgos_dht_compute_heat_index(void *dht, int t, int h, int f);
int mgos_dht_read_humidity(void *dht, int f);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
