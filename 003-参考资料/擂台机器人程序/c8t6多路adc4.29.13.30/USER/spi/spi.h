#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include <stdio.h>


void SPI1_Init(void);
u8 SPI2_ReadWriteByte(u8 TxData);


#endif /* __SPI_FLASH_H */

