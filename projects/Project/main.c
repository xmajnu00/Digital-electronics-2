#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "timer.h"
#include "gpio.h"


#define UART_BAUD_RATE 9600

//

 uint16_t horizontal = 0;
 uint16_t vertical = 0;
 char uart_string[4];
 char counter_string[4];
int main(void)
{

    //Configer output pin for PWM regulation(otput pin OC1A)
    GPIO_config_output(&DDRB, PB1);
    GPIO_config_output(&DDRB, PB2);


    //Set pins PC0, PC1 as ADC inputs
    DDRC &= ~(_BV(PC0) | _BV(PC1));
    
    //enable ADC
    GPIO_write(&ADCSRA,ADEN,1);             
    
    //set refference voltage to 5V and input channel to ADC0(pin PC0)
    ADMUX &= ~( _BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3));
	ADMUX |= (_BV(REFS0));

    //set ADC prescaler as 64, enable ADC interrupt
    ADCSRA &= ~(_BV(ADPS0));
    ADCSRA |= (_BV(ADPS1) | _BV(ADPS2) | _BV(ADIE));

    //set ADC trigger on Timer0 overflow
    ADCSRB &= ~(_BV(ADTS1) | _BV(ADTS2));
    ADCSRB |= (_BV(ADTS2));

    //set Timer0 prescaler and interrupt (controls ADC)
    TIM_config_prescaler(TIM0, TIM_PRESC_64);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    //set Timer1 prescaler and interrupt (controls PWM)
    TIM_config_prescaler(TIM1, TIM_PRESC_8);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    //configure Timer1 for Fast PWM operation (WGM 13:0)
    TCCR1A |= (_BV(WGM11) | _BV(COM1A1) | _BV(COM1B1));
    TCCR1A &= ~(_BV(COM1A0) | _BV(COM1B0));

    TCCR1B |= (_BV(WGM12) | _BV(WGM13));

    //defines mode when OC1A pin is enabled on compare match and clears when BOTTOM  

    ICR1 = 39999;               //defines TOP of the TIM1, causes counter reset to BOTTOM
	
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	
    sei();

    for (;;) 
    {
        OCR1A = 1500 + (horizontal * 3.71); //
        OCR1B = 1500 + (vertical * 3.71);

        //maximum and minimum test rotate   
        /*OCR1A = 1500;                          
        _delay_ms(1000);
        OCR1A = 3000+300;
        _delay_ms(1000);
        OCR1A = 5300; 
        _delay_ms(1000);*/

        //upload to putty view for joystick
        itoa(horizontal, uart_string, 10);      
        uart_puts(uart_string);
        uart_puts("\r\n");
    }

    return (0);
}

//interrupt triggers ADC conversion
ISR(TIMER0_OVF_vect)
{
   GPIO_write(&ADCSRA,ADSC,1); 
}

ISR(TIMER1_OVF_vect)                          //overflow interrupt
{

}

ISR(ADC_vect)                                //conversion done interrupt
{
	// Read 10-bit ACD value
    switch (ADMUX)
    {
        case 0x40:                          //0b0100 0000
            horizontal = ADC;
            ADMUX =0x41;                    //0b0100 0001 AC1
            break;

        case 0x41:
            vertical = ADC;
            ADMUX = 0x40;                   //0b0100 0000 AC0
            break;
        default:
            //Default code
            break;
    }
	
    
}