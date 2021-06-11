/*
 * communication.h
 *
 *  Created on: Nov 29, 2020
 *      Author: ZhangGuixin
 */

#ifndef DREAM_COMMUNICATION_H_
#define DREAM_COMMUNICATION_H_

#include "macro.h"

void myuart_DMA(UART_HandleTypeDef *huart);
void myuartDMA_callback(UART_HandleTypeDef *huart);
void JY60_Callback(UART_HandleTypeDef *huart);

#endif /* DREAM_COMMUNICATION_H_ */
