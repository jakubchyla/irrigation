#include <stdint.h>
#include "uart_functions.h"
#include "main.h"
#include "stm32l4xx_hal_def.h"
#include "stm32l4xx_hal_uart.h"

extern UART_HandleTypeDef *hlpuart1;

void get_line(uint8_t *buffer, uint32_t buffer_size)
{
    uint8_t uart_char;
    uint32_t offset = 0;
    while (uart_char != '\n' && offset < buffer_size - 1)
    {
        buffer[offset] = HAL_UART_Receive(hlpuart1, &(buffer[offset]), 1, HAL_MAX_DELAY);
        offset++;
    }
    buffer[offset] = '\0';
}