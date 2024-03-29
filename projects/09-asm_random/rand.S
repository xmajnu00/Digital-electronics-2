;* ---------------------------------------------------------------------
;*
;* Assembly implementation of 4- and 8--bit LFSR-based (Linear Feedback
;* Shift Register) pseudo-random generators.
;* ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
;*
;* Copyright (c) 2017-2019 Tomas Fryza
;* Dept. of Radio Electronics, Brno University of Technology, Czechia
;* This work is licensed under the terms of the MIT license.
;*
;* https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
;* http://courses.cse.tamu.edu/walker/csce680/lfsr_table.pdf
;*
;* ---------------------------------------------------------------------

;* Includes ------------------------------------------------------------
; Set offset for control register addresses (NEEDED FOR I/O REGISTERS)
#define __SFR_OFFSET    0
#include <avr/io.h>

;* Define --------------------------------------------------------------
#define result  r16
#define temp    r17
#define input   r24

;* Functions -----------------------------------------------------------
;* LFSR-based 4-bit pseudo-random generator.
;* Input:  r24 - Current value of shift register
;* Return: r24 - New value of shift register
.global rand4_asm
rand4_asm:
    loop:
        SBI PORTB,5
        CBI PORTB,5
        dec input
        brne loop
        
    ret                     ; Return from subroutine
