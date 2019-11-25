#ifndef __uart_H
#define __uart_H

#include "stm32f4xx_hal.h"
#include "main.h"


extern UART_HandleTypeDef huart2;
extern void Error_Handler(void);
void uart_init(void);


#endif
