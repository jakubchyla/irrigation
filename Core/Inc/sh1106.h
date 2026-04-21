#ifndef SS1306_H
#define SS1306_H

#include "stm32l4xx_hal.h"

#define SH1106_WIDTH 128
#define SH1106_HEIGHT 64

enum SH1106_STATE {
    ON = 0,
    OFF = 1
};

enum SH1106_COLOR {
    BLACK = 0,
    WHITE = 1
};

struct SH1106_DATA_t {
    uint16_t x;
    uint16_t y;
    I2C_HandleTypeDef *i2c_handle;
};

struct SH1106_FONT_T {
    uint8_t width;
    uint8_t height;
    uint16_t const *data;
};

extern const struct SH1106_FONT_T SH1106_FONT;

void sh1106_draw_pixel(uint16_t x, uint16_t y, enum SH1106_COLOR color);
void sh1106_set_cursor(uint8_t x, uint8_t y);
uint8_t sh1106_write_string(char *str, struct SH1106_FONT_T font, enum SH1106_COLOR color);
void sh1106_update_screen();
void sh1106_set_state(enum SH1106_STATE state);
void sh1106_fill_screen(enum SH1106_COLOR color);
void sh1106_init(I2C_HandleTypeDef *i2c_handle);

#endif