/*
 * main.c
 *
 *  Created on: 2015/03/12
 *      Author: Yoshio
 */

#include "system/cmsis/LPC13Uxx.h"
#include "system/peripheral/uart.h"

int main(void)
{
	SystemCoreClockUpdate();

	const uint32_t UART_BAUDRATE = 115200;

	uart_init(UART_BAUDRATE);

	uart_puts_with_term("Hello, World!\n");

	while (1)
	{
		volatile uint32_t counter = 0;
		while (counter != 1000)
		{
			counter++;
		}
	}

	return 0;
}
