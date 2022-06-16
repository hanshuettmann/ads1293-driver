/**
 ******************************************************************************
 * @file    Drivers/API/Inc/API_Debounce.c
 * @author  Patricio Hans Hüttmann
 * @brief   This file provides firmware functions to Debounce FSM
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
#include <stm32f4xx_hal.h>
#include <stm32f4xx_nucleo_144.h>
#include <API_Debounce.h>
#include <API_Delay.h>

/* Private define ------------------------------------------------------------*/
#define DEBOUNCE_DELAY 40

/* Private Structures declaration --------------------------------------------*/
typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_RISING, BUTTON_DOWN
} debounceState_t;

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Private global variables */
static debounceState_t currentState;
static bool_t buttonPressed;

/**
 * @brief  Initialize Debounce Finite State Machine FSM
 * @param  none
 * @retval None
 */
void debounceFSM_init(void) {
	/* Initialize User Button */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	currentState = BUTTON_UP;
	buttonPressed = false;
}

/**
 * @brief  Read entries and update FSM state and pressed status
 * @param  none
 * @retval None
 */
void debounceFSM_update(void) {
	/* Initialize delay_t handler */
	static delay_t debounceDelay;

	switch (currentState) {
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)) {
			currentState = BUTTON_FALLING;
			if (delayInit(&debounceDelay, DEBOUNCE_DELAY) != DELAY_OK)
				Error_Handler();
		}
		break;

	case BUTTON_FALLING:
		if (delayRead(&debounceDelay)) {
			if (BSP_PB_GetState(BUTTON_USER)) {
				currentState = BUTTON_DOWN;
				buttonPressed = true;
			} else {
				currentState = BUTTON_UP;
			}
		}
		break;

	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)) {
			currentState = BUTTON_RISING;
			if (delayInit(&debounceDelay, DEBOUNCE_DELAY) != DELAY_OK)
				Error_Handler();
		}
		break;

	case BUTTON_RISING:
		if (delayRead(&debounceDelay)) {
			if (!BSP_PB_GetState(BUTTON_USER)) {
				currentState = BUTTON_UP;
				buttonPressed = false;
			} else {
				currentState = BUTTON_DOWN;
			}
		}
		break;

	default:
		debounceFSM_init();
		break;
	}
}

/**
 * @brief  Read if the user button is pressed
 * @param  none
 * @retval Button status
 */
bool_t readKey(void) {
	bool_t pressed = false;

	if (buttonPressed) {
		pressed = true;
		buttonPressed = false;
	}

	return pressed;
}

/* Private function -----------------------------------------------*/
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* Toggle LED2 */
	while (1) {
		BSP_LED_Toggle(LED2);
		HAL_Delay(500);
	}
}

/*****************************END OF FILE**************************************/
