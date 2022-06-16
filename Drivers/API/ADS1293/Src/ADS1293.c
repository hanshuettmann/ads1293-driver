/**
 ******************************************************************************
 * @file    Drivers/API/Src/API_ADS1293.c
 * @author  Patricio Hans Hüttmann
 * @brief   This file provides firmware functions to manage ADS1293 device
 */
/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "ADS1293.h"
#include "NUCLEO_F429ZI_port.h"

/**
 * @brief  Initialize ADS1293 device
 * @param  dummy set this value to 0
 * @retval ADS1293_StatusTypeDef Init process status
 */
ADS1293_StatusTypeDef ads1293Init(uint8_t dummy) {
	/* Init SPI peripheral */
	if (spiInit(0) != NUCLEO_SPI_OK) {
		return ADS1293_ERROR;
	}

	/* Set device CS to HIGH */
	setNSS(GPIO_PIN_SET);

	return ADS1293_OK;
}

/**
 * @brief  Read ADS1293 ID register
 * @param  pidData pointer to the uint8_t buffer
 * @retval ADS1293_StatusTypeDef process status
 */
ADS1293_StatusTypeDef ads1293ReadID(uint8_t *pidData) {

	uint8_t ptxData = REVID | RREG;

	/* Validate *pidData */
	if (pidData == NULL) {
		return ADS1293_ERROR;
	}

	/* Read register and get sensor ID into pidData */
	if (ads1293ReadRegister(&ptxData, pidData, REG_ID_SIZE) != ADS1293_OK) {
		return ADS1293_ERROR;
	}

	return ADS1293_OK;

}

/**
 * @brief  Read register from *ptxData address
 * @param  ptxData pointer to the uint8_t buffer to be sent with the register address
 * @param  prxData pointer to the uint8_t buffer to store the register value
 * @param  size size amount of data to be sent
 * @retval ADS1293_StatusTypeDef process status
 */
ADS1293_StatusTypeDef ads1293ReadRegister(uint8_t *ptxData, uint8_t *prxData,
		uint16_t size) {
	/* Validate *ptxData, *prxData and size parameters */
	if (ptxData == NULL || prxData == NULL || size <= 0) {
		return ADS1293_ERROR;
	}

	/* ADS1293 sensor uses 7bit register addresses. MSB in ptxData indicates if the register is being
	 * read or write. Set MSB to 1 will read the register value */
	uint8_t readAddress = *ptxData | RREG;

	/* Set ADS1293 CS to LOW to start communication */
	setNSS(GPIO_PIN_RESET);

	/* Send register address with the read command over SPI protocol */
	if (spiSendData(&readAddress, REG_ID_SIZE) != NUCLEO_SPI_OK) {
		return ADS1293_ERROR;
	}

	/* Read register and load value into *prxData */
	if (spiReceiveData(prxData, REG_ID_SIZE) != NUCLEO_SPI_OK) {
		return ADS1293_ERROR;
	}

	/* Set ADS1293 CS to HIGH to finish communication */
	setNSS(GPIO_PIN_SET);

	return ADS1293_OK;
}

/**
 * @brief  Read register from *ptxData address
 * @param  ptxData pointer to the uint8_t buffer to be sent with the register address
 * @param  prxData pointer to the uint8_t buffer to store the register value
 * @param  size size amount of data to be sent
 * @retval ADS1293_StatusTypeDef process status
 */
ADS1293_StatusTypeDef ads1293WriteRegister(uint8_t wrAddress, uint8_t data,
		uint16_t size) {
	uint8_t dataToSend = data;

	/* ADS1293 sensor uses 7bit register addresses. MSB in ptxData indicates if the register is being
	 * read or write. Set MSB to 1 will read the register value */
	uint8_t writeAddress = wrAddress & WREG;

	/* Set ADS1293 CS to LOW to start communication */
	setNSS(GPIO_PIN_RESET);

	/* Send register address with the read command over SPI protocol */
	if (spiSendData(&writeAddress, size) != NUCLEO_SPI_OK) {
		return ADS1293_ERROR;
	}

	/* Send register address with the read command over SPI protocol */
	if (spiSendData(&dataToSend, size) != NUCLEO_SPI_OK) {
		return ADS1293_ERROR;
	}

	/* Set ADS1293 CS to HIGH to finish communication */
	setNSS(GPIO_PIN_SET);

	return ADS1293_OK;
}

/**
 * @brief  Set ADS1293 to start a 3 lead ecg
 * @param  none
 * @retval none
 */
void ads1293Set3LeadECG(void) {
	/* Connect channel 1’s INP to IN2 and INN to IN1 */
	ads1293WriteRegister(FLEX_CH1_CN, 0x11, 1);
	/* Connect channel 2’s INP to IN3 and INN to IN1 */
	ads1293WriteRegister(FLEX_CH2_CN, 0x19, 1);
	/* Enable the common-mode detector on input pins IN1, IN2 and IN3 */
	ads1293WriteRegister(CMDET_EN, 0x07, 1);
	/* Connect the output of the RLD amplifier internally to pin IN4 */
	ads1293WriteRegister(RLD_CN, 0x04, 1);
	/* Use external crystal and feed the internal oscillator's output to the digital */
	ads1293WriteRegister(OSC_CN, 0x04, 1);
	/* Shuts down unused channel 3’s signal path */
	ads1293WriteRegister(AFE_SHDN_CN, 0x24, 1);
	/* Configures the R2 decimation rate as 5 for all channels */
	ads1293WriteRegister(R2_RATE, 0x02, 1);
	/* Configures the R3 decimation rate as 6 for channel 1 */
	ads1293WriteRegister(R3_RATE_CH1, 0x02, 1);
	/* Configures the R3 decimation rate as 6 for channel 2 */
	ads1293WriteRegister(R3_RATE_CH2, 0x02, 1);
	/* Configures the DRDYB source to channel 1 ECG (or fastest channel) */
	ads1293WriteRegister(DRDYB_SRC, 0x08, 1);
	/* Enables channel 1 ECG and channel 2 ECG for loop read-back mode */
	ads1293WriteRegister(CH_CNFG, 0x30, 1);
	/* Starts data conversion */
	ads1293WriteRegister(CONFIG, 0x01, 1);

}

/**
 * @brief  Read loop read-back register
 * @param  sourceBytes source bytes number
 * @retval none
 */
void ads1293ReadDataLoop(uint8_t *rawData, uint32_t sourceBytes) {
	/* Read DATA_LOOP register */
	uint8_t readAddress = DATA_LOOP | RREG;

	/* Set ADS1293 CS to LOW to start communication */
	setNSS(GPIO_PIN_RESET);

	/* Send register address with the read command over SPI protocol */
	spiSendData(&readAddress, sizeof(uint8_t));

	for (uint32_t i = 0; i < (1 + sourceBytes); ++i) {
		spiReceiveData(&rawData[i], sizeof(uint8_t));
	}

	/* Set ADS1293 CS to HIGH to finish communication */
	setNSS(GPIO_PIN_RESET);

}
