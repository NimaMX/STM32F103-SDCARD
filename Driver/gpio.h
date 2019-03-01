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


#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "clock.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDCARD_DETECT_Pin 				GPIO_Pin_1
#define SDCARD_DETECT_GPIO_Port 	GPIOA

#define SD_CS_Pin 								GPIO_Pin_4
#define SD_CS_GPIO_Port 					GPIOA

#define LED_GREEN_Pin 						GPIO_Pin_0
#define LED_RED_Pin 							GPIO_Pin_1

#define LED_GREEN_GPIO_Port 			GPIOB
#define LED_RED_GPIO_Port 				GPIOB

void initGpio(void);

void gpio_PortClockStart(GPIO_TypeDef *GPIOx);

void gpio_setStateHigh(GPIO_TypeDef *pinPort , uint8_t pinNumber);

void gpio_setStateLow(GPIO_TypeDef *pinPort , uint8_t pinNumber);

void gpio_HammerState(GPIO_TypeDef *pinPort , uint8_t pinNumber , uint32_t delay_time);

uint16_t gpio_ReadPinState(GPIO_TypeDef *pinport , uint8_t pinNumber);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
