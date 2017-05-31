/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mgos_arduino_spi.h"

#include <SPI.h>

#include "mongoose/mongoose.h"

#if MGOS_ENABLE_SPI

SPIImpl SPI;

SPISettings::SPISettings() : clock(1000000), bit_order(MSBFIRST), mode(0) {
}

SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t mode)
    : clock(clock), bit_order(bitOrder), mode(mode) {
}

SPIImpl::SPIImpl(struct mgos_spi *spi) : spi_(spi) {
  memset(&txn_, 0, sizeof(txn_));
  txn_.cs = -1; /* CS control is performed externally */
}

void SPIImpl::begin() {
}

void SPIImpl::end() {
}

void SPIImpl::setBitOrder(uint8_t bitOrder) {
  (void) bitOrder;
}

void SPIImpl::setDataMode(uint8_t dataMode) {
  txn_.mode = dataMode;
}

void SPIImpl::setFrequency(uint32_t freq) {
  txn_.freq = freq;
}

void SPIImpl::beginTransaction(SPISettings settings) {
  setFrequency(settings.clock);
  setBitOrder(settings.bit_order);
  setDataMode(settings.mode);
}

void SPIImpl::endTransaction() {
}

uint8_t SPIImpl::transfer(uint8_t data) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return 0;
  txn.fd.tx_data = txn.fd.rx_data = &data;
  txn.fd.len = sizeof(data);
  if (!mgos_spi_run_txn(spi_, true /* full_duplex */, &txn)) data = 0;
  return data;
}

uint16_t SPIImpl::transfer16(uint16_t data) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return 0;
  data = htons(data);
  txn.fd.tx_data = txn.fd.rx_data = &data;
  txn.fd.len = sizeof(data);
  if (!mgos_spi_run_txn(spi_, true /* full_duplex */, &txn)) data = 0;
  data = ntohs(data);
  return data;
}

uint32_t SPIImpl::transfer32(uint32_t data) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return 0;
  data = htonl(data);
  txn.fd.tx_data = txn.fd.rx_data = &data;
  txn.fd.len = sizeof(data);
  if (!mgos_spi_run_txn(spi_, true /* full_duplex */, &txn)) data = 0;
  data = ntohl(data);
  return data;
}

void SPIImpl::transfer(void *data, size_t count) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return;
  txn.fd.tx_data = txn.fd.rx_data = data;
  txn.fd.len = count;
  mgos_spi_run_txn(spi_, true /* full_duplex */, &txn);
}

void SPIImpl::transferBytes(const uint8_t *data, uint8_t *out, uint32_t size) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return;
  txn.fd.tx_data = data;
  txn.fd.rx_data = out;
  txn.fd.len = size;
  mgos_spi_run_txn(spi_, true /* full_duplex */, &txn);
}

void SPIImpl::write(uint8_t data) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return;
  txn.hd.tx_data = &data;
  txn.hd.tx_len = sizeof(data);
  mgos_spi_run_txn(spi_, false /* full_duplex */, &txn);
}

void SPIImpl::write16(uint16_t data) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return;
  data = htons(data);
  txn.hd.tx_data = &data;
  txn.hd.tx_len = sizeof(data);
  mgos_spi_run_txn(spi_, false /* full_duplex */, &txn);
}

void SPIImpl::write32(uint32_t data) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return;
  data = htonl(data);
  txn.hd.tx_data = &data;
  txn.hd.tx_len = sizeof(data);
  mgos_spi_run_txn(spi_, false /* full_duplex */, &txn);
}

void SPIImpl::writeBytes(const uint8_t *data, uint32_t size) {
  struct mgos_spi_txn txn = txn_;
  if (spi_ == nullptr) return;
  txn.hd.tx_data = data;
  txn.hd.tx_len = size;
  mgos_spi_run_txn(spi_, false /* full_duplex */, &txn);
}

void SPIImpl::setSPI(struct mgos_spi *spi) {
  spi_ = spi;
}

void mgos_arduino_spi_init(void) {
  SPI.setSPI(mgos_spi_get_global());
}

#endif /* MGOS_ENABLE_SPI */
