#include <avr/io.h>
#include <util/delay.h>
#include"char_lcd.h"
#include <stdio.h>

int main(void)
{
    DDRD=0xFF;
    lcd_init();
    lcd_on();
    lcd_puts("Hello World!");
    _delay_ms(1000);
    lcd_shift(10,60);
    lcd_shift(-10,60);
    lcd_clear();
    char str[16];
    uint8_t i=0;
    while(1)
    {
       lcd_clear();
       sprintf(str,"counter=%d",i);
       lcd_puts(str);
       i++;
       _delay_ms(100);
        
    }
    return 0;
}
