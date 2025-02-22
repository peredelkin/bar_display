/*
 * ssd2828.h
 *
 *  Created on: 22 февр. 2025 г.
 *      Author: ruslan
 */

#ifndef SSD2828_H_
#define SSD2828_H_

#include <stdint.h>
#include <assert.h>

#ifndef PACKED
#define PACKED __attribute__((packed))
#endif

#define SSD2828_ADDR_DIR		0xB0	//Device Identification Register
#define SSD2828_ADDR_VICR1		0xB1  //RGB Interface Control Register 1
#define SSD2828_ADDR_VICR2		0xB2  //RGB Interface Control Register 2
#define SSD2828_ADDR_VICR3		0xB3  //RGB Interface Control Register 3
#define SSD2828_ADDR_VICR4		0xB4  //RGB Interface Control Register 4
#define SSD2828_ADDR_VICR5		0xB5  //RGB Interface Control Register 5
#define SSD2828_ADDR_VICR6		0xB6  //RGB Interface Control Register 6
#define SSD2828_ADDR_CFGR		0xB7  //Configuration Register
#define SSD2828_ADDR_VCR		0xB8  //VC Control Register
#define SSD2828_ADDR_PCR		0xB9  //PLL Control Register
#define SSD2828_ADDR_PLCR		0xBA  //PLL Configuration Register
#define SSD2828_ADDR_CCR		0xBB  //Clock Control Register
#define SSD2828_ADDR_PSCR1		0xBC  //Packet Size Control Register 1
#define SSD2828_ADDR_PSCR2		0xBD  //Packet Size Control Register 2
#define SSD2828_ADDR_PSCR3		0xBE  //Packet Size Control Register 3
#define SSD2828_ADDR_PDR		0xBF  //Packet Drop Register
#define SSD2828_ADDR_OCR		0xC0  //Operation Control Register
#define SSD2828_ADDR_MRSR		0xC1  //Maximum Return Size Register
#define SSD2828_ADDR_RDCR		0xC2  //Return Data Count Register
#define SSD2828_ADDR_ARSR		0xC3  //ACK Response Register
#define SSD2828_ADDR_LCR		0xC4  //Line Control Register
#define SSD2828_ADDR_ICR		0xC5  //Interrupt Control Register
#define SSD2828_ADDR_ISR		0xC6  //Interrupt Status Register
#define SSD2828_ADDR_ESR		0xC7  //Error Status Register
#define SSD2828_ADDR_DAR1		0xC9  //Delay Adjustment Register 1
#define SSD2828_ADDR_DAR2		0xCA  //Delay Adjustment Register 2
#define SSD2828_ADDR_DAR3		0xCB  //Delay Adjustment Register 3
#define SSD2828_ADDR_DAR4		0xCC  //Delay Adjustment Register 4
#define SSD2828_ADDR_DAR5		0xCD  //Delay Adjustment Register 5
#define SSD2828_ADDR_DAR6		0xCE  //Delay Adjustment Register 6
#define SSD2828_ADDR_HTTR1		0xCF  //HS TX Timer Register 1
#define SSD2828_ADDR_HTTR2		0xD0  //HS TX Timer Register 2
#define SSD2828_ADDR_LRTR1		0xD1  //LP RX Timer Register 1
#define SSD2828_ADDR_LRTR2		0xD2  //LP RX Timer Register 2
#define SSD2828_ADDR_TSR		0xD3  //TE Status Register
#define SSD2828_ADDR_LRR		0xD4  //SPI Read Register
#define SSD2828_ADDR_PLLR		0xD5  //PLL Lock Register
#define SSD2828_ADDR_TR			0xD6  //Test Register
#define SSD2828_ADDR_TECR		0xD7  //TE Count Register
#define SSD2828_ADDR_ACR1		0xD8  //Analog Control Register 1
#define SSD2828_ADDR_ACR2		0xD9  //Analog Control Register 2
#define SSD2828_ADDR_ACR3		0xDA  //Analog Control Register 3
#define SSD2828_ADDR_ACR4		0xDB  //Analog Control Register 4
#define SSD2828_ADDR_IOCR		0xDC  //Interrupt Output Control Register
#define SSD2828_ADDR_VICR7		0xDD  //RGB Interface Control Register 7
#define SSD2828_ADDR_LCFR		0xDE  //Lane Configuration Register
#define SSD2828_ADDR_DAR7		0xDF  //Delay Adjustment Register 7
#define SSD2828_ADDR_PUCR1		0xE0  //Pull Control Register 1
#define SSD2828_ADDR_PUCR2		0xE1  //Pull Control Register 2
#define SSD2828_ADDR_PUCR3		0xE2  //Pull Control Register 3
#define SSD2828_ADDR_CBCR1		0xE9  //CABC Brightness Control Register 1
#define SSD2828_ADDR_CBCR2		0xEA  //CABC Brightness Control Register 2
#define SSD2828_ADDR_CBSR		0xEB  //CABC Brightness Status Register
#define SSD2828_ADDR_ECR		0xEC  //Encoder Control Register
#define SSD2828_ADDR_VSDR		0xED  //Video Sync Delay Register
#define SSD2828_ADDR_TMR		0xEE  //Trimming Register
#define SSD2828_ADDR_GPIO1		0xEF  //GPIO Register 1
#define SSD2828_ADDR_GPIO2		0xF0  //GPIO Register 2
#define SSD2828_ADDR_DLYA01		0xF1  //DLYA01 Register
#define SSD2828_ADDR_DLYA23		0xF2  //DLYA23 Register
#define SSD2828_ADDR_DLYB01		0xF3  //DLYB01 Register
#define SSD2828_ADDR_DLYB23		0xF4  //DLYB23 Register
#define SSD2828_ADDR_DLYC01		0xF5  //DLYC01 Register
#define SSD2828_ADDR_DLYC23		0xF6  //DLYC23 Register
#define SSD2828_ADDR_ACR5		0xF7  //Analog Control Register 5
#define SSD2828_ADDR_RR			0xFF  //Read Register

#define SSD2828_DATA_DIR		0x2828	//Device Identification Register

#define SSD2828_DATA_SIZE 2

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned DIR :16;
	} bit;
} ssd2828_DIR_t;
static_assert(sizeof(ssd2828_DIR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DIR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned HSA :8;	//Horizontal Sync Active Period
		unsigned VSA :8;	//Vertical Sync Active Period
	} bit;
} ssd2828_VICR1_t;
static_assert(sizeof(ssd2828_VICR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR1_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned HBP :8;	//Horizontal Back Porch Period
		unsigned VBP :8;	//Vertical Back Porch Period
	} bit;
} ssd2828_VICR2_t;
static_assert(sizeof(ssd2828_VICR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR2_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned HFP :8;	//Horizontal Front Porch Period
		unsigned VFP :8;	//Vertical Front Porch Period
	} bit;
} ssd2828_VICR3_t;
static_assert(sizeof(ssd2828_VICR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR3_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned HACT :16;	//Horizontal Active Period
	} bit;
} ssd2828_VICR4_t;
static_assert(sizeof(ssd2828_VICR4_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR4_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned VACT :16;	//Vertical Active Period
	} bit;
} ssd2828_VICR5_t;
static_assert(sizeof(ssd2828_VICR5_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR5_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned VPF :2;	//Video Pixel Format
		unsigned VM :2;		//Video Mode
		unsigned VCS :1;	//Video Clock Suspend
		unsigned BLLP :1;	//BLLP Control
		unsigned NVD :1;	//Non Video Data Transmission Control
		unsigned NVB :1;	//Non Video Data Burst Mode Control
		unsigned CBM :1;	//Compress Burst Mode Control
		unsigned RES_9_12 :4;
		unsigned PCLK_P :1;	//PCLK_P
		unsigned HS_P :1;	//HS_P
		unsigned VS_P :1;	//VS_P
	} bit;
} ssd2828_VICR6_t;
static_assert(sizeof(ssd2828_VICR6_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR6_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned HS :1;		//HS Mode
		unsigned CKE :1;	//Clock Lane Enable
		unsigned SLP :1;	//Sleep Mode Enable
		unsigned VEN :1;	//Video Mode Enable
		unsigned HCLK :1;	//HS Clock Disable
		unsigned CSS :1;	//Clock Source Select
		unsigned DCS :1;	//DCS Enable
		unsigned REN :1;	//Read Enable
		unsigned ECD :1;	//ECC CRC Check Disable
		unsigned EOT :1;	//EOT Packet Enable
		unsigned LPE :1;	//Long Packet Enable
		unsigned TXD :1;	//Transmit Disable
		unsigned RES :4;
	} bit;
} ssd2828_CFGR_t;
static_assert(sizeof(ssd2828_CFGR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_CFGR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned VC1 :2;	//Virtual Channel ID for RGB Interface
		unsigned VC2 :2;	//Virtual Channel ID for SPI Interface
		unsigned VCE :2;	//Virtual Channel ID for EOT Packet
		unsigned VCM :2;	//Virtual Channel ID for Maximum Return Size Packet
		unsigned RES_8_15 :8;
	} bit;
} ssd2828_VCR_t;
static_assert(sizeof(ssd2828_VCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned PEN :1;	//PLL Enable
		unsigned RES_1_12 :12;
		unsigned SYS_DIS :1;//SYS_clk DISable
		unsigned SYSD :2;	//SYS_clk Divider
	} bit;
} ssd2828_PCR_t;
static_assert(sizeof(ssd2828_PCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned NS :8;		//PLL Multiplier
		unsigned MS :5;		//PLL Divider
		unsigned RES_13 :1;
		unsigned FR :2;		//Frequency Range
	} bit;
} ssd2828_PLCR_t;
static_assert(sizeof(ssd2828_PLCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PLCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned LPD :6;	//LP Clock Divider
		unsigned RES_6_15: 10;
	} bit;
} ssd28282_CCR_t;
static_assert(sizeof(ssd28282_CCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd28282_CCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned TDC_L :16;	//Transmit Data Count
	} bit;
} ssd2828_PSCR1_t;
static_assert(sizeof(ssd2828_PSCR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PSCR1_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned TDC_H :16;	//Transmit Data Count
	} bit;
} ssd2828_PSCR2_t;
static_assert(sizeof(ssd2828_PSCR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PSCR2_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned PST :13;	//Packet Size Threshold
		unsigned RES_13_15 :3;
	} bit;
} ssd2828_PSCR3_t;
static_assert(sizeof(ssd2828_PSCR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PSCR3_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned GPD :16;	//Generic Packet Drop
	} bit;
} ssd2828_GPDR_t;
static_assert(sizeof(ssd2828_GPDR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_GPDR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned COP :1;	//Cancel Operation
		unsigned RES_1_7 :7;
		unsigned RST :1;	//Software Reset
		unsigned RES_9_15 :7;
	} bit;
} ssd2828_OCR_t;
static_assert(sizeof(ssd2828_OCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_OCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned MRS :16;	//Maximum Return Size
	} bit;
} ssd2828_MRSR_t;
static_assert(sizeof(ssd2828_MRSR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_MRSR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned RDC :16;	//Return Data Count
	} bit;
} ssd2828_RDCR_t;
static_assert(sizeof(ssd2828_RDCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_RDCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned AR :16;	//ACK Response
	} bit;
} ssd2828_ARSR_t;
static_assert(sizeof(ssd2828_ARSR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ARSR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned FBW :1;	//Force BTA After Write
		unsigned FBT :1;	//Force BTA TE
		unsigned FBC :1;	//Force Bus Contention
		unsigned RTB :1;	//Register Triggered BTA
		unsigned RT :1;		//Reset Trigger
		unsigned IBC :1;	//Ignore Bus Contention
		unsigned RES_6_15 :10;
	} bit;
} ssd2828_LCR_t;
static_assert(sizeof(ssd2828_LCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_LCR_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned RDRE :1;	//Read Data Ready Enable
		unsigned POE :1;	//Packet Operation Enable
		unsigned BTARE :1;	//BTA Response Enable
		unsigned ARRE :1;	//ACK Response Ready Enable
		unsigned RES_4 :1;
		unsigned HSTOE :1;	//HS TX Time Out Enable
		unsigned LPTOE :1;	//LP RX Time Out Enable
		unsigned PLSE :1;	//PLL Lock Status Enable
		unsigned MLAE :1;	//MCU Long Buffer Available Enable
		unsigned MLEE :1;	//MCU Long Buffer Empty Enable
		unsigned RES_10_13 :4;
		unsigned CBAE :1;	//Command Buffer Available Enable
		unsigned CBEE :1;	//Command Buffer Empty Enable
	} bit;
} ssd2828_ICR_t;
static_assert(sizeof(ssd2828_ICR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ICR_t!");

typedef union {
	struct PACKED {
		unsigned RDR :1;	//Read Data Ready
		unsigned PO :1;		//Packet Operation
		unsigned BTAR :1;	//BTA Response
		unsigned ARR :1;	//ACK Response Ready
		unsigned ATR :1;	//ACK Trigger Response
		unsigned HSTO :1;	//HS TX Time Out
		unsigned LPTO :1;	//LP RX Time Out
		unsigned PLS :1;	//PLL Lock Status
		unsigned MLA :1;	//Reserved
		unsigned MLE :1;	//Reserved
		unsigned DST :1;	//Data Lane Status
		unsigned CST :1;	//Clock Lane Status
		unsigned RES_12_13 :2;
		unsigned CBA :1;	//Command Buffer Available
		unsigned CBE :1;	//Command Buffer Empty
	} bit;
} ssd2828_ISR_t;
static_assert(sizeof(ssd2828_ISR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ISR_t!");

typedef union {
	struct PACKED {
		unsigned VMM :1;	//VC Mis Match
		unsigned RES_2 :1;
		unsigned CONT :1;	//Contention
		unsigned RES_3 :1;
		unsigned MLO :1;	//Reserved
		unsigned RES_5_6 :2;
		unsigned CBO :1;	//Command Buffer Overflow
		unsigned ECCE1 :1;	//ECC Single Bit Error
		unsigned ECCE2 :1;	//ECC Multi Bit Error
		unsigned CRCE :1;	//CRC Error
		unsigned RES_11_15 :5;
	} bit;
} ssd2828_ESR_t;
static_assert(sizeof(ssd2828_ESR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ESR_t!");

typedef union {
	struct PACKED {
		unsigned HPD :8;	//HS Prepare Delay
		unsigned HZD :8;	//HS Zero Delay
	} bit;
} ssd2828_DAR1_t;
static_assert(sizeof(ssd2828_DAR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR1_t!");










#endif /* SSD2828_H_ */
