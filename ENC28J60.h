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
//�������������
#define ENC28J60_BUFSIZE    0x2000
#define ENC28J60_RXSIZE     0x1A00
#define ENC28J60_MAXFRAME   1500

#define ENC28J60_RXSTART    0
#define ENC28J60_RXEND      (ENC28J60_RXSIZE-1)
#define ENC28J60_TXSTART    ENC28J60_RXSIZE
#define ENC28J60_BUFEND     (ENC28J60_BUFSIZE-1)
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
void enc28j60_init(uint8_t *macadr);//������������� ENC28J60
// ����������� PHY
uint16_t enc28j60_read_phy(uint8_t adr);
void enc28j60_write_phy(uint8_t adr, uint16_t data);
//

void enc28j60_send_packet(uint8_t *data, uint16_t len);//�������� �������
uint16_t enc28j60_recv_packet(uint8_t *buf, uint16_t buflen);//����� �������
