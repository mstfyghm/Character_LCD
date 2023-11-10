// This library is written for 4-bit interface with character lcd
#include <stdint.h>


//---------------------------User defined pins-----------------
#define LCD_RS_PORT PORTD
#define LCD_RS 4
#define LCD_EN_PORT PORTD
#define LCD_EN 5
#define LCD_DB4_PORT PORTD
#define LCD_DB4 0
#define LCD_DB5_PORT PORTC
#define LCD_DB5 3
#define LCD_DB6_PORT PORTD
#define LCD_DB6 2
#define LCD_DB7_PORT PORTD
#define LCD_DB7 3

#define N_OF_LINES 2
#define N_OF_COLLUMNS 16
//--------------------------LCD commands--------------------
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_RETURN_HOME 0x02
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON 0x0C
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_BLINK 0x0F
#define LCD_DISPLAY_SHIFT 0x18
#define LCD_CURSOR_SHIFT_RIGHT 0x14 
#define LCD_CURSOR_SHIFT_LEFT 0x10
#define LCD_FUNCTION_SET 0x28
#define LCD_SET_CGRAM_ADDRESS 0x40
#define LCD_SET_DDRAM_ADDRESS 0x80
#define LCD_DDRAM_2ND_ROW_OFFSET 0x40
#define LCD_DDRAM_3RD_ROW_OFFSET 0x14
#define LCD_DDRAM_4TH_ROW_OFFSET 0x54

void lcd_init(void);

void lcd_on(void);

void lcd_off(void);

void lcd_clear(void);

void lcd_return_home(void);

void lcd_cursor_on(void);

void lcd_corsur_off(void);

void lcd_cursor_blink(void);

void lcd_gotoxy(uint8_t x, uint8_t y);

void lcd_shift(int8_t steps, uint8_t delay);

void lcd_putch(char ch);

void lcd_puts(char *str);
