#include "irrigation.h"
#include "sh1106.h"
#include "main.h"
#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_adc.h"
#include "stm32l4xx_hal_def.h"
#include "stm32l4xx_hal_gpio.h"

extern ADC_HandleTypeDef hadc1;

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t  out_min, int32_t out_max)
{
    return ((x - in_min) * (out_max - out_min)) / ((in_max - in_min) + out_min);
}

inline int32_t constrain(int32_t value, int32_t min, int32_t max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

void get_moisture(uint32_t *moisture1, uint32_t *moisture2, uint32_t *moisture3)
{
    int32_t moisture_tmp;
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    moisture_tmp = HAL_ADC_GetValue(&hadc1);
    moisture_tmp = constrain(map(HAL_ADC_GetValue(&hadc1), SENSOR1_MIN, SENSOR1_MAX, 0, 100), 0, 100);
    *moisture1 = moisture_tmp;
    // HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    // moisture_tmp = constrain(0, 100, map(HAL_ADC_GetValue(&hadc1), 2700, 1500, 0, 100));
    // *moisture2 = moisture_tmp;
    // HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    // moisture_tmp = constrain(0, 100, map(HAL_ADC_GetValue(&hadc1), 2700, 1500, 0, 100));
    // *moisture1 = moisture_tmp;
}

void enable_pump(uint8_t pump_number)
{
    switch(pump_number)
    {
        case 1:
            HAL_GPIO_WritePin(RELAY1_GPIO_Port, RELAY1_Pin, 0);
            HAL_Delay(PUMP1_TIME);
            HAL_GPIO_WritePin(RELAY1_GPIO_Port, RELAY1_Pin, 1);
        break;
        // case 2:
        //     HAL_GPIO_WritePin(RELAY2_GPIO_Port, RELAY2_Pin, 0);
        //     HAL_Delay(PUMP2_TIME);
        //     HAL_GPIO_WritePin(RELAY2_GPIO_Port, RELAY2_Pin, 1);
        // break;
        // case 3:
        //     HAL_GPIO_WritePin(RELAY3_GPIO_Port, RELAY3_Pin, 0);
        //     HAL_Delay(PUMP3_TIME);
        //     HAL_GPIO_WritePin(RELAY3_GPIO_Port, RELAY3_Pin, 1);
        // break;
    }
}


void update_display_moisture(uint32_t moisture1, uint32_t moisture2, uint32_t moisture3)
{
    char moisture_str[10];
    sh1106_fill_screen(BLACK);
    sh1106_set_cursor(29, 10);
    sh1106_write_string("Wilgotnosc", SH1106_FONT, WHITE);
    sh1106_set_cursor(50, 25);
    sprintf(moisture_str, "%lu%%", moisture1);
    sh1106_write_string(moisture_str, SH1106_FONT, WHITE);
    sh1106_update_screen();
}


void irrigate()
{
    uint32_t moisture1, moisture2, moisture3;
    get_moisture(&moisture1, &moisture2, &moisture3);
    update_display_moisture(moisture1, moisture2, moisture3);

    if (moisture1 < SENSOR1_TARGET)
    {
        enable_pump(1);
    }
    // if (moisture2 < SENSOR2_TARGET)
    // {
    //     enable_pump(2);
    // }
    // if (moisture3 < SENSOR3_TARGET)
    // {
    //     enable_pump(3);
    // }
}
