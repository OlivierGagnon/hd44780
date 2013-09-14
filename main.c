#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "hc4094.h"
#include "hd44780.h"

int main(void)
{
    HC4094Init();
    LCD_4bit_Init();
    LCD_Clear();

    LCD_WriteLongString("Testing wrapped line on LCD");
    _delay_ms(5000);
    LCD_Clear();

    LCD_WriteString("Count1:");
    LCD_Goto_Position(2,1);
    LCD_WriteString("Count2:");

    while(1)
    {
        int count1=0;
        int count2=1000;
        for (count1 = 0; count1 < 1000; count1++)
        {

            //put an arrow next to highest value
            if (count1 > count2)
            {
                LCD_Goto_Position(1, 16);
                LCD_4bit_WriteDDRAM(0b01111111); //arrow
            }
            else if (count1 == count2) //clear the arrow position when equal
            {
                LCD_Goto_Position(1, 16);
                LCD_WriteString(" ");
                LCD_Goto_Position(2, 16);
                LCD_WriteString(" ");
            }
            else if (count1 == 0) //clear the arrow position when 0
            {
                LCD_Goto_Position(1, 16);
                LCD_WriteString(" ");
                LCD_Goto_Position(2, 16);
                LCD_WriteString(" ");
            }
            else
            {
                LCD_Goto_Position(2, 16);
                LCD_4bit_WriteDDRAM(0b01111111); //arrow
            }

            //3 if conditions, to remove the digit that is gone
            if (count2 < 1000)
            {
                LCD_Goto_Position(2,12);
                LCD_WriteString(" ");
            }
            else if (count2 < 100)
            {
                LCD_Goto_Position(2,11);
                LCD_WriteString(" ");
            }
            else
            {
                LCD_Goto_Position(2,10);
                LCD_WriteString(" ");
            }

            if (count1 == 0)
            {
                LCD_Goto_Position(1,9);
                LCD_WriteString("    ");
            }

            LCD_Goto_Position(2,9);
            LCD_WriteInt(count2);
            LCD_Goto_Position(1,9);
            LCD_WriteInt(count1);

            count2--;
            _delay_ms(10);
        }

    }
    return 0;
}
