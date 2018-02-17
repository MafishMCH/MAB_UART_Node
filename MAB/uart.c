/*
 * uart.c
 *
 *  Created on: Feb 16, 2018
 *      Author: Jakub Matysczak
 */
#include "uart.h"
#include "stm32f1xx.h"
#include "utils.h"

void uart_init()
{
	for(uint8_t i = 0; i < 16; i++)
	{
		rx_rpi[i] = 0;
		tx_rpi[i] = 0;
		rx_rs485[i] = 0;
		tx_rs485[i] = 0;
	}
	for(uint8_t i = 0; i < 8; i++)
	{
		drivers[i].adress = 0x10+i;
		drivers[i].available = FALSE;
		for(uint8_t j = 0; j < RS485_DATA_SIZE; j++)
		{
			drivers[i].rxData[j] = 0;
			drivers[i].txData[j] = 0;
		}
		drivers[i].rxData[0] = RS485_SOF;
		drivers[i].rxData[1] = drivers[i].adress;
		drivers[i].rxData[RS485_DATA_SIZE - 1] = RS485_EOF;
	}
	ms_elapsed = 0;
	isBusy_rs485 = RS485_FREE;
	messages_to_send = 0;
}
uint8_t uart_eorx_rpi()
{
	if(rx_rpi[0] == RS485_SOF && rx_rpi[RS485_DATA_SIZE-1] == RS485_EOF)
	{
		//wiadomosc poprawna
		uint8_t target = rx_rpi[1] - 0x10;
		for(uint8_t i = 2; i < RS485_DATA_SIZE-1; i++)		//-1 przez EOF
		{
			drivers[target].rxData[i] = rx_rpi[i];
		}
		if(drivers[target].rxData[RS485_DATA_SIZE-1] == RS485_EOF)
			return SUCCESS;
		else
			return FAILURE;
	}
	else
	{
		//wiadomosc niepoprawna
		return FAILURE;
	}
}
uint8_t uart_eorx_rs485(UART_HandleTypeDef *uart_rpi)
{

	//sprawdzanie poprawnosci wiadomosci
	if(rx_rs485[0] == RS485_SOF && rx_rs485[RS485_DATA_SIZE-1] == RS485_EOF)
	{
		//wiadomosc poprawna
		for(uint8_t i = 0; i < RS485_DATA_SIZE; i++)
			tx_rpi[i] = rx_rs485[i];
		HAL_UART_Transmit_IT(uart_rpi, tx_rpi, RS485_DATA_SIZE);
		return SUCCESS;
	}
	else
	{
		//wiadomosc niepoprawna
		HAL_UART_AbortReceive_IT(uart_rpi);
		return FAILURE;
	}
}
void rs485_send_all(UART_HandleTypeDef *uart_rs)			//javol
{
	ms_elapsed = 0;
	for(uint8_t i = 0; i < 8;i++)
	{
		isBusy_rs485 = RS485_BUSY;			//magistrala zajeta
		HAL_UART_Transmit_IT(uart_rs, drivers[i].txData, RS485_DATA_SIZE);
		while(isBusy_rs485 == RS485_BUSY);	//dopoki nie wysle czekaj
		isBusy_rs485 = RS485_BUSY;			//magistrala zajeta
		ms_elapsed = 0;						//timer na zero
		HAL_UART_Receive_IT(uart_rs, drivers[i].rxData, RS485_DATA_SIZE);
		while(isBusy_rs485 == RS485_BUSY || ms_elapsed < RS485_TIMEOUT_MS);	//czekaj na wolna magistrale albo timeout
		if(ms_elapsed >= RS485_TIMEOUT_MS)		//jesli timeout to przypisz ze sterownik padl
			drivers[i].available = FALSE;
		else
			drivers[i].available = TRUE;
	}
}
void rpi_send_all(UART_HandleTypeDef *uart_rpi)
{
	uint8_t temp_arr[RS485_DATA_SIZE * 8];
	uint8_t iterator = 0;
	for(uint8_t i = 0; i < 8; i++)
	{
		temp_arr[iterator] =drivers[i].rxData[iterator & RS485_DATA_SIZE];
	}
	HAL_UART_Transmit_IT(uart_rpi, temp_arr, RS485_DATA_SIZE * 8);
}
