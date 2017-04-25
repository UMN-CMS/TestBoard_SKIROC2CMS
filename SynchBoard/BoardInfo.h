#ifndef BOARD_DATA
#define BOARD_DATA



// PAGE used to power cycle the ORM's and CTL
#define FPGA_POWER_PAGE 0xF


// ORM PAGE Definitions
// Could also use an enum for this...
#define ORM0_PAGE 0x2
#define ORM0_CONFIG_PAGE 0x3
#define ORM1_PAGE 0x4
#define ORM1_CONFIG_PAGE 0x5
#define ORM2_PAGE 0x6
#define ORM2_CONFIG_PAGE 0x7
#define ORM3_PAGE 0x8
#define ORM3_CONFIG_PAGE 0x9
#define CTL_ORM_PAGE 0x10
#define CTL_CONFIG_PAGE 0x11


// ORM Flash Memory Chip Info
#define CHIP_ID 2144792 // hex 20 ba 18 -- The default chip ID for the ORM's Flash Memory



#endif
