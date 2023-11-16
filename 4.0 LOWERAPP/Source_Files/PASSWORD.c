/*
 * PASSWORD.c
 *
 * Created: 9/3/2020 9:24:10 PM
 *  Author: 8
 */ 
/* #include "LED.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "util/delay.h"

#define NUM 7

vuint8_t pass[]="#13499#";
vuint8_t inputt[16];
vuint16_t count=0,flag=0;

int main(void)
{
//Key_Configure(DIOA);

LCD_init();
LCD_DisplayString("Enter Your Pass");
LCD_Select_RowCol(1,0);
while(1)
{
uint8_t ch=Key_PRESSED(DIOA);
if(ch)
{
_delay_ms(400);
if(ch != 'D')
{
LCD_DisplayChar('*');
inputt[count++]=ch;
}
else
{
if(count == NUM)
{
for(vuint8_t i=0;i<NUM;i++)
{
if(pass[i] == inputt[i])
{
flag++;
}
else
{
break;
}
}
if(flag == NUM)
{
LCD_Clear();
LCD_Select_RowCol(0,0);
LCD_DisplayString("Correct pass");
_delay_ms(3000);
LCD_Clear();
LCD_DisplayString("Enter Your Pass");
LCD_Select_RowCol(1,0);
}
else
{
LCD_Clear();
LCD_Select_RowCol(0,0);
LCD_DisplayString("Wrong pass");
_delay_ms(1000);
LCD_Clear();
LCD_DisplayString("Enter Your Pass");
LCD_Select_RowCol(1,0);
}
}
else
{
LCD_Clear();
LCD_Select_RowCol(0,0);
LCD_DisplayString("Wrong pass");
_delay_ms(1000);
LCD_Clear();
LCD_DisplayString("Enter Your Pass");
LCD_Select_RowCol(1,0);
}
}

}

}

} */