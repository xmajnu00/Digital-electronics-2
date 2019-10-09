/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED_PIN     PB5
#define BLINK_DELAY 500
#define LED2_PIN     PD4
#define button      PD2
//*#define bit_is_set(sfr,0)
//*#define bit_is_clear(PINB , 5)

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    
    GPIO_config_output (&DDRB,LED_PIN);
    GPIO_config_output(&DDRB, LED2_PIN);
    GPIO_config_input_pullup(&DDRD, &PORTD, button);
    
    

    /* Infinite loop */
    for (;;)
    {
        if(GPIO_read(&PIND, button) == 0)
        {
            GPIO_toggle(&PORTB, LED_PIN);
            GPIO_toggle(&PORTB, LED2_PIN);
            _delay_ms(BLINK_DELAY);
        }
    }

    return (0);
  
}
