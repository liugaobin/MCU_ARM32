#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "gd32f4xx.h"

void uart_init(void);
void uart_send_byte(uint8_t byte);

#endif