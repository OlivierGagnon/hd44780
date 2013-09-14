/*
*
* 4094 shift register functions
*
*/

#include <avr/io.h>
#include "hc4094.h"

void HC4094Init(void)
{
	//Set pins as output
	HC4094_DDR|=((1<<HC4094_CLOCK_PIN)|(1<<HC4094_LATCH_PIN)|(1<<HC4094_DATA_PIN));
}

//Sends a clock pulse
void HC4094Pulse(void)
{
	HC4094_PORT|=(1<<HC4094_CLOCK_PIN);	//HIGH
	HC4094_PORT&=(~(1<<HC4094_CLOCK_PIN));	//LOW
}

//Sends a pulse on latch
void HC4094Latch(void)
{
	HC4094_PORT|=(1<<HC4094_LATCH_PIN);//HIGH
	HC4094_PORT&=(~(1<<HC4094_LATCH_PIN));//LOW
}

void HC4094Write(int data)
{
	//bit bang to shift register
	uint8_t i;
	for(i=0;i<8;i++)
	{

		if(data & 0b00000001)
		{
			HC4094DataHigh();
		}
		else
		{
			HC4094DataLow();
		}
		HC4094Pulse();
		data = data>>1;
	}
	HC4094Latch();
}
