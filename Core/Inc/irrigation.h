#ifndef IRRIGATION_H
#define IRRIGATION_H

#include <stdint.h>

#define SENSOR1_MIN 2700
#define SENSOR1_MAX 1450
#define SENSOR1_TARGET 50

#define PUMP1_TIME 3000

#define SENSOR2_MIN 2700
#define SENSOR2_MAX 1500
#define SENSOR2_TARGET 50

#define PUMP2_TIME 3000

#define SENSOR3_MIN 2700
#define SENSOR3_MAX 1500
#define SENSOR3_TARGET 50

#define PUMP3_TIME 3000

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t  out_min, int32_t out_max);
int32_t constrain(int32_t value, int32_t min, int32_t max);
void get_moisture(uint32_t *moisture1, uint32_t *moisture2, uint32_t *moisture3);
void update_display_moisture(uint32_t moisture1, uint32_t moisture2, uint32_t moisture3);
void enable_pump(uint8_t pump_number);
void irrigate();

#endif