#include "ENC28J60.h"

uint8_t enc28j60_read(uint8_t cmd, uint8_t adr)
{
	uint8_t data;
	spi_cs_L();
	spi_tx_data(cmd|(adr&0x1F));//отправляем команду 
	if(adr&0x80) spi_rx_data();// при необходимости пропускаем ложный байт
	data = spi_rx_data();// читаем данные
	spi_cs_H();
	return data;
}

void enc28j60_write(uint8_t cmd, uint8_t adr, uint8_t data)
{
	spi_cs_L();
	spi_tx_data(cmd|(adr&0x1F));//отправляем команду 
	spi_tx_data(data);
	spi_cs_H();
}
