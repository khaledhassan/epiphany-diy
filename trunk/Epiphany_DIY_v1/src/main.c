/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * AVR Software Framework (ASF).
 */





#include <asf.h>
#include <avr/io.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "motor.h"
#include "lcd.h"
#include "uart.h"
#include "RTC.h"
#include "picServo.h"
//#include "ATtinyServo.h"
#include "ADC.h"
#include "sonar.h"

#define DbLedOn()		(PORTR.OUTCLR = 0x02)		//Turns the debug led on.  The led is connected with inverted logic
#define DbLedOff()		(PORTR.OUTSET = 0x02)		//Turns the debug led off.  The led is connected with inverted logic
#define DbLedToggle()	(PORTR.OUTTGL = 0x02)		//Toggles the debug led off.  The led is connected with inverted logic

	

int main (void)
{	
	board_init();	/*This function originates in the file init.c, and is used to initialize the Epiphany DIY
					  motorInit() is declared within because by default you the user should define what your
					  motor setup is to prevent hurting the Epiphany.  You can do this by 
					*/	  
	RTC_DelayInit();//initializes the Real time clock this seems to actually take an appreciable amount of time
	DbLedOn();	//I like to do this by default to show the board is no longer suspended in the bootloader.
	servoControlInit();//initializes the servo module ***including enabling global interrupts*** required for the servo control module 
	uartInit(&USARTC0,57600);//as can be seen in the schematic.  This uart is connected to the USB port.  This function initializes this uart	
	uartInit(&USARTE1,9600);//as can be seen in the schematic.  This uart is connected to the USB port.  This function initializes this uart	
	ADCsInits();//this function initializes the ADCs inside the Xmega		 
	LCDInit();
	//you should add any further initializations here
	sei();
	fprintf_P(&lcd_str,PSTR("Out of the Box\nEpiphany DIY"));
	fprintf_P(&USB_str,PSTR("Out of the Box:\rElectronics and Robotics\rPresents the\rEpiphany DIY\rSoftware Version %s\r%s"),sVersion,date);		
	uint8_t i;
	while (1)
	{
		
		for(i=0;i<8;i++){
		ADCA_request(0,ExternalChannel0 + i);
		while(!ADCA_CH0_ConvComplete);
		fprintf(&USB_str,"ADC%d = %d\r\n",i,ADCA_getVal(0));
		}		
		fprintf(&USB_str,"\r\r\r");
		
		_delay_ms(200);
	}
}