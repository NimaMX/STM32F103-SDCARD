/*
		gpio.c file is a hardware Driver.
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

#include "gpio.h"

void initGpio(void)
{
		GPIO_InitTypeDef gpio_struct;

		// Gpio Clock Configuration
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

		// Init RED_GREEN
		gpio_struct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
		gpio_struct.GPIO_Speed = GPIO_Speed_2MHz;
		gpio_struct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB , &gpio_struct);

		// Init SD_CARD_HARDWARE_TRIGGER
		gpio_struct.GPIO_Pin = GPIO_Pin_1;
		gpio_struct.GPIO_Speed = GPIO_Speed_2MHz;
		gpio_struct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOA , &gpio_struct);

}

void gpio_PortClockStart(GPIO_TypeDef *GPIOx)
{
  if (GPIOx == GPIOA)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  else if (GPIOx == GPIOB)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  else if (GPIOx == GPIOC)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  else if (GPIOx == GPIOD)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  else if (GPIOx == GPIOE)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  else if (GPIOx == GPIOF)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  else if (GPIOx == GPIOG)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
}

void gpio_setStateHigh(GPIO_TypeDef *pinPort , uint8_t pinNumber)
{
		GPIO_SetBits(pinPort , pinNumber);
}

void gpio_setStateLow(GPIO_TypeDef *pinPort , uint8_t pinNumber)
{
		GPIO_ResetBits(GPIOB , pinNumber);
}

void gpio_HammerState(GPIO_TypeDef *pinPort , uint8_t pinNumber , uint32_t delay_time)
{
		gpio_setStateHigh(pinPort , pinNumber);
		delay(delay_time);
		gpio_setStateLow(pinPort , pinNumber);
}

uint16_t gpio_ReadPinState(GPIO_TypeDef *pinport , uint8_t pinNumber)
{
		return (GPIO_ReadInputData(pinport) & pinNumber);
}
