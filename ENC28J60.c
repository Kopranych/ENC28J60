#include "ENC28J60.h"

uint8_t enc28j60_read(uint8_t cmd, uint8_t adr)
{
	uint8_t data;
	spi_cs_L();
	spi_tx_data(cmd|(adr&0x1F));//���������� ������� 
	if(adr&0x80) spi_rx_data();// ��� ������������� ���������� ������ ����
	data = spi_rx_data();// ������ ������
	spi_cs_H();
	return data;
}

void enc28j60_write(uint8_t cmd, uint8_t adr, uint8_t data)
{
	spi_cs_L();
	spi_tx_data(cmd|(adr&0x1F));//���������� ������� 
	spi_tx_data(data);
	spi_cs_H();
}

uint8_t enc28j60_current_bank = 0;
// ����� ����� ���������
void enc28j60_set_bank(uint8_t adr)
{
    uint8_t bank;

    // ������� ��������� � ������������ �����?
    if( (adr & ENC28J60_ADDR_MASK) < ENC28J60_COMMON_CR )
    {
        // �������� ����� �����
        bank = (adr >> 5) & 0x03; //BSEL1|BSEL0=0x03
        
        // ���� ������ "�� ���" ����
        if(bank != enc28j60_current_bank)
        {
            // �������� ����
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

// ������ ������ �� ������ (�� ������ � ��������� ERDPT)
void enc28j60_read_buffer(uint8_t *buf, uint16_t len)
{
    spi_cs_L();
    spi_tx_data(ENC28J60_SPI_RBUF);
    while(len--)
        *(buf++) = spi_rx_data();
    spi_cs_H();
}

// ������ ������ � ����� (�� ������ � ��������� EWRPT)
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
	spi_tx_data(ENC28J60_SPI_SC);// ���������� �������
	spi_cs_H();
	_delay_ms(1);// ���, ���� ENC28J60 ����������������
	enc28j60_current_bank = 0;// �� �������� ��� ����
}
