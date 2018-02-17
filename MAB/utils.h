/*
 * utils.h
 *
 *  Created on: Feb 16, 2018
 *      Author: Jakub Matyszcak
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "stm32f1xx_hal.h"

#define LED_ON HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_OFF HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)
#define LED_TOGGLE HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin)
#define TRUE 1
#define FALSE 0
#define SUCCESS	1
#define FAILURE 0

int32_t ilimit(int32_t val, int32_t min, int32_t max);
int32_t iabs(int32_t val);

#endif /* UTILS_H_ */
