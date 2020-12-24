#define F_CPU	8000000UL
#define BAUD	9600
#define BRC	((F_CPU/16/BAUD)-1)
#include <util/setbaud.h>
#include <avr/io.h>
#include "diskio.h"
#include "ff.h"
#include <stdio.h>
#include "uart.h"
#include <util/delay.h>

int main(void)
{

	FATFS fs;
	FIL fil;
	char line[100];
	FRESULT fr;
	DSTATUS ds;

	uart_init(BRC);
	while(1){
		USART_TX("t");
		_delay_ms(500);
	}

	//stdout = &uart_output;
	//stdin = &uart_input;

	_delay_ms(2000);
	while(1)
	{
		ds = disk_initialize(0);
		fr = f_mount(&fs, "", 0);
		fr = f_open(&fil, "test.txt", FA_READ);
		while(f_gets(line, sizeof line, &fil))
		{
			printf(line);
		}
		_delay_ms(1000);
	}
	return 0;
}

