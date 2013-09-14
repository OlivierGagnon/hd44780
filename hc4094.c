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
	//Pulse the  Clock
	HC4094_PORT|=(1<<HC4094_CLOCK_PIN);	//HIGH
	HC4094_PORT&=(~(1<<HC4094_CLOCK_PIN));	//LOW
}

//Sends a pulse on latch
void HC4094Latch(void)
{
	//Pulse the Store Clock
	HC4094_PORT|=(1<<HC4094_LATCH_PIN);//HIGH
	HC4094_PORT&=(~(1<<HC4094_LATCH_PIN));//LOW
}

void HC4094Write(int data)
{
	//Send each 8 bits serially
	uint8_t i;
	for(i=0;i<8;i++)
	{
		//Output the data on data line according to the
		//Value of LSB
		if(data & 0b00000001)
		{
			//LSB is 1 so output high
			HC4094DataHigh();
		}
		else
		{
			//LSB is 0 so output low
			HC4094DataLow();
		}
		HC4094Pulse();  //Pulse the Clock line
		data=data>>1;  //Now bring next bit at LSB position
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC4094Latch();
}
