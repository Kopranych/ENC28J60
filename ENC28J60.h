#include <avr/io.h>
#include <util/delay.h>
#include "SPI.h"
#include "ENC28J60_map_register.h"

//������ 
#define ENC28J60_SPI_ROR    0x00//������ ��������
#define ENC28J60_SPI_WOR    0x40//������ ��������
#define ENC28J60_SPI_SOB    0x80//��������� ��� �� �����
#define ENC28J60_SPI_COB    0xA0//������ ��� �� �����
#define ENC28J60_SPI_RBUF   0x3A//������ ������
#define ENC28J60_SPI_WBUF   0x7A// ������ � �����
#define ENC28J60_SPI_SC     0xFF//������ �����
//


#define ENC28J60_ADDR_MASK  0x1F//




uint8_t enc28j60_read(uint8_t cmd, uint8_t adr);//������ ������ �� ��������
void enc28j60_write(uint8_t cmd, uint8_t adr, uint8_t data);//������ ������ � �������
void enc28j60_set_bank(uint8_t adr);// ����� ����� ���������
uint8_t enc28j60_rcr(uint8_t adr);//������ ��������
uint16_t enc28j60_rcr16(uint8_t adr);//������ ���� ��������� L & H
void enc28j60_wcr(uint8_t adr, uint8_t arg);//������ �������� 
void enc28j60_wcr16(uint8_t adr, uint16_t arg);//������ ���� ��������� L & H
void enc28j60_bfc(uint8_t adr, uint8_t mask);//������� ����� � �������� (reg[adr] &= ~mask)
void enc28j60_bfs(uint8_t adr, uint8_t mask);//��������� ����� � �������� (reg[adr] |= mask)
void enc28j60_read_buffer(uint8_t *buf, uint16_t len);//������ ������ �� ������ (�� ������ � ��������� ERDPT)
void enc28j60_write_buffer(uint8_t *buf, uint16_t len);//// ������ ������ � ����� (�� ������ � ��������� EWRPT)
void enc28j60_soft_reset();//������ �����
