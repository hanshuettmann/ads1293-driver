/**
 ******************************************************************************
 * @file    Drivers/API/Src/API_Uart.c
 * @author  Patricio Hans Hüttmann
 * @brief   This file provides firmware functions to manage UART peripheral
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
#include <API_Uart.h>
#include <stdio.h>
#include <string.h>

/* Settings messages */
static const char *UART_WELCOME_MSG = "<!-- Starting UART port -->\n\r";
static const char *UART_BAUDRATE_MSG = "Baudrate: 9600\n\r";
static const char *UART_WORDLENGTH_MSG = "Wordlength: 8 bits\n\r";
static const char *UART_STOPBITS_MSG = "Stop bits: 1 bit\n\r";
static const char *UART_PARITY_MSG = "Parity: Odd\n\r";
static const char *UART_FLOWCONTROL_MSG = "HW Flow Control: None\n\r";
static const char *UART_MODE_MSG = "Mode: TX_RX\n\r";
static const char *UART_OVERSAMPLING_MSG = "Oversampling: 16\n\n\r";

/* UART handler declaration */
static UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief  Initialize UART peripheral
 * @param  none
 * @retval bool Init process status
 */
bool_t uartInit(void) {

	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	UartHandle.Instance = USARTx;

	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	/* Init peripheral */
	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
		/* Initialization Error */
		return false;
	} else {
		uartSendString((uint8_t*) UART_WELCOME_MSG);
		uartSendString((uint8_t*) UART_BAUDRATE_MSG);
		uartSendString((uint8_t*) UART_WORDLENGTH_MSG);
		uartSendString((uint8_t*) UART_STOPBITS_MSG);
		uartSendString((uint8_t*) UART_PARITY_MSG);
		uartSendString((uint8_t*) UART_FLOWCONTROL_MSG);
		uartSendString((uint8_t*) UART_MODE_MSG);
		uartSendString((uint8_t*) UART_OVERSAMPLING_MSG);
		return true;
	}

}

/**
 * @brief  Send string to the console
 * @param  pstring pointer to the array to be sent to the console
 * @retval none
 */
void uartSendString(uint8_t *pstring) {
	/* Validates pstring parameter */
	if (pstring == NULL) {
		return;
	}

	/* Send pstring to the console */
	HAL_UART_Transmit(&UartHandle, (uint8_t*) pstring,
			strlen((const char*) pstring), HAL_MAX_DELAY);
}

/**
 * @brief Send a finite number of characters to the console
 * @param pstring pointer to the array to be sent to the console
 * @param size amount of characters to send
 * @retval none
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	/* Validates pstring and size parameters */
	if (pstring == NULL || size < 0) {
		return;
	}

	/* Send pstring to the console */
	HAL_UART_Transmit(&UartHandle, (uint8_t*) pstring, size, HAL_MAX_DELAY);
}

/**
 * @brief  Receive string from UART
 * @param  pstring Pointer to data buffer (u8 or u16 data elements).
 * @param  size  Amount of data elements (u8 or u16) to be received.
 * @retval none
 */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	/* Validates pstring and size parameters */
	if (pstring == NULL || size < 0) {
		return;
	}

	/* Receive pstring from the serial port */
	HAL_UART_Receive(&UartHandle, (uint8_t*) pstring, size, HAL_MAX_DELAY);
}

/*****************************END OF FILE**************************************/
