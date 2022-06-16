/**
 ******************************************************************************
 * @file    Drivers/API/Inc/API_Debounce.h
 * @author  Patricio Hans Hüttmann
 * @brief   Header for API_Debounce.c module
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

/* Structures declaration ----------------------------------------------------*/
typedef bool bool_t;

/* Public function prototypes ------------------------------------------------*/
void debounceFSM_init(void);
void debounceFSM_update(void);

bool_t readKey(void);

/*****************************END OF FILE**************************************/
