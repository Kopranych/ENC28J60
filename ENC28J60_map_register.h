// С этого адреса начинаются глобальные для всех банков регистры
#define ENC28J60_COMMON_CR    0x1B

//Банк 0
#define ERDPTL  0x00
#define ERDPTH	0x01
#define EWRPTL 	0x02
#define EWRPTH	0x03
#define ETXSTL 	0x04
#define ETXSTH	0x05
#define ETXNDL	0x06
#define ETXNDH	0x07
#define ERXSTL	0x08
#define ERXSTH	0x09
#define ERXNDL	0x0A
#define ERXNDH	0x0B
#define ERXRDPTL  0x0C
#define ERXRDPTH  0x0D
#define ERXWRPTL  0x0E
#define ERXWRPTH  0x0F
#define EDMASTL	0x10
#define EDMASTH	0x11
#define EDMANDL	0x12
#define EDMANDH	0x13
#define EDMADSTL  0x14
#define EDMADSTH  0x15
#define EDMACSL	0x16
#define EDMACSH	0x17
#define EIE		0x1B
#define EIR		0x1C
#define ESTAT	0x1D
#define ECON2	0x1E
#define ECON1	0x1F


//Банк 1
#define EHT0	(0x00|0x20)
#define EHT1	(0x01|0x20)
#define EHT2	(0x02|0x20)
#define EHT3	(0x03|0x20)
#define EHT4	(0x04|0x20)
#define EHT5	(0x05|0x20)
#define EHT6	(0x06|0x20)
#define EHT7	(0x07|0x20)
#define EPMM0	(0x08|0x20)
#define EPMM1	(0x09|0x20)
#define EPMM2	(0x0A|0x20)
#define EPMM3	(0x0B|0x20)
#define EPMM4	(0x0C|0x20)
#define EPMM5	(0x0D|0x20)
#define EPMM6	(0x0E|0x20)
#define EPMM7	(0x0F|0x20)
#define EPMCSL	(0x10|0x20)
#define EPMCSH	(0x11|0x20)
#define EPMOL	(0x14|0x20)
#define EPMOH	(0x15|0x20)
#define EWOLIE	(0x16|0x20)//нет в
#define EWOLIR	(0x17|0x20)//даташите
#define ERXFCON	(0x18|0x20)
#define EPKTCNT	(0x19|0x20)
#define EIE		0x1B
#define EIR		0x1C
#define ESTAT	0x1D
#define ECON2	0x1E
#define ECON1	0x1F

//Банк 2, регистры MAC,MII
#define MACON1	(0x00|0x40|0x80)
#define MACON1_TXPAUS (1<<3)
#define MACON1_RXPAUS (1<<2)
#define	MACON1_MARXEN (1<<0)
#define MACON2 	(0x01|0x40|0x80)
#define MACON3	(0x02|0x40|0x80)
#define MACON3_PADCFG0 (1<<5)
#define MACON3_TXCRCEN (1<<4)
#define MACON3_FRMLNEN (1<<1)
#define MACON3_FULDPX  (1<<0)
#define MACON4	(0x03|0x40|0x80)
#define MABBIPG	(0x04|0x40|0x80)
#define MAIPGL	(0x06|0x40|0x80)
#define MAIPGH	(0x07|0x40|0x80)
#define MACLCON1  (0x08|0x40|0x80)
#define MACLCON2  (0x09|0x40|0x80)
#define MAMXFLL	(0x0A|0x40|0x80)
#define MAMXFLH	(0x0B|0x40|0x80)
#define MICMD	(0x12|0x40|0x80)
#define MICMD_MIIRD 0x01
#define MIREGADR  (0x14|0x40|0x80)
#define MIWRL	(0x16|0x40|0x80)
#define MIWRH	(0x17|0x40|0x80)
#define MIRDL	(0x18|0x40|0x80)
#define MIRDH	(0x19|0x40|0x80)
#define EIE		0x1B
#define EIR		0x1C
#define ESTAT	0x1D
#define ECON2	0x1E
#define ECON1	0x1F

//Банк 3
#define MAADR1	(0x00|0x60)
#define MAADR0	(0x01|0x60)
#define MAADR3	(0x02|0x60)
#define MAADR2	(0x03|0x60)
#define MAADR5	(0x04|0x60)
#define MAADR4	(0x05|0x60)
#define EBSTSD	(0x06|0x60)
#define EBSTCON	(0x07|0x60)
#define EBSTCSL	(0x08|0x60)
#define EBSTCSH	(0x09|0x60)
#define MISTAT	(0x0A|0x60)
#define MISTAT_BUSY 0x01
#define EREVID	(0x12|0x60)
#define ECOCON	(0x15|0x60)
#define EFLOCON	(0x17|0x60)
#define EPAUSL	(0x18|0x60)
#define EPAUSH	(0x19|0x60)
#define EIE		0x1B
#define EIR		0x1C
#define ESTAT	0x1D
#define ECON2	0x1E
#define ECON1	0x1F

// PHY registers
#define PHCON1 				0x00
#define PHSTAT1 			0x01
#define PHID1 				0x02
#define PHID2 				0x03
#define PHCON2 				0x10
#define PHSTAT2 			0x11
#define PHIE 				0x12
#define PHIR 				0x13
#define PHLCON 				0x14

// PHCON1
#define PHCON1_PRST			0x8000
#define PHCON1_PLOOPBK		0x4000
#define PHCON1_PPWRSV		0x0800
#define PHCON1_PDPXMD		0x0100

// PHSTAT1
#define PHSTAT1_PFDPX		0x1000
#define PHSTAT1_PHDPX		0x0800
#define PHSTAT1_LLSTAT		0x0004
#define PHSTAT1_JBSTAT		0x0002

// PHCON2
#define PHCON2_FRCLNK		0x4000
#define PHCON2_TXDIS		0x2000
#define PHCON2_JABBER		0x0400
#define PHCON2_HDLDIS		0x0100

// PHSTAT2
#define PHSTAT2_TXSTAT		0x2000
#define PHSTAT2_RXSTAT		0x1000
#define PHSTAT2_COLSTAT		0x0800
#define PHSTAT2_LSTAT		0x0400
#define PHSTAT2_DPXSTAT		0x0200
#define PHSTAT2_PLRITY		0x0010

// PHIE
#define PHIE_PLNKIE			0x0010
#define PHIE_PGEIE			0x0002

// PHIR
#define PHIR_PLNKIF			0x0010
#define PHIR_PGIF			0x0004

// PHLCON
#define PHLCON_LACFG3		0x0800
#define PHLCON_LACFG2		0x0400
#define PHLCON_LACFG1		0x0200
#define PHLCON_LACFG0		0x0100
#define PHLCON_LBCFG3		0x0080
#define PHLCON_LBCFG2		0x0040
#define PHLCON_LBCFG1		0x0020
#define PHLCON_LBCFG0		0x0010
#define PHLCON_LFRQ1		0x0008
#define PHLCON_LFRQ0		0x0004
#define PHLCON_STRCH		0x0002

// ECON1
#define ECON1_TXRST			0x80
#define ECON1_RXRST			0x40
#define ECON1_DMAST			0x20
#define ECON1_CSUMEN		0x10
#define ECON1_TXRTS			0x08
#define ECON1_RXEN			0x04
#define ECON1_BSEL1			0x02
#define ECON1_BSEL0			0x01

// EIR
#define EIR_PKTIF			0x40
#define EIR_DMAIF			0x20
#define EIR_LINKIF			0x10
#define EIR_TXIF			0x08
#define EIR_WOLIF			0x04
#define EIR_TXERIF			0x02
#define EIR_RXERIF			0x01

// ECON2
#define ECON2_AUTOINC		0x80
#define ECON2_PKTDEC		0x40
#define ECON2_PWRSV			0x20
#define ECON2_VRPS			0x08
