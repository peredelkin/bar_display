#include "ssd2828.h"

#define SSD2828_ENTER_FITI_CMD_COUNT 2
static const uint8_t ssd2828_enter_fiti_cmd[SSD2828_ENTER_FITI_CMD_COUNT] = {
		0xCD,	/*MIPI Address : 0xCD*/
		0xAA	/*CD=”AA” → Enter fiti command.*/
};

#define SSD2828_EXIT_FITI_CMD_COUNT 2
static const uint8_t ssd2828_exit_fiti_cmd[SSD2828_EXIT_FITI_CMD_COUNT] = {
		0x4D,	/*MIPI Address : 0x4D*/
		0x00	/*4D=”00” → Exit fiti command.*/
};

#define SSD2828_REG_0x41_COUNT 2
static const uint8_t ssd2828_reg_0x41_0x34[SSD2828_REG_0x41_COUNT] = {
		0x41,	/*MIPI Address : 0X41*/
		0x34	/**/
};

static const uint8_t ssd2828_reg_0x41_0x56[SSD2828_REG_0x41_COUNT] = {
		0x41,	/*MIPI Address : 0X41*/
		0x56	/**/
};

#define SSD2828_REG_0x30_COUNT 2
static const uint8_t ssd2828_reg_0x30[SSD2828_REG_0x30_COUNT] = {
		0x30,	/*MIPI Address : 0x30*/
		0x00	/**/
};

#define SSD2828_REG_0x39_COUNT 2
static const uint8_t ssd2828_reg_0x39[SSD2828_REG_0x39_COUNT] = {
		0x39,	/*MIPI Address : 0X39*/
		0x11	/**/
};

#define SSD2828_REG_0x32_COUNT 2
static const uint8_t ssd2828_reg_0x32[SSD2828_REG_0x32_COUNT] = {
		0x32,	/*MIPI Address : 0x32*/
		0x00,	/**/
};

#define SSD2828_REG_0x33_COUNT 2
static const uint8_t ssd2828_reg_0x33[SSD2828_REG_0x33_COUNT] = {
		0x33,	/*MIPI Address : 0X33*/
		0x38,	/**/
};

#define SSD2828_REG_0x35_COUNT 2
static const uint8_t ssd2828_reg_0x35[SSD2828_REG_0x35_COUNT] = {
		0x35,	/*MIPI Address : 0X35*/
		0x24	/**/
};

#define SSD2828_REG_0x4F_COUNT 2
static const uint8_t ssd2828_reg_0x4F[SSD2828_REG_0x4F_COUNT] = {
		0x4F,	/*MIPI Address : 0x4F*/
		0x35	/**/
};

#define SSD2828_REG_0x4E_COUNT 2
static const uint8_t ssd2828_reg_0x4E[SSD2828_REG_0x4E_COUNT] = {
		0x4E,	/*MIPI Address : 0x4E*/
		0x27	/**/
};

#define SSD2828_GSTV_COUNT 9
static const uint8_t ssd2828_gstv[SSD2828_GSTV_COUNT] = {
		0x55,	/*MIPI Address : 0X55*/
		0x00,	/*gstv1_rise*/
		0x0F,	/*gstv1_fall*/
		0x00,	/*gstv2_rise*/
		0x0F,	/*gstv2_fall*/
		0x00,	/*gstv3_rise*/
		0x0F,	/*gstv3_fall*/
		0x00,	/*gstv4_rise*/
		0x0F	/*gstv4_fall*/
};

#define SSD2828_GCKV_COUNT 17
static const uint8_t ssd2828_gckv[SSD2828_GCKV_COUNT] = {
		0x56,	/*MIPI Address : 0X56*/
		0x00,	/*gckv1_rise*/
		0x0F,	/*gckv1_fall*/
		0x00,	/*gckv2_rise*/
		0x0F,	/*gckv2_fall*/
		0x00,	/*gckv3_rise*/
		0x0F,	/*gckv3_fall*/
		0x00,	/*gckv4_rise*/
		0x0F,	/*gckv4_fall*/
		0x00,	/*gckv5_rise*/
		0x0F,	/*gckv5_fall*/
		0x00,	/*gckv6_rise*/
		0x0F,	/*gckv6_fall*/
		0x00,	/*gckv7_rise*/
		0x0F,	/*gckv7_fall*/
		0x00,	/*gckv8_rise*/
		0x0F,	/*gckv8_fall*/
};

#define SSD2828_REG_0x65_COUNT 2
static const uint8_t ssd2828_reg_0x65[SSD2828_REG_0x65_COUNT] = {
		0x65,	/*MIPI Address : 0X65*/
		0x08	/*goa_updn: Forward*/
};

#define SSD2828_REG_0x3A_COUNT 2
static const uint8_t ssd2828_reg_0x3A[SSD2828_REG_0x3A_COUNT] = {
		0x3A,	/*MIPI Address : 0X3A*/
		0x08	/*dummy_sel: 8 clk*/
};

#define SSD2828_REG_0x36_COUNT 2
static const uint8_t ssd2828_reg_0x36[SSD2828_REG_0x36_COUNT] = {
		0x36,	/*MIPI Address : 0X36*/
		0x49	/**/
};

#define SSD2828_REG_0x67_COUNT 2
static const uint8_t ssd2828_reg_0x67[SSD2828_REG_0x67_COUNT] = {
		0x67,	/*MIPI Address : 0X67*/
		0x82	/**/
};

#define SSD2828_REG_0x69_COUNT 2
static const uint8_t ssd2828_reg_0x69[SSD2828_REG_0x69_COUNT] = {
		0x69,	/*MIPI Address : 0X69*/
		0x20	/**/
};

#define SSD2828_REG_0x6C_COUNT 2
static const uint8_t ssd2828_reg_0x6C[SSD2828_REG_0x6C_COUNT] = {
		0x6C,	/*MIPI Address : 0X6C*/
		0x80	/**/
};

#define SSD2828_REG_0x6D_COUNT 2
static const uint8_t ssd2828_reg_0x6D[SSD2828_REG_0x6D_COUNT] = {
		0x6D,	/*MIPI Address : 0X6D*/
		0x01	/**/
};

#define SSD2828_POS_GAMMA_COUNT 20
static const uint8_t ssd2828_pos_gamma[SSD2828_POS_GAMMA_COUNT] = {
		0x53, /*MIPI Address : 0X53*/
		0x1F, /*GP_00:Setting gamma positive voltage for level 255*/
		0x19, /*GP_01:Setting gamma positive voltage for level 253*/
		0x15, /*GP_02:Setting gamma positive voltage for level 250*/
		0x11, /*GP_03:Setting gamma positive voltage for level 246*/
		0x11, /*GP_04:Setting gamma positive voltage for level 240*/
		0x11, /*GP_05:Setting gamma positive voltage for level 232*/
		0x12, /*GP_06:Setting gamma positive voltage for level 224*/
		0x14, /*GP_07:Setting gamma positive voltage for level 208*/
		0x15, /*GP_08:Setting gamma positive voltage for level 176*/
		0x11, /*GP_09:Setting gamma positive voltage for level 128*/
		0x0D, /*GP_10:Setting gamma positive voltage for level 80*/
		0x0B, /*GP_11:Setting gamma positive voltage for level 48*/
		0x0B, /*GP_12:Setting gamma positive voltage for level 30*/
		0x0D, /*GP_13:Setting gamma positive voltage for level 22*/
		0x0C, /*GP_14:Setting gamma positive voltage for level 14*/
		0x0C, /*GP_15:Setting gamma positive voltage for level 8*/
		0x08, /*GP_16:Setting gamma positive voltage for level 4*/
		0x04, /*GP_17:Setting gamma positive voltage for level 2*/
		0x00 /*GP_18:Setting gamma positive voltage for level 0*/
};

#define SSD2828_NEG_GAMMA_COUNT 20
static const uint8_t ssd2828_neg_gamma[SSD2828_NEG_GAMMA_COUNT] = {
		0x54,	/*MIPI Address : 0X54*/
		0x1F,	/*GN_00: Setting gamma negative voltage for level 255*/
		0x19,	/*GN_01: Setting gamma negative voltage for level 253*/
		0x15,	/*GN_02: Setting gamma negative voltage for level 250*/
		0x11,	/*GN_03: Setting gamma negative voltage for level 246*/
		0x11,	/*GN_04: Setting gamma negative voltage for level 240*/
		0x11,	/*GN_05: Setting gamma negative voltage for level 232*/
		0x13,	/*GN_06: Setting gamma negative voltage for level 224*/
		0x15,	/*GN_07: Setting gamma negative voltage for level 208*/
		0x16,	/*GN_08: Setting gamma negative voltage for level 176*/
		0x11,	/*GN_09: Setting gamma negative voltage for level 128*/
		0x0D,	/*GN_10: Setting gamma negative voltage for level 80*/
		0x0C,	/*GN_11: Setting gamma negative voltage for level 48*/
		0x0C,	/*GN_12: Setting gamma negative voltage for level 30*/
		0x0E,	/*GN_13: Setting gamma negative voltage for level 22*/
		0x0C,	/*GN_14: Setting gamma negative voltage for level 14*/
		0x0C,	/*GN_15: Setting gamma negative voltage for level 8*/
		0x08,	/*GN_16: Setting gamma negative voltage for level 4*/
		0x04,	/*GN_17: Setting gamma negative voltage for level 2*/
		0x00	/*GN_18: Setting gamma negative voltage for level 0*/
};

#define SSD2828_REG_0x6B_COUNT 2
static const uint8_t ssd2828_reg_0x6B[SSD2828_REG_0x6B_COUNT] = {
		0x6B,	/*MIPI Address : 0X6B*/
		0x00	/**/
};

#define SSD2828_REG_0x58_COUNT 2
static const uint8_t ssd2828_reg_0x58[SSD2828_REG_0x58_COUNT] = {
		0x58,	/*MIPI Address : 0X58*/
		0x00	/**/
};

#define SSD2828_REG_0x73_COUNT 2
static const uint8_t ssd2828_reg_0x73[SSD2828_REG_0x73_COUNT] = {
		0x73,	/*MIPI Address : 0X73*/
		0xF0	/**/
};

#define	SSD2828_REG_0x76_COUNT 2
static const uint8_t ssd2828_reg_0x76[SSD2828_REG_0x76_COUNT] = {
		0x76,	/**/
		0x40	/**/
};

#define SSD2828_REG_0x77_COUNT 2
static const uint8_t ssd2828_reg_0x77[SSD2828_REG_0x77_COUNT] = {
		0x77,	/*MIPI Address : 0X77*/
		0x04	/**/
};

#define SSD2828_REG_0x74_COUNT 2
static const uint8_t ssd2828_reg_0x74[SSD2828_REG_0x74_COUNT] = {
		0x74,	/*MIPI Address : 0X74*/
		0x17	/**/
};

#define SSD2828_REG_0x5E_COUNT 2
static const uint8_t ssd2828_reg_0x5E[SSD2828_REG_0x5E_COUNT] = {
		0x5E,	/*MIPI Address : 0X5E*/
		0x03	/**/
};

#define SSD2828_REG_0x68_COUNT 2
static const uint8_t ssd2828_reg_0x68[SSD2828_REG_0x68_COUNT] = {
		0x68,	/*MIPI Address : 0X68*/
		0x10	/**/
};

#define SSD2828_REG_0x6A_COUNT 2
static const uint8_t ssd2828_reg_0x6A[SSD2828_REG_0x6A_COUNT] = {
		0x6A,	/*MIPI Address : 0X6A*/
		0x00	/**/
};

#define SSD2828_REG_0x28_COUNT 2
static const uint8_t ssd2828_reg_0x28[SSD2828_REG_0x28_COUNT] = {
		0x28,	/*MIPI Address : 0x28*/
		0x31	/*28=”31” → LEDON pin output power enable signal.*/
};

#define SSD2828_REG_0x29_COUNT 2
static const uint8_t ssd2828_reg_0x29[SSD2828_REG_0x29_COUNT] = {
		0x29,	/*MIPI Address : 0x29*/
		0x21	/*29=”01” → Only for 400RGBx1280 resolution..*/
};

#define SSD2828_REG_0x63_COUNT 2
static const uint8_t ssd2828_reg_0x63[SSD2828_REG_0x63_COUNT] = {
		0x63,	/*MIPI Address : 0X63*/
		0x04	/**/
};

#define SSD2828_REG_0x27_COUNT 2
static const uint8_t ssd2828_reg_0x27[SSD2828_REG_0x27_COUNT] = {
		0x27,	/*MIPI Address : 0x27*/
		0x00	/*27=”00” → Lock OTP register.*/
};

#define SSD2828_REG_0x7C_COUNT 2
static const uint8_t ssd2828_reg_0x7C[SSD2828_REG_0x7C_COUNT] = {
		0x7C,	/*?*/
		0x80	/**/
};

#define SSD2828_REG_0x2E_COUNT 2
static const uint8_t ssd2828_reg_0x2E[SSD2828_REG_0x2E_COUNT] = {
		0x2E,	/*MIPI Address : 0x2E*/
		0x05	/*PWRIC_CLK1 = 0x05 ¡ú 118.25 kHz*/
};

#define SSD2828_REG_0x4C_COUNT 2
static const uint8_t ssd2828_reg_0x4C[SSD2828_REG_0x4C_COUNT] = {
		0x4C,	/*?*/
		0x80	/**/
};

#define SSD2828_REG_0x50_COUNT 2
static const uint8_t ssd2828_reg_0x50[SSD2828_REG_0x50_COUNT] = {
		0x50,	/*?*/
		0xC0	/**/
};

#define SSD2828_REG_0x78_COUNT 2
static const uint8_t ssd2828_reg_0x78[SSD2828_REG_0x78_COUNT] = {
		0x78,	/*MIPI Address : 0x78*/
		0x6E	/*VGH_REG_SEL = 0x6E ¡ú 13.29V*/
};

#define SSD2828_REG_0x2D_COUNT 2
static const uint8_t ssd2828_reg_0x2D[SSD2828_REG_0x2D_COUNT] = {
		0x2D,	/*MIPI Address : 0x2D*/
		0x31	/*? VGL_REG_SEL = 0x31 ¡ú -11.04V*/
};

#define SSD2828_REG_0x49_COUNT 2
static const uint8_t ssd2828_reg_0x49[SSD2828_REG_0x49_COUNT] = {
		0x49,	/*?*/
		0x00	/**/
};

typedef struct {
	uint32_t data_count;
	uint8_t* data_array;
} ssd2828_mipi_reg_t;

#define SSD2828_REGS_COUNT 42
static const ssd2828_mipi_reg_t[SSD2828_REGS_COUNT] = {
		{
				.data_count = SSD2828_ENTER_FITI_CMD_COUNT,
				.data_array = ssd2828_enter_fiti_cmd
		},

		{
				.data_count = SSD2828_REG_0x41_COUNT,
				.data_array = ssd2828_reg_0x41_0x34
		},

		{
				.data_count = SSD2828_REG_0x30_COUNT,
				.data_array = ssd2828_reg_0x30
		},

		{
				.data_count = SSD2828_REG_0x39_COUNT,
				.data_array = ssd2828_reg_0x39
		},

		{
				.data_count = SSD2828_REG_0x32_COUNT,
				.data_array = передать ssd2828_reg_0x32
		},

		{
				.data_count = SSD2828_REG_0x33_COUNT,
				.data_array = ssd2828_reg_0x33
		},

		{
				.data_count = SSD2828_REG_0x35_COUNT,
				.data_array = ssd2828_reg_0x35
		},

		{
				.data_count = SSD2828_REG_0x4F_COUNT,
				.data_array = ssd2828_reg_0x4F
		},

		{
				.data_count = SSD2828_REG_0x4E_COUNT,
				.data_array = ssd2828_reg_0x4E
		},

		{
				.data_count = SSD2828_REG_0x41_COUNT,
				.data_array = ssd2828_reg_0x41_0x56
		},

		{
				.data_count = SSD2828_GSTV_COUNT,
				.data_array = ssd2828_gstv
		},

		{
				.data_count = SSD2828_GCKV_COUNT,
				.data_array = ssd2828_gckv
		},

		{
				.data_count = SSD2828_REG_0x65_COUNT,
				.data_array = ssd2828_reg_0x65
		},

		{
				.data_count = SSD2828_REG_0x3A_COUNT,
				.data_array = ssd2828_reg_0x3A
		},

		{
				.data_count = SSD2828_REG_0x36_COUNT,
				.data_array = ssd2828_reg_0x36
		},

		{
				.data_count = SSD2828_REG_0x67_COUNT,
				.data_array = ssd2828_reg_0x67
		},

		{
				.data_count = SSD2828_REG_0x69_COUNT,
				.data_array = ssd2828_reg_0x69
		},

		{
				.data_count = SSD2828_REG_0x6C_COUNT,
				.data_array = ssd2828_reg_0x6C
		},

		{
				.data_count = SSD2828_REG_0x6D_COUNT,
				.data_array = ssd2828_reg_0x6D
		},

		{
				.data_count = SSD2828_POS_GAMMA_COUNT,
				.data_array = ssd2828_pos_gamma
		},

		{
				.data_count = SSD2828_NEG_GAMMA_COUNT,
				.data_array = ssd2828_neg_gamma
		},

		{
				.data_count = SSD2828_REG_0x6B_COUNT,
				.data_array = ssd2828_reg_0x6B
		},

		{
				.data_count = SSD2828_REG_0x58_COUNT,
				.data_array = ssd2828_reg_0x58
		},

		{
				.data_count = SSD2828_REG_0x73_COUNT,
				.data_array = ssd2828_reg_0x73
		},

		{
				.data_count = SSD2828_REG_0x76_COUNT,
				.data_array = ssd2828_reg_0x76
		},

		{
				.data_count = SSD2828_REG_0x77_COUNT,
				.data_array = ssd2828_reg_0x77
		},

		{
				.data_count = SSD2828_REG_0x74_COUNT,
				.data_array = ssd2828_reg_0x74
		},

		{
				.data_count = SSD2828_REG_0x5E_COUNT,
				.data_array = ssd2828_reg_0x5E
		},

		{
				.data_count = SSD2828_REG_0x68_COUNT,
				.data_array = ssd2828_reg_0x68
		},

		{
				.data_count = SSD2828_REG_0x6A_COUNT,
				.data_array = ssd2828_reg_0x6A
		},

		{
				.data_count = SSD2828_REG_0x28_COUNT,
				.data_array = ssd2828_reg_0x28
		},

		{
				.data_count = SSD2828_REG_0x29_COUNT,
				.data_array = ssd2828_reg_0x29
		},

		{
				.data_count = SSD2828_REG_0x63_COUNT,
				.data_array = ssd2828_reg_0x63
		},

		{
				.data_count = SSD2828_REG_0x27_COUNT,
				.data_array = ssd2828_reg_0x27
		},

		{
				.data_count = SSD2828_REG_0x7C_COUNT,
				.data_array = ssd2828_reg_0x7C
		},

		{
				.data_count = SSD2828_REG_0x2E_COUNT,
				.data_array = ssd2828_reg_0x2E
		},

		{
				.data_count = SSD2828_REG_0x4C_COUNT,
				.data_array = ssd2828_reg_0x4C
		},

		{
				.data_count = SSD2828_REG_0x50_COUNT,
				.data_array = ssd2828_reg_0x50
		},

		{
				.data_count = SSD2828_REG_0x78_COUNT,
				.data_array = ssd2828_reg_0x78
		},

		{
				.data_count = SSD2828_REG_0x2D_COUNT,
				.data_array = ssd2828_reg_0x2D
		},

		{
				.data_count = SSD2828_REG_0x49_COUNT,
				.data_array = ssd2828_reg_0x49
		},

		{
				.data_count = SSD2828_EXIT_FITI_CMD_COUNT,
				.data_array = ssd2828_exit_fiti_cmd
		}
};
