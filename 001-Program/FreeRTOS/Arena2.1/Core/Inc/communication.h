//
// Created by dream on 2021/6/11.
//

#ifndef INC_002_ARENA_COMMUNICATION_H
#define INC_002_ARENA_COMMUNICATION_H

#include "macro.h"


void myuartDMA_callback(UART_HandleTypeDef *huart);
void JY60_Callback(UART_HandleTypeDef *huart);
void myuart_DMA(UART_HandleTypeDef *huart);

#endif //INC_002_ARENA_COMMUNICATION_H
