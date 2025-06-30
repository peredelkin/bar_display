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
	SSD2828_send_cmd(0xbc); //Packet Size Control Register 1
	SSD2828_send_data(num & 0xff);
	SSD2828_send_data((num >> 8) & 0xff);
	SSD2828_send_cmd(0xbf); //Packet Drop Register
}

SSD2828_initial() {

	SSD2828_send_cmd(0xb7);  //Configuration Register
	SSD2828_send_data(0x50); //DCS = 0x1, HCLK = 0x1
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xb8);  //VC Control Register
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xb9);  //PLL Control Register
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xBA);  //PLL Configuration Register
	SSD2828_send_data(0x25); //NS = 0x25
	SSD2828_send_data(0x82); //FR = 0x2, MS = 0x2

	SSD2828_send_cmd(0xBB);  //Clock Control Register
	SSD2828_send_data(0x07); //LPD = 0x7
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xb9); //PLL Control Register
	SSD2828_send_data(0x01); //PEN = 0x1
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xDE);  //Lane Configuration Register
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xc9);  //Delay Adjustment Register 1
	SSD2828_send_data(0x02); //HPD = 0x02
	SSD2828_send_data(0x23); //HZD = 0x23

	SSD2828_send_cmd(0xCA); //Delay Adjustment Register 2
	SSD2828_send_data(0x01); //CPD = 0x1
	SSD2828_send_data(0x23); //CZD = 0x23

	SSD2828_send_cmd(0xCB);  //Delay Adjustment Register 3
	SSD2828_send_data(0x10); //CPTD = 0x10
	SSD2828_send_data(0x05); //CPED = 0x05

	SSD2828_send_cmd(0xCC); //Delay Adjustment Register 4
	SSD2828_send_data(0x05); //HTD = 0x05
	SSD2828_send_data(0x10); //CTD = 0x10
			/*============================================================================*/

	//LCD driver initialization
	SSD2828_send_cmd(0xB7);  //Configuration Register
	SSD2828_send_data(0x50); //DCS = 0x1, HCLK = 0x1
	SSD2828_send_data(0x02); //EOT = 0x1

	SSD2828_send_cmd(0xBD);  //Packet Size Control Register 2
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);
////////////////////////////////////////////

	SSD2828_send_acmd(1);
	SSD2828_send_data(0x10);  //DCS_ENTER_SLEEP_MODE?

	SSD2828_send_acmd(2);
	SSD2828_send_data(0xCD); //MIPI Address : 0xCD
	SSD2828_send_data(0xAA); //CD= 0xAA ¡ú Enter fiti command.

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x41); //MIPI Address : 0X41
	SSD2828_send_data(0x34); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x30); //MIPI Address : 0x30
	SSD2828_send_data(0x00); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x39);  //MIPI Address : 0X39
	SSD2828_send_data(0x11); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x32); //MIPI Address : 0x32
	SSD2828_send_data(0x00); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x33);  //MIPI Address : 0X33
	SSD2828_send_data(0x38); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x35); //MIPI Address : 0X35
	SSD2828_send_data(0x24); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x4F); //MIPI Address : 0x4F
	SSD2828_send_data(0x35); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x4E); //MIPI Address : 0x4E
	SSD2828_send_data(0x27); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x41); //MIPI Address : 0X41
	SSD2828_send_data(0x56);  //

	SSD2828_send_acmd(9);
	SSD2828_send_data(0x55); //MIPI Address : 0X55
	SSD2828_send_data(0x00); //gstv1_rise
	SSD2828_send_data(0x0F); //gstv1_fall
	SSD2828_send_data(0x00); //gstv2_rise
	SSD2828_send_data(0x0F); //gstv2_fall
	SSD2828_send_data(0x00); //gstv3_rise
	SSD2828_send_data(0x0F); //gstv3_fall
	SSD2828_send_data(0x00); //gstv4_rise
	SSD2828_send_data(0x0F); //gstv4_fall

	SSD2828_send_acmd(17);
	SSD2828_send_data(0x56); //MIPI Address : 0X56
	SSD2828_send_data(0x00); //gckv1_rise
	SSD2828_send_data(0x0F);  //gckv1_fall
	SSD2828_send_data(0x00); //gckv2_rise
	SSD2828_send_data(0x0F); //gckv2_fall
	SSD2828_send_data(0x00);  //gckv3_rise
	SSD2828_send_data(0x0F); //gckv3_fall
	SSD2828_send_data(0x00); //gckv4_rise
	SSD2828_send_data(0x0F); //gckv4_fall
	SSD2828_send_data(0x00);  //gckv5_rise:
	SSD2828_send_data(0x0F); //gckv5_fall
	SSD2828_send_data(0x00); //gckv6_rise
	SSD2828_send_data(0x0F); //gckv6_fall
	SSD2828_send_data(0x00);  //gckv7_rise
	SSD2828_send_data(0x0F); //gckv7_fall
	SSD2828_send_data(0x00); //gckv8_rise
	SSD2828_send_data(0x0F);  //gckv8_fall

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x65); //MIPI Address : 0X65
	SSD2828_send_data(0x08); //goa_updn: Forward

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x3A); //MIPI Address : 0X3A
	SSD2828_send_data(0x08);  //dummy_sel: 8 clk

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x36); //MIPI Address : 0X36
	SSD2828_send_data(0x49); //

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x67); //MIPI Address : 0X67
	SSD2828_send_data(0x82);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x69); //MIPI Address : 0X69
	SSD2828_send_data(0x20);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x6C); //MIPI Address : 0X6C
	SSD2828_send_data(0x80);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x6D);  //MIPI Address : 0X6D
	SSD2828_send_data(0x01);

	SSD2828_send_acmd(20);
	SSD2828_send_data(0x53); //MIPI Address : 0X53
	SSD2828_send_data(0x1F); //GP_00:Setting gamma positive voltage for level 255 .
	SSD2828_send_data(0x19); //GP_01:Setting gamma positive voltage for level 253 .
	SSD2828_send_data(0x15); //GP_02:Setting gamma positive voltage for level 250 .
	SSD2828_send_data(0x11); //GP_03:Setting gamma positive voltage for level 246 .
	SSD2828_send_data(0x11); //GP_04:Setting gamma positive voltage for level 240 .
	SSD2828_send_data(0x11); //GP_05:Setting gamma positive voltage for level 232 .
	SSD2828_send_data(0x12); //GP_06:Setting gamma positive voltage for level 224 .
	SSD2828_send_data(0x14); //GP_07:Setting gamma positive voltage for level 208 .
	SSD2828_send_data(0x15); //GP_08:Setting gamma positive voltage for level 176 .
	SSD2828_send_data(0x11); //GP_09:Setting gamma positive voltage for level 128 .
	SSD2828_send_data(0x0D);  //GP_10:Setting gamma positive voltage for level 80 .
	SSD2828_send_data(0x0B); //GP_11:Setting gamma positive voltage for level 48 .
	SSD2828_send_data(0x0B); //GP_12:Setting gamma positive voltage for level 30 .
	SSD2828_send_data(0x0D); //GP_13:Setting gamma positive voltage for level 22 .
	SSD2828_send_data(0x0C);  //GP_14:Setting gamma positive voltage for level 14 .
	SSD2828_send_data(0x0C); //GP_15:Setting gamma positive voltage for level 8 .
	SSD2828_send_data(0x08); //GP_16:Setting gamma positive voltage for level 4 .
	SSD2828_send_data(0x04); //GP_17:Setting gamma positive voltage for level 2 .
	SSD2828_send_data(0x00); //GP_18:Setting gamma positive voltage for level 0 .

	SSD2828_send_acmd(20);
	SSD2828_send_data(0x54); //MIPI Address : 0X54
	SSD2828_send_data(0x1F);  //GN_00: Setting gamma negative voltage for level 255 .
	SSD2828_send_data(0x19); //GN_01: Setting gamma negative voltage for level 253 .
	SSD2828_send_data(0x15); //GN_02: Setting gamma negative voltage for level 250 .
	SSD2828_send_data(0x11); //GN_03: Setting gamma negative voltage for level 246 .
	SSD2828_send_data(0x11); //GN_04: Setting gamma negative voltage for level 240 .
	SSD2828_send_data(0x11); //GN_05: Setting gamma negative voltage for level 232 .
	SSD2828_send_data(0x13); //GN_06: Setting gamma negative voltage for level 224 .
	SSD2828_send_data(0x15); //GN_07: Setting gamma negative voltage for level 208 .
	SSD2828_send_data(0x16); //GN_08: Setting gamma negative voltage for level 176 .
	SSD2828_send_data(0x11); //GN_09: Setting gamma negative voltage for level 128 .
	SSD2828_send_data(0x0D); //GN_10: Setting gamma negative voltage for level 80 .
	SSD2828_send_data(0x0C); //GN_11: Setting gamma negative voltage for level 48 .
	SSD2828_send_data(0x0C); //GN_12: Setting gamma negative voltage for level 30 .
	SSD2828_send_data(0x0E); //GN_13: Setting gamma negative voltage for level 22 .
	SSD2828_send_data(0x0C); //GN_14: Setting gamma negative voltage for level 14 .
	SSD2828_send_data(0x0C); //GN_15: Setting gamma negative voltage for level 8 .
	SSD2828_send_data(0x08); //GN_16: Setting gamma negative voltage for level 4 .
	SSD2828_send_data(0x04); //GN_17: Setting gamma negative voltage for level 2 .
	SSD2828_send_data(0x00); //GN_18: Setting gamma negative voltage for level 0 .

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x6B); //MIPI Address : 0X6B
	SSD2828_send_data(0x00);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x58); //MIPI Address : 0X58
	SSD2828_send_data(0x00);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x73); //MIPI Address : 0X73
	SSD2828_send_data(0xF0);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x76); //?
	SSD2828_send_data(0x40);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x77); //MIPI Address : 0X77
	SSD2828_send_data(0x04);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x74); //MIPI Address : 0X74
	SSD2828_send_data(0x17);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x5E); //MIPI Address : 0X5E
	SSD2828_send_data(0x03);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x68); //MIPI Address : 0X68
	SSD2828_send_data(0x10);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x6A); //MIPI Address : 0X6A
	SSD2828_send_data(0x00);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x28); //MIPI Address : 0x28
	SSD2828_send_data(0x31); //28=¡±31¡± ¡ú LEDON pin output power enable signal.

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x29); //MIPI Address : 0x29
	SSD2828_send_data(0x21); //? 29=¡±01¡± ¡ú Only for 400RGBx1280 resolution.

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x63); //MIPI Address : 0X63
	SSD2828_send_data(0x04);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x27); //MIPI Address : 0x27
	SSD2828_send_data(0x00); //? 27=¡±00¡± ¡ú Lock OTP register.

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x7C); //?
	SSD2828_send_data(0x80);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x2E); //MIPI Address : 0x2E
	SSD2828_send_data(0x05); //PWRIC_CLK1 = 0x05 ¡ú 118.25 kHz

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x4C); //?
	SSD2828_send_data(0x80);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x50); //?
	SSD2828_send_data(0xC0);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x78); //MIPI Address : 0x78
	SSD2828_send_data(0x6E); //VGH_REG_SEL = 0x6E ¡ú 13.29V

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x2D); //MIPI Address : 0x2D
	SSD2828_send_data(0x31); //? VGL_REG_SEL = 0x31 ¡ú -11.04V

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x49); //?
	SSD2828_send_data(0x00);

	SSD2828_send_acmd(2);
	SSD2828_send_data(0x4D); //MIPI Address : 0x4D
	SSD2828_send_data(0x00); //4D=¡±00¡± ¡ú Exit fiti command.

	SSD2828_send_acmd(1);
	SSD2828_send_data(0x11); //DCS_EXIT_SLEEP_MODE
	delay_ms(120);
	SSD2828_send_acmd(1);
	SSD2828_send_data(0x29);  //DCS_SET_DISPLAY_ON
	delay_ms(120);

	SSD2828_send_cmd(0xb7);
	SSD2828_send_data(0x50);
	SSD2828_send_data(0x00);   //Configuration Register

	SSD2828_send_cmd(0xb8);
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);   //VC(Virtual ChannelID) Control Register

	SSD2828_send_cmd(0xb9);
	SSD2828_send_data(0x00);   //1=PLL disable
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xBA);   //
	SSD2828_send_data(0x25);   //14,D7-0=NS(0x01 : NS=1)
	SSD2828_send_data(0x82);   //42,D15-14=PLL00=62.5-125 01=126-250 10=251-500 11=501-1000  DB12-8=MS(01:MS=1)

	SSD2828_send_cmd(0xBB);   //LP Clock Divider LP clock = 400MHz / LPD / 8 = 480 / 8/ 8 = 7MHz
	SSD2828_send_data(0x07);   //D5-0=LPD=0x1 šC Divide by 2
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xb9);
	SSD2828_send_data(0x01);   //1=PLL disable
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xc9);
	SSD2828_send_data(0x02);
	SSD2828_send_data(0x23);   //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
	delay_ms(100);

	SSD2828_send_cmd(0xCA);
	SSD2828_send_data(0x01);   //CLK Prepare
	SSD2828_send_data(0x23);   //Clk Zero

	SSD2828_send_cmd(0xCB); //local_write_reg(addr=0xCB,data=0x0510)
	SSD2828_send_data(0x10); //Clk Post
	SSD2828_send_data(0x05); //Clk Per

	SSD2828_send_cmd(0xCC); //local_write_reg(addr=0xCC,data=0x100A)
	SSD2828_send_data(0x05); //HS Trail
	SSD2828_send_data(0x10); //Clk Trail

	SSD2828_send_cmd(0xD0);
	SSD2828_send_data(0x00);
	SSD2828_send_data(0x00);

	//RGB interface configuration
	SSD2828_send_cmd(0xB1);
	SSD2828_send_data(0x18); //HSPW 07
	SSD2828_send_data(0x02); //VSPW 05

	SSD2828_send_cmd(0xB2);
	SSD2828_send_data(0xa0); //HBPD 0x64=100
	SSD2828_send_data(0x0a); //VBPD 8 ŒõÐ¡ÏÂÒÆ

	SSD2828_send_cmd(0xB3);
	SSD2828_send_data(0xa0); //HFPD 8
	SSD2828_send_data(0x0c); //VFPD 10

	SSD2828_send_cmd(0xB4); //Horizontal active period 720=02D0
	SSD2828_send_data(0x90); //013F=319 02D0=720
	SSD2828_send_data(0x01);

	SSD2828_send_cmd(0xB5); //Vertical active period 1280=0500
	SSD2828_send_data(0x00); //01DF=479 0500=1280
	SSD2828_send_data(0x05);

	SSD2828_send_cmd(0xB6); //RGB CLK  16BPP=00 18BPP=01
	SSD2828_send_data(0x0b); //D7=0 D6=0 D5=0  D1-0=11 šC 24bpp	 //07
	SSD2828_send_data(0x00); //D15=VS D14=HS D13=CLK D12-9=NC D8=0=Video with blanking packet. 00-F0

	//MIPI lane configuration
	SSD2828_send_cmd(0xDE); //ÍšµÀÊý
	SSD2828_send_data(0x03); //11=4LANE 10=3LANE 01=2LANE 00=1LANE
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xD6); //  05=BGR  04=RGB
	SSD2828_send_data(0x05); //D0=0=RGB 1:BGR D1=1=Most significant byte sent first
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xDB);
	SSD2828_send_data(0x58);
	SSD2828_send_data(0x00);

	SSD2828_send_cmd(0xB7);
	SSD2828_send_data(0x6B);   //4b
	SSD2828_send_data(0x02);

}

