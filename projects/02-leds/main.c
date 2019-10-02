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
    /* Set output pin */
    DDRB |= _BV(LED_PIN);           /* DDRB = DDRB or (0010 0000) */
    DDRD |= _BV(LED2_PIN);
    DDRD &= ~_BV(button);
    /* Turn LED off */
    PORTD |= _BV(button);
    PORTB &= ~_BV(LED_PIN);         /* PORTB = PORTB and (0010 0000) */
    PORTD &= ~_BV(LED2_PIN);
    

    /* Infinite loop */
    for (;;)
    {
      if (bit_is_clear(PIND , button))
      {
       /* Invert LED and delay */
        PORTB ^= _BV(LED_PIN);      /* PORTB = PORTB xor (0010 0000) */
         PORTD ^= _BV(LED2_PIN);   
         _delay_ms(BLINK_DELAY);     /* Wait for several milisecs */
      }
    }

    return (0);
  
}
