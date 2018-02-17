/*
 * uart.h
 *
 *  Created on: Feb 11, 2018
 *      Author: Jakub Matyszczak
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f1xx_hal.h"
#include "main.h"

#define TRANSCEIVER_ADR 	0x20
#define RS485_DATA_SIZE 	10
#define RS485_TIMEOUT_MS	10
#define RS485_SOF			0xCC
#define RS485_EOF			0xDD
#define RS485_BUSY			1
#define RS485_FREE  		0

uint8_t rx_rpi[16];
uint8_t tx_rpi[16];
uint8_t rx_rs485[16];
uint8_t tx_rs485[16];
uint8_t isBusy_rs485;
uint8_t messages_to_send;
uint32_t ms_elapsed;

typedef struct driver
{
	uint8_t adress;
	uint8_t txData[RS485_DATA_SIZE];
	uint8_t rxData[RS485_DATA_SIZE];
	uint8_t available;
}drv;
drv drivers[8];

void uart_init();
uint8_t uart_eorx_rpi();
void uart_eotx_rpi();
uint8_t uart_eorx_rs485(UART_HandleTypeDef *uart);
void rs485_send_all(UART_HandleTypeDef *uart);
void rpi_send_all(UART_HandleTypeDef *uart);

#endif /* UART_H_ */
