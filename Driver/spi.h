/*
		spi.h file is a hardware Driver.
    Copyright (C) 2018 Nima Mohammadi
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f10x.h"
#include "stm32f10x_spi.h"

void initSpi(void);

void SpiSendData(uint8_t data);

uint8_t SpiTransceiveByte(uint8_t data);

uint8_t SpiReceive(void);

void SpiCsLow(void);
void SpiCsHigh(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H */
