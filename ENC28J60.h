#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "ENC28J60_map_register.h"

//Опкоды 
#define ENC28J60_SPI_ROR    0x00//чтение регистра
#define ENC28J60_SPI_WOR    0x40//запись регистра
#define ENC28J60_SPI_SOB    0x80//установка бит по маске
#define ENC28J60_SPI_COB    0xA0//снятие бит по маске
#define ENC28J60_SPI_RBUF   0x3A//чтение буфера
#define ENC28J60_SPI_WBUF   0x7A// запись в буфер
#define ENC28J60_SPI_SC     0xFF//мягкий сброс
//
//Инициализация
#define ENC28J60_BUFSIZE    0x2000
#define ENC28J60_RXSIZE     0x1A00
#define ENC28J60_MAXFRAME   1500

#define ENC28J60_RXSTART    0
#define ENC28J60_RXEND      (ENC28J60_RXSIZE-1)
#define ENC28J60_TXSTART    ENC28J60_RXSIZE
#define ENC28J60_BUFEND     (ENC28J60_BUFSIZE-1)
//



#define ENC28J60_ADDR_MASK  0x1F//




uint8_t enc28j60_read(uint8_t cmd, uint8_t adr);//чтение данных из регистра
void enc28j60_write(uint8_t cmd, uint8_t adr, uint8_t data);//запись данных в регистр
void enc28j60_set_bank(uint8_t adr);// Выбор банка регистров
uint8_t enc28j60_rcr(uint8_t adr);//чтение регистра
uint16_t enc28j60_rcr16(uint8_t adr);//чтение пары регистров L & H
void enc28j60_wcr(uint8_t adr, uint8_t arg);//запись регистра 
void enc28j60_wcr16(uint8_t adr, uint16_t arg);//запись пары регистров L & H
void enc28j60_bfc(uint8_t adr, uint8_t mask);//очистка битов в регистре (reg[adr] &= ~mask)
void enc28j60_bfs(uint8_t adr, uint8_t mask);//Установка битов в регистре (reg[adr] |= mask)
void enc28j60_read_buffer(uint8_t *buf, uint16_t len);//Чтение данных из буфера (по адресу в регистрах ERDPT)
void enc28j60_write_buffer(uint8_t *buf, uint16_t len);//// Запись данных в буфер (по адресу в регистрах EWRPT)
void enc28j60_soft_reset();//мягкий сброс
void enc28j60_init(uint8_t *macadr);//инициализация ENC28J60
// Настраиваем PHY
uint16_t enc28j60_read_phy(uint8_t adr);
void enc28j60_write_phy(uint8_t adr, uint16_t data);
//

void enc28j60_send_packet(uint8_t *data, uint16_t len);//отправка пакетов
uint16_t enc28j60_recv_packet(uint8_t *buf, uint16_t buflen);//прием пакетов
