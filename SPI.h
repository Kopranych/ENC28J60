// Библиотека для работы с шиной SPI

#include <avr/io.h>

#define SPI_DDR	 DDRB
#define SPI_PORT PORTB
#define SPI_SS 	 PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK  PB7

void spi_init_master();//функция инициализация шины SPI как мастер
void spi_init_slave();//функция инициализация шины SPI как slave
uint8_t spi_tx_data(uint8_t data);//передача данных по SPI
uint8_t spi_rx_data();//функция приема данных данных по SPI
void spi_cs_L();//chip select low
void spi_cs_H();//chip select high
