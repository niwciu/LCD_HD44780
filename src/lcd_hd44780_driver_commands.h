// clang-format off

// LCD driver commands
#define LCDC_CLS            0x01
#define LCDC_HOME           0x02
/********************************/
#define LCDC_ENTRY_MODE     0x04
    #define LCDC_ENTRYR     0x02
    #define LCDC_ENTRYL     0x00
    #define LCDC_MOVE       0x01
/********************************/
#define LCDC_ONOFF          0x08
    #define LCDC_DISPLAYON  0x04
    #define LCDC_CURSORON   0x02
    #define LCDC_CURSOROFF  0x00
    #define LCDC_BLINKON    0x01
/********************************/
#define LCDC_SHIFT          0x10
    #define LCDC_SHIFTDISP  0x08
    #define LCDC_SHIFTR     0x04
    #define LCDC_SHIFTL     0x00
/********************************/
#define LCDC_FUNC           0x20
    #define LCDC_FUNC8B     0x10
    #define LCDC_FUNC4B     0x00
    #define LCDC_FUNC2L     0x08
    #define LCDC_FUNC1L     0x00
    #define LCDC_FUNC5x10   0x04
    #define LCDC_FUNC5x7    0x00
/********************************/
#define LCDC_SET_CGRAM      0x40
#define LCDC_SET_DDRAM      0x80

// clang-format on