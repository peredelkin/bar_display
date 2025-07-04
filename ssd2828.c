/*
 * ssd2828.c
 *
 *  Created on: 22 февр. 2025 г.
 *      Author: ruslan
 */

#include "ssd2828.h"

__attribute__((weak)) void delay_ms(uint32_t ms) {
	(void) ms;
}

bool DC_2828; //D/C
bool SDI_2828; //MOSI
bool SCLK_2828; //CLK
bool SDO_2828; //MISO
bool CS_2828; //CS
bool RST_2828; //RST

/* SSD2828 interface define */

sbit SDI_2828 = P1 ^ 5;
sbit SCLK_2828 = P1 ^ 7;
sbit SDO_2828 = P1 ^ 6;
sbit CS_2828 = P3 ^ 6;
sbit RST_2828 = P3 ^ 4;

void SSD2828_Reset(void) {

	RST_2828 = 0;
	delay_ms(30);
	RST_2828 = 1;
	delay_ms(50);

	CS_2828 = 1;
	SCLK_2828 = 0;
	SDI_2828 = 1;

}

void SSD2828_send_cmd(unsigned int Sdata) {
	unsigned char i;

	CS_2828 = 0;
	SDI_2828 = 0;
	SCLK_2828 = 0;
	SCLK_2828 = 1;

//	for (i = 8; i > 0; i--) {
//		if (Sdata & 0x80)
//			SDI_2828 = 1;
//		else
//			SDI_2828 = 0;
//		SCLK_2828 = 0;
//		SCLK_2828 = 1;
//		Sdata <<= 1;
//	}

	SCLK_2828 = 0;
	CS_2828 = 1;
}

void SSD2828_send_data(unsigned int Sdata) {
	unsigned char i;

	CS_2828 = 0;
	SDI_2828 = 1;
	SCLK_2828 = 0;
	SCLK_2828 = 1;

//	for (i = 8; i > 0; i--) {
//		if (Sdata & 0x80)
//			SDI_2828 = 1;
//		else
//			SDI_2828 = 0;
//		SCLK_2828 = 0;
//		SCLK_2828 = 1;
//		Sdata <<= 1;
//	}

	SCLK_2828 = 0;
	CS_2828 = 1;
}

//unsigned char SSD2828_read_data(void) {
//	unsigned char i;
//	unsigned char Value = 0;
//
//	CS_2828 = 0;
//	SCLK_2828 = 0;
//
//	for (i = 0; i < 8; i++) {
//		SCLK_2828 = 0;
//		SCLK_2828 = 1;
//		Value <<= 1;
//		if (SDO_2828 == 1)
//			Value |= 0x01;
//	}
//	CS_2828 = 1;
//
//	return Value;
//}

//2014-08-29 È¥µôbd be
void SSD2828_send_acmd(unsigned int num) {
	SSD2828_send_cmd(SSD2828_ADDR_PSCR1); //Packet Size Control Register 1
	SSD2828_send_data(num & 0xff);
	SSD2828_send_data((num >> 8) & 0xff);
	SSD2828_send_cmd(SSD2828_ADDR_PDR); //Packet Drop Register
}

SSD2828_initial() {

	SSD2828_send_cmd(SSD2828_ADDR_CFGR);  //Configuration Register
	SSD2828_send_data(0x50); //DCS = 0x1, HCLK = 0x1
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_VCR);  //VC Control Register
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_PCR);  //PLL Control Register
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_PLCR);  //PLL Configuration Register
	SSD2828_send_data(0x25); //NS = 0x25
	SSD2828_send_data(0x82); //FR = 0x2, MS = 0x2

	SSD2828_send_cmd(SSD2828_ADDR_CCR);  //Clock Control Register
	SSD2828_send_data(0x07); //LPD = 0x7
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_PCR); //PLL Control Register
	SSD2828_send_data(0x01); //PEN = 0x1
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_LCFR);  //Lane Configuration Register
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_DAR1);  //Delay Adjustment Register 1
	SSD2828_send_data(0x02); //HPD = 0x02
	SSD2828_send_data(0x23); //HZD = 0x23

	SSD2828_send_cmd(SSD2828_ADDR_DAR2); //Delay Adjustment Register 2
	SSD2828_send_data(0x01); //CPD = 0x1
	SSD2828_send_data(0x23); //CZD = 0x23

	SSD2828_send_cmd(SSD2828_ADDR_DAR3);  //Delay Adjustment Register 3
	SSD2828_send_data(0x10); //CPTD = 0x10
	SSD2828_send_data(0x05); //CPED = 0x05

	SSD2828_send_cmd(SSD2828_ADDR_DAR4); //Delay Adjustment Register 4
	SSD2828_send_data(0x05); //HTD = 0x05
	SSD2828_send_data(0x10); //CTD = 0x10
			/*============================================================================*/

	//LCD driver initialization
	SSD2828_send_cmd(SSD2828_ADDR_CFGR);  //Configuration Register
	SSD2828_send_data(0x50); //DCS = 0x1, HCLK = 0x1
	SSD2828_send_data(0x02); //EOT = 0x1

	SSD2828_send_cmd(SSD2828_ADDR_PSCR2);  //Packet Size Control Register 2
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);
////////////////////////////////////////////

	SSD2828_send_acmd(1);
	SSD2828_send_data(0x10);  //DCS_ENTER_SLEEP_MODE?

	//TODO: передать массив настроек через MIPI
	//	SSD2828_send_acmd(SSD2828_REGS_COUNT);
	// передать ssd2828_mipi_reg_t

	SSD2828_send_acmd(1);
	SSD2828_send_data(0x11); //DCS_EXIT_SLEEP_MODE
	delay_ms(120);
	SSD2828_send_acmd(1);
	SSD2828_send_data(0x29);  //DCS_SET_DISPLAY_ON
	delay_ms(120);

	SSD2828_send_cmd(SSD2828_ADDR_CFGR);
	SSD2828_send_data(0x50);
	SSD2828_send_data(0x00);   //Configuration Register

	SSD2828_send_cmd(SSD2828_ADDR_VCR);
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);   //VC(Virtual ChannelID) Control Register

	SSD2828_send_cmd(SSD2828_ADDR_PCR);
	SSD2828_send_data(0x00);   //1=PLL disable
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_PLCR);   //
	SSD2828_send_data(0x25);   //14,D7-0=NS(0x01 : NS=1)
	SSD2828_send_data(0x82);   //42,D15-14=PLL00=62.5-125 01=126-250 10=251-500 11=501-1000  DB12-8=MS(01:MS=1)

	SSD2828_send_cmd(SSD2828_ADDR_CCR);   //LP Clock Divider LP clock = 400MHz / LPD / 8 = 480 / 8/ 8 = 7MHz
	SSD2828_send_data(0x07);   //D5-0=LPD=0x1 šC Divide by 2
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_PCR);
	SSD2828_send_data(0x01);   //1=PLL disable
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_DAR1);
	SSD2828_send_data(0x02);
	SSD2828_send_data(0x23);   //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
	delay_ms(100);

	SSD2828_send_cmd(SSD2828_ADDR_DAR2);
	SSD2828_send_data(0x01);   //CLK Prepare
	SSD2828_send_data(0x23);   //Clk Zero

	SSD2828_send_cmd(SSD2828_ADDR_DAR3); //local_write_reg(addr=0xCB,data=0x0510)
	SSD2828_send_data(0x10); //Clk Post
	SSD2828_send_data(0x05); //Clk Per

	SSD2828_send_cmd(SSD2828_ADDR_DAR4); //local_write_reg(addr=0xCC,data=0x100A)
	SSD2828_send_data(0x05); //HS Trail
	SSD2828_send_data(0x10); //Clk Trail

	SSD2828_send_cmd(SSD2828_ADDR_HTTR2);
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	//RGB interface configuration
	SSD2828_send_cmd(SSD2828_ADDR_VICR1);
	SSD2828_send_data(0x18); //HSPW 07
	SSD2828_send_data(0x02); //VSPW 05

	SSD2828_send_cmd(SSD2828_ADDR_VICR2);
	SSD2828_send_data(0xa0); //HBPD 0x64=100
	SSD2828_send_data(0x0a); //VBPD 8 ŒõÐ¡ÏÂÒÆ

	SSD2828_send_cmd(SSD2828_ADDR_VICR3);
	SSD2828_send_data(0xa0); //HFPD 8
	SSD2828_send_data(0x0c); //VFPD 10

	SSD2828_send_cmd(SSD2828_ADDR_VICR4); //Horizontal active period 720=02D0
	SSD2828_send_data(0x90); //013F=319 02D0=720
	SSD2828_send_data(0x01);

	SSD2828_send_cmd(SSD2828_ADDR_VICR5); //Vertical active period 1280=0500
	SSD2828_send_data(0x00); //01DF=479 0500=1280
	SSD2828_send_data(0x05);

	SSD2828_send_cmd(SSD2828_ADDR_VICR6); //RGB CLK  16BPP=00 18BPP=01
	SSD2828_send_data(0x0b); //D7=0 D6=0 D5=0  D1-0=11 šC 24bpp	 //07
	SSD2828_send_data(0x00); //D15=VS D14=HS D13=CLK D12-9=NC D8=0=Video with blanking packet. 00-F0

	//MIPI lane configuration
	SSD2828_send_cmd(SSD2828_ADDR_LCFR); //ÍšµÀÊý
	SSD2828_send_data(0x03); //11=4LANE 10=3LANE 01=2LANE 00=1LANE
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_TR); //  05=BGR  04=RGB
	SSD2828_send_data(0x05); //D0=0=RGB 1:BGR D1=1=Most significant byte sent first
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_ACR4);
	SSD2828_send_data(0x58);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(SSD2828_ADDR_CFGR);
	SSD2828_send_data(0x6B);   //4b
	SSD2828_send_data(0x02);

}

