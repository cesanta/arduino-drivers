/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 *
 * Arduino OneWire driver API wrapper
 */

#include "mgos_arduino_onewire.h"

#if MGOS_ENABLE_ARDUINO_API && MGOS_ENABLE_ONEWIRE

OneWire *mgos_arduino_onwire_init(uint8_t pin) {
  return new OneWire(pin);
}

void mgos_arduino_onwire_close(OneWire *ow) {
  if (ow != nullptr) {
    delete ow;
    ow = nullptr;
  }
}

uint8_t mgos_arduino_onwire_reset(OneWire *ow) {
  if (ow == nullptr) return 0;
  return ow->reset();
}

void mgos_arduino_onwire_select(OneWire *ow, const uint8_t *addr) {
  if (ow == nullptr) return;
  return ow->select(addr);
}

void mgos_arduino_onwire_skip(OneWire *ow) {
  if (ow == nullptr) return;
  return ow->skip();
}

void mgos_arduino_onwire_write(OneWire *ow, uint8_t v) {
  if (ow == nullptr) return;
  return ow->write(v);
}

void mgos_arduino_onwire_write_bytes(OneWire *ow, const uint8_t *buf, uint16_t count) {
  if (ow == nullptr) return;
  return ow->write_bytes(buf, count);
}

uint8_t mgos_arduino_onwire_read(OneWire *ow) {
  if (ow == nullptr) return 0;
  return ow->read();
}

void mgos_arduino_onwire_read_bytes(OneWire *ow, uint8_t *buf, uint16_t count) {
  if (ow == nullptr) return;
  return ow->read_bytes(buf, count);
}

void mgos_arduino_onwire_write_bit(OneWire *ow, uint8_t v) {
  if (ow == nullptr) return;
  return ow->write_bit(v);
}

uint8_t mgos_arduino_onwire_read_bit(OneWire *ow) {
  if (ow == nullptr) return 0;
  return ow->read_bit();
}

void mgos_arduino_onwire_depower(OneWire *ow) {
  if (ow == nullptr) return;
  return ow->depower();
}

void mgos_arduino_onwire_reset_search(OneWire *ow) {
  if (ow == nullptr) return;
  return ow->reset_search();
}

void mgos_arduino_onwire_target_search(OneWire *ow, uint8_t family_code) {
  if (ow == nullptr) return;
  return ow->target_search(family_code);
}

uint8_t mgos_arduino_onwire_search(OneWire *ow, uint8_t *newAddr, int search_mode) {
  if (ow == nullptr) return 0;
  return ow->search(newAddr, search_mode);
}

uint8_t mgos_arduino_onwire_crc8(OneWire *ow, const uint8_t *addr, uint8_t len) {
  if (ow == nullptr) return 0;
  return ow->crc8(addr, len);
}

#endif /* MGOS_ENABLE_ARDUINO_API && MGOS_ENABLE_ONEWIRE */
