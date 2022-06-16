/**
 ******************************************************************************
 * @file    Drivers/API/Inc/API_Delay.h
 * @author  Patricio Hans Hüttmann
 * @brief   Header for API_Delay.c module
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>

/* Structures declaration ----------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

typedef enum {
	DELAY_OK = 0x00U,
	DELAY_ERROR = 0x01U
} delay_statusTypeDef;

/* Public function prototypes -----------------------------------------------*/
delay_statusTypeDef delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
delay_statusTypeDef delayWrite(delay_t *delay, tick_t duration);

/*****************************END OF FILE**************************************/
