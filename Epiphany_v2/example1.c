/*
 * example1.c
 *
 * Created: 8/29/2013 1:05:36 AM
 *  Author: Tim
 */ 

#include "Epiphany.h"

void setup()
{
	//initialize the system clock to 32MHz
	//this is actually unnecessary since the RTC is system clock independent
	clockInit();
	
	//initialize the real time clock used for delays
	RTC_DelayInit();
	
	//initialize the uart used for the usb serial port
	usbInit(115200);
	
	//initialize the led pin for output
	dbledInit();
}

void loop()
{
	if(delayOver)
	{
		dbledTgl();
		RTC_Delay_ms(25);
	}
	
	/*
	code can run here while the RTC delay is counted up.
	using delays such as those in util/delay.h just waste
	clock cycles, that could be used for processing.  The
	RTC delay method used here is a great way to multi-task
	code in the MCU
	*/
	
}