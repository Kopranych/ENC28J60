#include "SPI.h"
#include "ENC28J60_map_register.h"


void spi_cs_L()
{
	SPI_PORT&= ~(1<<SPI_SS);
}

void spi_cs_H()
{
	SPI_PORT|= 1<<SPI_SS;//строб вверх
}

void spi_init_master()
{
	SPI_DDR |= 1<<SPI_SS|1<<SPI_MOSI|1<<SPI_SCK;
	SPI_DDR &=~(1<<SPI_MISO);
	SPI_PORT&=~(1<<SPI_SS|1<<SPI_MOSI|1<<SPI_SCK|1<<SPI_MISO);
	SPCR |=1<<SPE|1<<MSTR;//включаем SPI и режим Master
	SPSR |=1<<SPI2X;//удвоение частоты тактового сигнала для модуля ENC28J60
}

void spi_init_slave()
{
	SPI_DDR &= ~(1<<SPI_SS|1<<SPI_MOSI|1<<SPI_SCK);
	SPI_DDR |=1<<SPI_MISO;
	SPI_PORT&=~(1<<SPI_SS|1<<SPI_MOSI|1<<SPI_SCK|1<<SPI_MISO);
	SPCR |=1<<SPE;//включаем SPI и режим Slave
}

uint8_t spi_tx_data(uint8_t data)
{
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));//ждем пока данные передадутся
	SPI_PORT|= 1<<SPI_SS;//строб вверх
	spi_cs_L();//вниз для сдвига данных далее
	return SPDR;
}

uint8_t spi_rx_data()
{
	uint8_t data = 0xFF;
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));//ждем пока данные не передадутся
	return SPDR;
}

