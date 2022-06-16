/**
 ******************************************************************************
 * @file    Drivers/API/Inc/API_Delay.c
 * @author  Patricio Hans Hüttmann
 * @brief   This file provides firmware functions to manage non blocker delays
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
#include <API_Delay.h>

/**
 * @brief  Initialize delay handler
 * @param  delay: pointer to a delay_t structure that contains
 *         the corresponding values to use the delay.
 * @param  duration: Timeout value
 * @retval Delay def status
 */
delay_statusTypeDef delayInit(delay_t *delay, tick_t duration) {
	//Timeout and pointer validation
	if (delay == 0 || duration < 0) {
		return DELAY_ERROR;
	}

	delay->startTime = HAL_GetTick();
	delay->duration = duration;
	delay->running = false;
	return DELAY_OK;
}

/**
 * @brief  Reads if delay is running or not
 * @param  delay: pointer to a delay_t structure that contains
 *         the corresponding values to use the delay.
 * @retval Boolean that indicates the state of the delay. True for delay running and false indicating
 * 		   duration time has elapsed
 */
bool_t delayRead(delay_t *delay) {
	//Pointer validation
	if (delay == 0) {
		while(1);
	}

	if (!delay->running) {
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	if (HAL_GetTick() - delay->startTime > delay->duration) {
		delay->running = false;
		return true;
	} else {
		return false;
	}
}

/**
 * @brief  Sets delay duration
 * @param  delay: pointer to a delay_t structure that contains
 *         the corresponding values to use the delay.
 * @param  duration: Timeout value
 */
delay_statusTypeDef delayWrite(delay_t *delay, tick_t duration) {
	//Timeout and pointer validation
	if (delay == 0 || duration < 0) {
		return DELAY_ERROR;
	}

	delay->duration = duration;
	return DELAY_OK;
}

/*****************************END OF FILE**************************************/
