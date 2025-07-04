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

#define SSD2828_ADDR_DIR		0xB0  //Device Identification Register
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

#define SSD2828_DATA_DIR		0x2828 //Device Identification Register

#define SSD2828_DATA_SIZE 2

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DIR :16;			//Device Identification Number
	} bit;
} ssd2828_DIR_t;
static_assert(sizeof(ssd2828_DIR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DIR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HSA :8;			//Horizontal Sync Active Period
		unsigned VSA :8;			//Vertical Sync Active Period
	} bit;
} ssd2828_VICR1_t;
static_assert(sizeof(ssd2828_VICR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HBP :8;			//Horizontal Back Porch Period
		unsigned VBP :8;			//Vertical Back Porch Period
	} bit;
} ssd2828_VICR2_t;
static_assert(sizeof(ssd2828_VICR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HFP :8;			//Horizontal Front Porch Period
		unsigned VFP :8;			//Vertical Front Porch Period
	} bit;
} ssd2828_VICR3_t;
static_assert(sizeof(ssd2828_VICR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR3_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HACT :16;			//Horizontal Active Period
	} bit;
} ssd2828_VICR4_t;
static_assert(sizeof(ssd2828_VICR4_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR4_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned VACT :16;			//Vertical Active Period
	} bit;
} ssd2828_VICR5_t;
static_assert(sizeof(ssd2828_VICR5_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR5_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned VPF :2;			//Video Pixel Format
		unsigned VM :2;				//Video Mode
		unsigned VCS :1;			//Video Clock Suspend
		unsigned BLLP :1;			//BLLP Control
		unsigned NVD :1;			//Non Video Data Transmission Control
		unsigned NVB :1;			//Non Video Data Burst Mode Control
		unsigned CBM :1;			//Compress Burst Mode Control
		unsigned RES_9_12 :4;
		unsigned PCLK_P :1;			//PCLK_P
		unsigned HS_P :1;			//HS_P
		unsigned VS_P :1;			//VS_P
	} bit;
} ssd2828_VICR6_t;
static_assert(sizeof(ssd2828_VICR6_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR6_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HS :1;				//HS Mode
		unsigned CKE :1;			//Clock Lane Enable
		unsigned SLP :1;			//Sleep Mode Enable
		unsigned VEN :1;			//Video Mode Enable
		unsigned HCLK :1;			//HS Clock Disable
		unsigned CSS :1;			//Clock Source Select
		unsigned DCS :1;			//DCS Enable
		unsigned REN :1;			//Read Enable
		unsigned ECD :1;			//ECC CRC Check Disable
		unsigned EOT :1;			//EOT Packet Enable
		unsigned LPE :1;			//Long Packet Enable
		unsigned TXD :1;			//Transmit Disable
		unsigned RES :4;
	} bit;
} ssd2828_CFGR_t;
static_assert(sizeof(ssd2828_CFGR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_CFGR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned VC1 :2;			//Virtual Channel ID for RGB Interface
		unsigned VC2 :2;			//Virtual Channel ID for SPI Interface
		unsigned VCE :2;			//Virtual Channel ID for EOT Packet
		unsigned VCM :2;			//Virtual Channel ID for Maximum Return Size Packet
		unsigned RES_8_15 :8;
	} bit;
} ssd2828_VCR_t;
static_assert(sizeof(ssd2828_VCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned PEN :1;			//PLL Enable
		unsigned RES_1_12 :12;
		unsigned SYS_DIS :1;		//SYS_clk DISable
		unsigned SYSD :2;			//SYS_clk Divider
	} bit;
} ssd2828_PCR_t;
static_assert(sizeof(ssd2828_PCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned NS :8;				//PLL Multiplier
		unsigned MS :5;				//PLL Divider
		unsigned RES_13 :1;
		unsigned FR :2;				//Frequency Range
	} bit;
} ssd2828_PLCR_t;
static_assert(sizeof(ssd2828_PLCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PLCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned LPD :6;			//LP Clock Divider
		unsigned RES_6_15: 10;
	} bit;
} ssd28282_CCR_t;
static_assert(sizeof(ssd28282_CCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd28282_CCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned TDC_L :16;			//Transmit Data Count
	} bit;
} ssd2828_PSCR1_t;
static_assert(sizeof(ssd2828_PSCR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PSCR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned TDC_H :16;			//Transmit Data Count
	} bit;
} ssd2828_PSCR2_t;
static_assert(sizeof(ssd2828_PSCR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PSCR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned PST :13;			//Packet Size Threshold
		unsigned RES_13_15 :3;
	} bit;
} ssd2828_PSCR3_t;
static_assert(sizeof(ssd2828_PSCR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PSCR3_t!");

typedef union {
	uint16_t all;
	struct PACKED {
		unsigned GPD :16;			//Generic Packet Drop
	} bit;
} ssd2828_GPDR_t;
static_assert(sizeof(ssd2828_GPDR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_GPDR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned COP :1;			//Cancel Operation
		unsigned RES_1_7 :7;
		unsigned RST :1;			//Software Reset
		unsigned RES_9_15 :7;
	} bit;
} ssd2828_OCR_t;
static_assert(sizeof(ssd2828_OCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_OCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned MRS :16;			//Maximum Return Size
	} bit;
} ssd2828_MRSR_t;
static_assert(sizeof(ssd2828_MRSR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_MRSR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned RDC :16;			//Return Data Count
	} bit;
} ssd2828_RDCR_t;
static_assert(sizeof(ssd2828_RDCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_RDCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned AR :16;			//ACK Response
	} bit;
} ssd2828_ARSR_t;
static_assert(sizeof(ssd2828_ARSR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ARSR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned FBW :1;			//Force BTA After Write
		unsigned FBT :1;			//Force BTA TE
		unsigned FBC :1;			//Force Bus Contention
		unsigned RTB :1;			//Register Triggered BTA
		unsigned RT :1;				//Reset Trigger
		unsigned IBC :1;			//Ignore Bus Contention
		unsigned RES_6_15 :10;
	} bit;
} ssd2828_LCR_t;
static_assert(sizeof(ssd2828_LCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_LCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned RDRE :1;			//Read Data Ready Enable
		unsigned POE :1;			//Packet Operation Enable
		unsigned BTARE :1;			//BTA Response Enable
		unsigned ARRE :1;			//ACK Response Ready Enable
		unsigned RES_4 :1;
		unsigned HSTOE :1;			//HS TX Time Out Enable
		unsigned LPTOE :1;			//LP RX Time Out Enable
		unsigned PLSE :1;			//PLL Lock Status Enable
		unsigned MLAE :1;			//MCU Long Buffer Available Enable
		unsigned MLEE :1;			//MCU Long Buffer Empty Enable
		unsigned RES_10_13 :4;
		unsigned CBAE :1;			//Command Buffer Available Enable
		unsigned CBEE :1;			//Command Buffer Empty Enable
	} bit;
} ssd2828_ICR_t;
static_assert(sizeof(ssd2828_ICR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ICR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned RDR :1;			//Read Data Ready
		unsigned PO :1;				//Packet Operation
		unsigned BTAR :1;			//BTA Response
		unsigned ARR :1;			//ACK Response Ready
		unsigned ATR :1;			//ACK Trigger Response
		unsigned HSTO :1;			//HS TX Time Out
		unsigned LPTO :1;			//LP RX Time Out
		unsigned PLS :1;			//PLL Lock Status
		unsigned MLA :1;			//Reserved
		unsigned MLE :1;			//Reserved
		unsigned DST :1;			//Data Lane Status
		unsigned CST :1;			//Clock Lane Status
		unsigned RES_12_13 :2;
		unsigned CBA :1;			//Command Buffer Available
		unsigned CBE :1;			//Command Buffer Empty
	} bit;
} ssd2828_ISR_t;
static_assert(sizeof(ssd2828_ISR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ISR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned VMM :1;			//VC Mis Match
		unsigned RES_2 :1;
		unsigned CONT :1;			//Contention
		unsigned RES_3 :1;
		unsigned MLO :1;			//Reserved
		unsigned RES_5_6 :2;
		unsigned CBO :1;			//Command Buffer Overflow
		unsigned ECCE1 :1;			//ECC Single Bit Error
		unsigned ECCE2 :1;			//ECC Multi Bit Error
		unsigned CRCE :1;			//CRC Error
		unsigned RES_11_15 :5;
	} bit;
} ssd2828_ESR_t;
static_assert(sizeof(ssd2828_ESR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ESR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HPD :8;			//HS Prepare Delay
		unsigned HZD :8;			//HS Zero Delay
	} bit;
} ssd2828_DAR1_t;
static_assert(sizeof(ssd2828_DAR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CPD :8;			//CLK Prepare Delay
		unsigned CZD :8;			//CLK Zero Delay
	} bit;
} ssd2828_DAR2_t;
static_assert(sizeof(ssd2828_DAR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CPTD :8;			//CLK Post Delay
		unsigned CPED :8;			//CLK Pre Delay
	} bit;
} ssd2828_DAR3_t;
static_assert(sizeof(ssd2828_DAR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR3_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HTD :8;			//HS Trail Delay
		unsigned CTD :8;			//CLK Trail Delay
	} bit;
} ssd2828_DAR4_t;
static_assert(sizeof(ssd2828_DAR4_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR4_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned WUD :16;			//Wake Up Delay
	} bit;
} ssd2828_DAR5_t;
static_assert(sizeof(ssd2828_DAR5_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR5_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned TGET :4;			//TA Get Delay
		unsigned RES_4_7: 4;
		unsigned TGO :4;			//TA Go Delay
		unsigned RES_12_15 :4;
	} bit;
} ssd2828_DAR6_t;
static_assert(sizeof(ssd2828_DAR6_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR6_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HTT_L :16;			//HS TX Timer
	} bit;
} ssd2828_HTTR1_t;
static_assert(sizeof(ssd2828_HTTR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_HTTR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HTT_H :16;			//HS TX Timer
	} bit;
} ssd2828_HTTR2_t;
static_assert(sizeof(ssd2828_HTTR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_HTTR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned LRT_L :16;			//LP RX Timer
	} bit;
} ssd2828_LRTR1_t;
static_assert(sizeof(ssd2828_LRTR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_LRTR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned LRT_H :16;			//LP RX Timer
	} bit;
} ssd2828_LRTR2_t;
static_assert(sizeof(ssd2828_LRTR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_LRTR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned TER :1;			//TE Response
		unsigned RES_1_15 :15;
	} bit;
} ssd2828_TSR_t;
static_assert(sizeof(ssd2828_TSR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_TSR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned RRA :8;			//Register Read Address
		unsigned RES_9_15 :8;
	} bit;
} ssd2828_LRR_t;
static_assert(sizeof(ssd2828_LRR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_LRR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned LOCK :16;			//LOCK
	} bit;
} ssd2828_PLLR_t;
static_assert(sizeof(ssd2828_PLLR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PLLR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CO :1;				//Color Order
		unsigned END :1;			//Endianess
		unsigned PNB :6;			//Packet Number in Blanking Period
		unsigned FLM :1;			//Force Lane Mode
		unsigned EIC :5;			//Error Injection Control
		unsigned TM_FL0 :2;			//Test Mode/Force Lane 0
	} bit;
} ssd2828_TR_t;
static_assert(sizeof(ssd2828_TR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_TR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned TEC :16;	//TE Count
	} bit;
} ssd2828_TECR_t;
static_assert(sizeof(ssd2828_TECR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_TECR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned D0_DELAY_SEL :6;	//Data lane 0 DELAY SELect
		unsigned D3_DELAY_0_1 :2;	//Data lane 3 DELAY SELect[1:0]
		unsigned D1_DELAY_SEL :6;	//Data lane 1 DELAY SELect
		unsigned D3_DELAY_2_3 :2;	//Data lane 3 DELAY SELect[3:2]
	} bit;
} ssd2828_ACR1_t;
static_assert(sizeof(ssd2828_ACR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ACR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned D2_DELAY_SEL :6;	//Data lane 2 DELAY SELect
		unsigned D3_DELAY_4_5 :2;	//Data lane 3 DELAY SELect[5:4]
		unsigned HSTX_DS :3;		//High Speed TX current Driver Selection
		unsigned LPTXDS :3;			//Low Power TX Drive strength Selection
		unsigned HSTX_Z :2;			//High Speed Transmit Trimming control
	} bit;
} ssd2828_ACR2_t;
static_assert(sizeof(ssd2828_ACR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ACR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned ISEL :3;			//Current Output Trim
		unsigned TC :3;				//Temperature Coefficient Select
		unsigned THFT0 :1;			//ThresHold 0
		unsigned THFT1 :1;			//ThresHold 1
		unsigned PREEM_E :1;		//PRE-EMphasis Enable
		unsigned PREEM_MOD :2;		//PREEM_MOD
		unsigned PREEM_SEL :3;		//PREEM_SEL
		unsigned TLFT0 :1;
		unsigned TLFT1 :1;
	} bit;
} ssd2828_ACR3_t;
static_assert(sizeof(ssd2828_ACR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ACR3_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned GF_E :1;			//Glitch filter Enable
		unsigned GFFT0 :1;			//Glitch Filter Selection 0
		unsigned GFFT1 :1;			//Glitch Filter Selection 1
		unsigned CD_EN :1;			//Contention Detection Enable
		unsigned ENLV :1;			//BandGap Reference Enable
		unsigned TCI :3;			//Current Temperature Coefficient Select
		unsigned RES_8 :1;
		unsigned CKF :1;			//ClocK Flip
		unsigned CLK_DELAY_SEL :6;	//CLocK lane DELAY SELect
	} bit;
} ssd2828_ACR4_t;
static_assert(sizeof(ssd2828_ACR4_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ACR4_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned IAS :1;			//Interrupt Active State
		unsigned IOT :2;			//Interrupt Output Type
		unsigned RES_3_15 :13;
	} bit;
} ssd2828_IOCR_t;
static_assert(sizeof(ssd2828_IOCR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_IOCR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned VFN :4;			//Vertical Front Porch Non Video Data Window
		unsigned VBN :4;			//Vertical Back Porch Non Video Data Window
		unsigned RES_8_15 :8;
	} bit;
} ssd2828_VICR7_t;
static_assert(sizeof(ssd2828_VICR7_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VICR7_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned LS0 :2;			//Lane Select
		unsigned RES_2_15 :14;
	} bit;
} ssd2828_LCFR_t;
static_assert(sizeof(ssd2828_LCFR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_LCFR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HED :6;			//HS Exit Delay
		unsigned RES_6_15 :10;
	} bit;
} ssd2828_DAR7_t;
static_assert(sizeof(ssd2828_DAR7_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DAR7_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned MR_PULL :2;		//MIPI Reset Pull
		unsigned IS_PULL :2;		//If_Sel Pull
		unsigned PS0_PULL :2;		//Pin Select 0 Pull
		unsigned PS1_PULL :2;		//Pin Select 1 Pull
		unsigned PS2_PULL :2;		//Pin Select 2 Pull
		unsigned PS3_PULL :2;		//Pin Select 3 Pull
		unsigned PS4_PULL :2;		//Pin Select 4 Pull
		unsigned XTAL_PULL :2;		//Xtal Mode Pull
	} bit;
} ssd2828_PUCR1_t;
static_assert(sizeof(ssd2828_PUCR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PUCR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CSX_PULL :2;		//Chip Select Pull
		unsigned DL_PULL :2;		//Data low byte Pull
		unsigned DM_PULL :2;		//Data medium byte Pull
		unsigned DH_PULL :2;		//Data high byte Pull
		unsigned VS_PULL :2;		//Vsync Pull
		unsigned PC_PULL :2;		//Pixel_clk Pull
		unsigned HS_PULL :2;		//Hsync Pull
		unsigned DEN_PULL :2;		//Den Pull
	} bit;
} ssd2828_PUCR2_t;
static_assert(sizeof(ssd2828_PUCR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PUCR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CM_PULL :2;
		unsigned SHUT_PULL :2;
		unsigned SDC_PULL :2;
		unsigned SCK_PULL :2;
		unsigned SDI_PULL :2;
		unsigned RES_10_15 :6;
	} bit;
} ssd2828_PUCR3_t;
static_assert(sizeof(ssd2828_PUCR3_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_PUCR3_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CABC_EN :1;
		unsigned BP_MODE :2;
		unsigned BCTR :1;
		unsigned DD :1;
		unsigned BL :1;
		unsigned GAM18 :1;
		unsigned RES_7	:1;
		unsigned WDBV :8;
	} bit;
} ssd2828_CBCR1_t;
static_assert(sizeof(ssd2828_CBCR1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_CBCR1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned CABC_MB :8;
		unsigned BCB_PS :4;
		unsigned PWM_PS	:4;
	} bit;
} ssd2828_CBCR2_t;
static_assert(sizeof(ssd2828_CBCR2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_CBCR2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned RDBV :8;
		unsigned BCL :1;
		unsigned RES_9_11 :3;
		unsigned VGA_SEL :4;
	} bit;
} ssd2828_CBSR_t;
static_assert(sizeof(ssd2828_CBSR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_CBSR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned ENC_EN :1;
		unsigned ENC_MODE :1;
		unsigned RES_2_3 :2;
		unsigned ENC_LW :12;
	} bit;
} ssd2828_ECR_t;
static_assert(sizeof(ssd2828_ECR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ECR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned HSD :8;
		unsigned VSD :8;
	} bit;
} ssd2828_VSDR_t;
static_assert(sizeof(ssd2828_VSDR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_VSDR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned TRIM_CMD :8;
		unsigned TRIM_EN :1;
		unsigned VBIST_EN :1;
		unsigned VBIST_SRT :1;
		unsigned XORC_EN :1;
		unsigned XORC_SEL :1;
		unsigned XORC_DONE :1;
		unsigned TRIM_PASS :1;
		unsigned TRIM_DONE :1;
	} bit_trim;
	struct PACKED {
		unsigned XORC_FILTER :4;
		unsigned RES_4_7 :4;
		unsigned TRIM_EN :1;
		unsigned VBIST_EN :1;
		unsigned VBIST_SRT :1;
		unsigned XORC_EN :1;
		unsigned XORC_SEL :1;
		unsigned XORC_DONE :1;
		unsigned TRIM_PASS :1;
		unsigned TRIM_DONE :1;
	} bit_xorc;
} ssd2828_TMR_t;
static_assert(sizeof(ssd2828_TMR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_TMR_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned GPIO0_CTR :7;
		unsigned GPIO0_STAT :1;
		unsigned GPIO1_CTR :7;
		unsigned GPIO1_STAT :1;
	} bit;
} ssd2828_GPIO1_t;
static_assert(sizeof(ssd2828_GPIO1_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_GPIO1_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned GPIO2_CTR :7;
		unsigned GPIO2_STAT :1;
		unsigned RES_8_16 :8;
	} bit;
} ssd2828_GPIO2_t;
static_assert(sizeof(ssd2828_GPIO2_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_GPIO2_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DELAY_A_0 :6;
		unsigned RES_6_7 :2;
		unsigned DELAY_A_1 :6;
		unsigned RES_14_15 :2;
	} bit;
} ssd2828_DLYA01_t;
static_assert(sizeof(ssd2828_DLYA01_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DLYA01_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DELAY_A_2 :6;
		unsigned RES_6_7 :2;
		unsigned DELAY_A_3 :6;
		unsigned RES_14_15 :2;
	} bit;
} ssd2828_DLYA23_t;
static_assert(sizeof(ssd2828_DLYA23_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DLYA23_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DELAY_B_0 :6;
		unsigned RES_6_7 :2;
		unsigned DELAY_B_1 :6;
		unsigned RES_14_15 :2;
	} bit;
} ssd2828_DLYB01_t;
static_assert(sizeof(ssd2828_DLYB01_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DLYB01_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DELAY_B_2 :6;
		unsigned RES_6_7 :2;
		unsigned DELAY_B_3 :6;
		unsigned RES_14_15 :2;
	} bit;
} ssd2828_DLYB23_t;
static_assert(sizeof(ssd2828_DLYB23_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DLYB23_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DELAY_C_0 :6;
		unsigned RES_6_7 :2;
		unsigned DELAY_C_1 :6;
		unsigned RES_14_15 :2;
	} bit;
} ssd2828_DLYC01_t;
static_assert(sizeof(ssd2828_DLYC01_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DLYC01_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned DELAY_C_2 :6;
		unsigned RES_6_7 :2;
		unsigned DELAY_C_3 :6;
		unsigned RES_14_15 :2;
	} bit;
} ssd2828_DLYC23_t;
static_assert(sizeof(ssd2828_DLYC23_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_DLYC23_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned REG_CTR :1;
		unsigned XOR_TUNE_EN :1;
		unsigned D0_FB_E :1;
		unsigned D1_FB_E :1;
		unsigned D2_FB_E :1;
		unsigned D3_FB_E :1;
		unsigned DEC_FB_E :1;
		unsigned DEC_XOR_E :1;
		unsigned RES_8_15 :8;
	} bit;
} ssd2828_ACR5_t;
static_assert(sizeof(ssd2828_ACR5_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_ACR5_t!");

typedef union {
	uint16_t all;
	uint8_t byte[SSD2828_DATA_SIZE];
	struct PACKED {
		unsigned RD :16;
	} bit;
} ssd2828_RR_t;
static_assert(sizeof(ssd2828_RR_t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828_RR_t!");

/*
typedef union {
	uint16_t all;
	struct PACKED {
		unsigned
	} bit;
} ssd2828__t;
static_assert(sizeof(ssd2828__t) == SSD2828_DATA_SIZE, "Invalid size of ssd2828__t!");
*/

typedef struct {
	uint32_t data_count;
	uint8_t* data_array;
} mipi_reg_t;


#endif /* SSD2828_H_ */
