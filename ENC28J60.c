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

uint8_t enc28j60_current_bank = 0;
// Выбор банка регистров
void enc28j60_set_bank(uint8_t adr)
{
    uint8_t bank;

    // Регистр относится к определённому банку?
    if( (adr & ENC28J60_ADDR_MASK) < ENC28J60_COMMON_CR )
    {
        // Получаем номер банка
        bank = (adr >> 5) & 0x03; //BSEL1|BSEL0=0x03
        
        // Если выбран "не тот" банк
        if(bank != enc28j60_current_bank)
        {
            // Выбираем банк
            enc28j60_write(ENC28J60_SPI_COB, ECON1, 0x03);
            enc28j60_write(ENC28J60_SPI_SOB, ECON1, bank);
            enc28j60_current_bank = bank;
        }
    }
}



uint8_t enc28j60_rcr(uint8_t adr)
{
    enc28j60_set_bank(adr);
    return enc28j60_read(ENC28J60_SPI_ROR, adr);
}


uint16_t enc28j60_rcr16(uint8_t adr)
{
    enc28j60_set_bank(adr);
    return enc28j60_read(ENC28J60_SPI_ROR, adr) |
        (enc28j60_read(ENC28J60_SPI_ROR, adr+1) << 8);
}


void enc28j60_wcr(uint8_t adr, uint8_t arg)
{
    enc28j60_set_bank(adr);
    enc28j60_write(ENC28J60_SPI_WOR, adr, arg);
}


void enc28j60_wcr16(uint8_t adr, uint16_t arg)
{
    enc28j60_set_bank(adr);
    enc28j60_write(ENC28J60_SPI_WOR, adr, arg);
    enc28j60_write(ENC28J60_SPI_WOR, adr+1, arg>>8);
}


void enc28j60_bfc(uint8_t adr, uint8_t mask)//????????????
{
    enc28j60_set_bank(adr);
    enc28j60_write(ENC28J60_SPI_COB, adr, mask);
}


void enc28j60_bfs(uint8_t adr, uint8_t mask)//??????????
{
    enc28j60_set_bank(adr);
    enc28j60_write(ENC28J60_SPI_SOB, adr, mask);
}

// Чтение данных из буфера (по адресу в регистрах ERDPT)
void enc28j60_read_buffer(uint8_t *buf, uint16_t len)
{
    spi_cs_L();
    spi_tx_data(ENC28J60_SPI_RBUF);
    while(len--)
        *(buf++) = spi_rx_data();
    spi_cs_H();
}

// Запись данных в буфер (по адресу в регистрах EWRPT)
void enc28j60_write_buffer(uint8_t *buf, uint16_t len)
{
    spi_cs_L();
    spi_tx_data(ENC28J60_SPI_WBUF);
    while(len--)
        spi_tx_data(*(buf++));
    spi_cs_H();
}

void enc28j60_soft_reset()
{
	spi_cs_L();
	spi_tx_data(ENC28J60_SPI_SC);// Отправляем команду
	spi_cs_H();
	_delay_ms(1);// Ждём, пока ENC28J60 инициализируется
	enc28j60_current_bank = 0;// Не забываем про банк
}
