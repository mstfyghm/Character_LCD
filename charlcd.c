// This library is written for 4-bit interface with character lcd
#include<avr/io.h>
#include <char_lcd.h>
#include <util/delay.h>

//--------------------------Static functions (for use only in this file)-------------------

static void _lcd_set_nibble(uint8_t data)
{
    if(data & 0x01) 
        LCD_DB4_PORT|=(1<<LCD_DB4);
    else   
        LCD_DB4_PORT &=~(1<<LCD_DB4);

    if(data & 0x02) 
        LCD_DB5_PORT|=(1<<LCD_DB5);
    else   
        LCD_DB5_PORT &=~(1<<LCD_DB5);
    
    if(data & 0x04) 
        LCD_DB6_PORT|=(1<<LCD_DB6);
    else   
        LCD_DB6_PORT &=~(1<<LCD_DB6);
    
    if(data & 0x08) 
        LCD_DB7_PORT|=(1<<LCD_DB7);
    else   
        LCD_DB7_PORT &=~(1<<LCD_DB7);
}

static inline void en_pulse(void)
{
    LCD_EN_PORT |=(1<<LCD_EN);
    _delay_us(1);
    LCD_EN_PORT &=~(1<<LCD_EN);
}

static void _lcd_send_command(uint8_t cmd)
{
    
    LCD_RS_PORT &=~(1<<LCD_RS);
    
    _lcd_set_nibble(cmd>>4);
    en_pulse();

    _lcd_set_nibble(cmd);
    en_pulse();
    _delay_us(40);
}

static void _lcd_send_data(uint8_t data)
{
    
    LCD_RS_PORT |=(1<<LCD_RS);
    
    _lcd_set_nibble(data>>4);
    en_pulse();

    _lcd_set_nibble(data);
    en_pulse();
    _delay_us(40);
}

static inline void _lcd_set_ddram_address(uint8_t address)
{
    _lcd_send_command(LCD_SET_DDRAM_ADDRESS | address);
}
//---------------------------User applicable functions-------------------
/**
 * 
 * 
*/
void lcd_init(void)
{

    _delay_ms(20);
    LCD_RS_PORT &=~(1<<LCD_RS);
    _lcd_set_nibble(0x03);
    en_pulse();
    _delay_ms(5);

    _lcd_set_nibble(0x03);
    en_pulse();
    _delay_us(100);

    _lcd_set_nibble(0x03);
    en_pulse();
    _delay_us(40);

    _lcd_set_nibble(0x02);
    en_pulse();
    _delay_us(40);

    _lcd_send_command(LCD_FUNCTION_SET);
    lcd_off();
    lcd_clear();
}

void lcd_on(void)
{
    _lcd_send_command(LCD_DISPLAY_ON);
    _delay_ms(200);
}

void lcd_off(void)
{
    _lcd_send_command(LCD_DISPLAY_OFF);
}

void lcd_clear(void)
{
    _lcd_send_command(LCD_CLEAR_DISPLAY);
    _delay_ms(2);
}

void lcd_return_home(void)
{
    _lcd_send_command(LCD_RETURN_HOME);
}

void lcd_cursor_on(void)
{
    _lcd_send_command(LCD_CURSOR_ON);
}

void lcd_corsur_off(void)
{
    _lcd_send_command(LCD_DISPLAY_ON);
}

void lcd_cursor_blink(void)
{
    _lcd_send_command(LCD_CURSOR_BLINK);
}

void lcd_gotoxy(uint8_t x, uint8_t y)
{
    switch(y)
    {
        case 0:
            _lcd_set_ddram_address(x);
        break;
        case 1:
            _lcd_set_ddram_address(LCD_DDRAM_2ND_ROW_OFFSET+x);
        break;
        case 2:
            _lcd_set_ddram_address(LCD_DDRAM_3RD_ROW_OFFSET+x);
        break;
        case 3:
            _lcd_set_ddram_address(LCD_DDRAM_4TH_ROW_OFFSET+x);
        break;
        
    }
}

void lcd_shift(int8_t steps, uint8_t delay_in_ms)
{
    uint8_t direction=0x04;
    if(steps<0)
    {
        steps=-steps;
        direction=0x00;
    }
    for(uint8_t i=steps;i>0;i--)
    {
        _lcd_send_command(LCD_DISPLAY_SHIFT | direction);
        _delay_ms(delay_in_ms);
    }
}

void lcd_putch(char ch)
{
    _lcd_send_data(ch);
}

void lcd_puts(char *str)
{
    while(*str!='\0')
        lcd_putch(*(str++));
}
