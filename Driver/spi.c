/*
		spi.c file is a hardware Driver.
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

#include "spi.h"

void initSpi(void)
{
		SPI_InitTypeDef SPI_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure , gpio_struct;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 , ENABLE);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOA , &GPIO_InitStructure);

				// Init SD_CARD_CHIP_SELECT
		gpio_struct.GPIO_Pin = GPIO_Pin_4;
		gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
		gpio_struct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA , &gpio_struct);

		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // | SPI_NSSInternalSoft_Set;
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI1 , &SPI_InitStructure);
		SPI_Cmd(SPI1 , ENABLE);

}

void SpiSendData(uint8_t data)
{
		SPI_I2S_SendData(SPI1 , data);
		while(SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_TXE) == RESET);
}

uint8_t SpiTransceiveByte(uint8_t data)
{
	SPI1->DR = data;
	while ((SPI1->SR & SPI_I2S_FLAG_RXNE) == 0);
	return SPI1->DR;
}

uint8_t SpiReceive()
{
		while(SPI_I2S_GetFlagStatus(SPI1 , SPI_I2S_FLAG_RXNE) == RESET);
		return ((uint8_t) (SPI_I2S_ReceiveData(SPI1)));
}

void SpiCsLow(void)
{
		GPIOA->BRR = GPIO_Pin_4;
}

void SpiCsHigh(void)
{
		GPIOA->BSRR = GPIO_Pin_4;
}
