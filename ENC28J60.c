#include "ENC28J60.h"



// "Правильное" значение ERXRDPT
uint16_t enc28j60_rxrdpt = 0;

uint8_t enc28j60_current_bank = 0;

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






// Read PHY register
uint16_t enc28j60_read_phy(uint8_t adr)
{
	enc28j60_wcr(MIREGADR, adr);
	enc28j60_bfs(MICMD, MICMD_MIIRD);
	while(enc28j60_rcr(MISTAT) & MISTAT_BUSY)
		;
	enc28j60_bfc(MICMD, MICMD_MIIRD);
	return enc28j60_rcr16(MIRDL);
}

// Write PHY register
void enc28j60_write_phy(uint8_t adr, uint16_t data)
{
	enc28j60_wcr(MIREGADR, adr);
	enc28j60_wcr16(MIWRL, data);
	while(enc28j60_rcr(MISTAT) & MISTAT_BUSY)
		;
}






//uint16_t enc28j60_rxrdpt = 0;

void enc28j60_init(uint8_t *macadr)
{
	// настраиваем SPI
	spi_init_master();
	// Выполняем сброс
	enc28j60_soft_reset();
	// настраиваем размер буфера для приема пакетов
    enc28j60_wcr16(ERXSTL, ENC28J60_RXSTART);
    enc28j60_wcr16(ERXNDL, ENC28J60_RXEND);
	// Указатель для чтения принятых пакетов
    enc28j60_wcr16(ERXRDPTL, ENC28J60_RXSTART);
    enc28j60_rxrdpt = ENC28J60_RXSTART;
	   // Настраиваем MAC
    enc28j60_wcr(MACON2, 0); // очищаем сброс
    enc28j60_wcr(MACON1, MACON1_TXPAUS|MACON1_RXPAUS| // включаем управление потоком
        MACON1_MARXEN); // разрешаем приём данных
    enc28j60_wcr(MACON3, MACON3_PADCFG0| // разрешаем паддинг
        MACON3_TXCRCEN| // разрешаем рассчёт контрольной суммы
        MACON3_FRMLNEN| //разрешаем контроль длины фреймов
        MACON3_FULDPX);// включаем полный дуплекс
    enc28j60_wcr16(MAMXFLL, ENC28J60_MAXFRAME); // устанавливаем максимальный размер фрейма
    enc28j60_wcr(MABBIPG, 0x15); // устанавливаем промежуток между фреймами
    enc28j60_wcr(MAIPGL, 0x12);
    enc28j60_wcr(MAIPGH, 0x0c);
    enc28j60_wcr(MAADR5, macadr[0]); // устанавливаем MAC-адрес
    enc28j60_wcr(MAADR4, macadr[1]);
    enc28j60_wcr(MAADR3, macadr[2]);
    enc28j60_wcr(MAADR2, macadr[3]);
    enc28j60_wcr(MAADR1, macadr[4]);
    enc28j60_wcr(MAADR0, macadr[5]);

    // Настраиваем PHY
    enc28j60_write_phy(PHCON1, PHCON1_PDPXMD); // включаем полный дуплекс
    enc28j60_write_phy(PHCON2, PHCON2_HDLDIS); // отключаем loopback
    enc28j60_write_phy(PHLCON, PHLCON_LACFG2| // настраиваем светодиодики
        PHLCON_LBCFG2|PHLCON_LBCFG1|PHLCON_LBCFG0|
        PHLCON_LFRQ0|PHLCON_STRCH);

    // разрешаем приём пакетов
    enc28j60_bfs(ECON1, ECON1_RXEN);
}




void enc28j60_send_packet(uint8_t *data, uint16_t len)
{
    // Ждем готовности передатчика
    while(enc28j60_rcr(ECON1) & ECON1_TXRTS)
    {
        // При ошибке, сбрасываем передатчик
        if(enc28j60_rcr(EIR) & EIR_TXERIF)
        {
            enc28j60_bfs(ECON1, ECON1_TXRST);
            enc28j60_bfc(ECON1, ECON1_TXRST);
        }
    }
        
    // Записываем пакет в буфер
    enc28j60_wcr16(EWRPTL, ENC28J60_TXSTART);
    enc28j60_write_buffer((uint8_t*)"\x00", 1);
    enc28j60_write_buffer(data, len);

    // Устанавливаем указатели ETXST и ETXND
    enc28j60_wcr16(ETXSTL, ENC28J60_TXSTART);
    enc28j60_wcr16(ETXNDL, ENC28J60_TXSTART + len);

    // Разрешаем отправку
    enc28j60_bfs(ECON1, ECON1_TXRTS);
}




uint16_t enc28j60_recv_packet(uint8_t *buf, uint16_t buflen)
{
    uint16_t len = 0, rxlen, status, temp;

    // Есть ли принятые пакеты?
    if(enc28j60_rcr(EPKTCNT))
    {
        // Считываем заголовок
        enc28j60_wcr16(ERDPTL, enc28j60_rxrdpt);

        enc28j60_read_buffer((void*)&enc28j60_rxrdpt, sizeof(enc28j60_rxrdpt));
        enc28j60_read_buffer((void*)&rxlen, sizeof(rxlen));
        enc28j60_read_buffer((void*)&status, sizeof(status));

        // Пакет принят успешно?
        if(status & 0x80)
        {
            // Выбрасываем контрольную сумму
            len = rxlen - 4;
            
            // Читаем пакет в буфер (если буфера не хватает, пакет обрезается)
            if(len > buflen) len = buflen;
            enc28j60_read_buffer(buf, len);    
        }

        // Устанавливаем ERXRDPT на адрес следующего пакета - 1
        temp = (enc28j60_rxrdpt - 1) & ENC28J60_BUFEND;
        enc28j60_wcr16(ERXRDPTL, temp);

        // Уменьшаем счётчик пакетов
        enc28j60_bfs(ECON2, ECON2_PKTDEC);
    }

    return len;
}
