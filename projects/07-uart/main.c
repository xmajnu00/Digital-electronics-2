/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
 * 
 * Note:
 *    Peter Fleury's UART library.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_puts("LCD testing");


    /* ADC
     * TODO: Configure ADC reference, clock source, enable ADC module, 
     *       and enable conversion complete interrupt */
    ADMUX &= ~(_BV(REFS1) | _BV(MUX2) |_BV(MUX1) |_BV(MUX0));
    ADMUX |= (_BV(REFS0));

    ADCSRA |= (_BV(ADEN) |_BV(ADIE) | _BV(ADPS2) |_BV(ADPS1) |_BV(ADPS0));
     

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
     TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Start ADC conversion
     ADCSRA |= _BV(ADSC);
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
   uint16_t value = 0;
   char uart_string[10];

	// Read 10-bit ACD value
   value = ADC;

  
if (value < 90)
    {
    uart_puts("\r\n\033[4;32m");   
    uart_puts("RIGHT");
    uart_putc(' ');
    uart_puts("\033[0m");
    } 
    
else if(value >= 90 && value <= 195)
    {
    uart_puts("\r\n\033[4;32m");   
    uart_puts("UP");
    uart_putc(' ');
    uart_puts("\033[0m");
    } 
  

else if(value >= 195 && value <= 380)
    {
    uart_puts("\r\n\033[4;32m");   
    uart_puts("DOWN");
    uart_putc(' ');
    uart_puts("\033[0m");
    } 
  


else if(value >= 380 && value <= 555)
    {
    uart_puts("\r\n\033[4;32m");   
    uart_puts("LEFT");
    uart_putc(' ');
    uart_puts("\033[0m");
    } 
  


else if(value >= 555 && value <= 790)
    {
    uart_puts("\r\n\033[4;32m");   
    uart_puts("SELECT");
    uart_putc(' ');
    uart_puts("\033[0m");
    } 

 


    lcd_clrscr();
    lcd_gotoxy(0,0);
    lcd_puts(uart_string);
   


    itoa(value, uart_string, 10);    
 

    if (value < 90)
    {
    lcd_gotoxy(0,1);
    lcd_puts("RIGHT");
    lcd_putc(' ');
    } 
    else if(value >= 90 && value <= 195)
    {
    lcd_gotoxy(0,1);
    lcd_puts("UP");
    lcd_putc(' ');
    } 
    else if(value >= 195 && value <= 380)
    {
    lcd_gotoxy(0,1);
    lcd_puts("DOWN");
    lcd_putc(' ');
    } 
    else if(value >= 380 && value <= 555)
    {
    lcd_gotoxy(0,1);
    lcd_puts("LEFT");
    lcd_putc(' ');
    } 
    else if(value >= 555 && value <= 790)
    {
    lcd_gotoxy(0,1);
    lcd_puts("SELECT");
    lcd_putc(' ');
    } 
    
    // TODO: Update LCD and UART transmiter
}
