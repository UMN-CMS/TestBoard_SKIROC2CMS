#ifndef BOARD_DATA
#define BOARD_DATA



// Board Type (SYNC or RDOUT) TODO
// #define BOARD_TYPE


// PAGE and pin numbers used to power cycle the ORM's and CTL
#define FPGA_POWER_PAGE 0xF
#define ORM0_POWER_PIN (0x1 - 1) // 0x1 is the physical pin, 0x0 is the pin as referenced by GPIOB
#define ORM1_POWER_PIN (0x2 - 1)
#define ORM2_POWER_PIN (0x3 - 1)
#define ORM3_POWER_PIN (0x4 - 1)
#define CTL_POWER_PIN (0x5 - 1)


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
