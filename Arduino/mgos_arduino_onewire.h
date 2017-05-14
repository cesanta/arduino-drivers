/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino OneWire driver API wrapper
 */

#ifndef _MGOS_ARDUINO_ONEWIRE_H_
#define _MGOS_ARDUINO_ONEWIRE_H_

#include "fw/src/mgos_features.h"
#include "OneWire.h"

#ifdef __cplusplus
extern "C" {
#endif

#if MGOS_ENABLE_ARDUINO_API && MGOS_ENABLE_ONEWIRE

OneWire *mgos_arduino_onewire_init(uint8_t pin);
void mgos_arduino_onewire_close(OneWire *ow);
uint8_t mgos_arduino_onewire_reset(OneWire *ow);
void mgos_arduino_onewire_select(OneWire *ow, const uint8_t *addr);
void mgos_arduino_onewire_skip(OneWire *ow);
void mgos_arduino_onewire_write(OneWire *ow, uint8_t v);
void mgos_arduino_onewire_write_bytes(OneWire *ow, const uint8_t *buf, uint16_t count);
uint8_t mgos_arduino_onewire_read(OneWire *ow);
void mgos_arduino_onewire_read_bytes(OneWire *ow, uint8_t *buf, uint16_t count);
void mgos_arduino_onewire_write_bit(OneWire *ow, uint8_t v);
uint8_t mgos_arduino_onewire_read_bit(OneWire *ow);
void mgos_arduino_onewire_depower(OneWire *ow);
void mgos_arduino_onewire_reset_search(OneWire *ow);
void mgos_arduino_onewire_target_search(OneWire *ow, uint8_t family_code);
uint8_t mgos_arduino_onewire_search(OneWire *ow, uint8_t *newAddr, uint8_t search_mode);
uint8_t mgos_arduino_onewire_crc8(OneWire *ow, const uint8_t *addr, uint8_t len);

#endif /* MGOS_ENABLE_ARDUINO_API && MGOS_ENABLE_ONEWIRE */

#ifdef __cplusplus
}
#endif

#endif /* _MGOS_ARDUINO_ONEWIRE_H_ */
