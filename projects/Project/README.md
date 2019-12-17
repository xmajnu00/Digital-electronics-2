
# Ovládání několika servomotorů SG90 analogovými joystiky HW-504

#### Table of Contents

1. [Introduction](#introduction)
2. [Hardware](#hardware)
3. [Software](#software)
4. [References](#references)


## Introduction
Téma tohoto projektu bylo Ovládání několika servomotorů SG90 analogovými joystiky HW-504. Podle zadání měl být kód psán v jazyce C. Arduino UNO obsahuje šest kanálu pro ADC převod. Pro naši práci jsme využili za pomocí ADC převodníku kanály pouze 2 a to AC0 a AC1. Tento převodník jsme spouštěli s předděličkou 64 pro Timer0. Použili jsme komparační mód "Analog comparator". Použili jsme joystick HW-504, který obsahuje dva interní potenciometr pro horizontální a vertikální polohu. Při vychýlení joysticku do maximální polohy dosahujeme hodnot výchylky od 0 do 1013. Tyto údaje jsou následně přivedeny na vstup ADC komparátoru. Za pomocí použití UART-u, jsme byli schopni zobrazovat hodnoty poloh joystiku v počítačovém prostředí Putty. <br/>
Servomotor SG 90 pracuje na frekvenci 50Hz a je schopen se otáčet ze základní polohy 0° do +-90°. Při uvedení joysticku do neutrální polohy dochází k vrácení servomotoru do výchozí pozice. Pro ovládání servomotoru je použita PWM (Pulse-width modulation) modulace s dělékou pulzu 20ms. Úhel natočení se odvíjí od střídy, která při šířce 1ms otáčí sevomotor o -90°, pro 2ms je úhel natočení +90° a 1.5ms nastaví motor do výchozí pozice 0°. Požadovanou frekvenci 50Hz, jsme spočítali pomocí vzorce uvedeného v datasheetě pro Fast PWM modulaci. PWM modulace využívá timer1, který je 16bitový. Obsahuje dva registry OC1A a OC1B, díky kterým jsme mohli zpracovávat dva kanály zároveň.  <br/>
Ve výsledném zapojení podle schématu, jsou jednotlivé servomotory ovládány pomocí joystiku. Vertikální pohyb joystiku ovládá jeden servomotor a horizontální pohyb druhý motor. <br/>
![Schéma zapojení](https://github.com/xmajnu00/Digital-electronics-2/blob/master/Untitled.jpg)

## Hardware

Arduino UNO ATMega328P <br/>
SG 90 servomotor <br/>
HW-504 Joystick <br/>
Nepájivé pole <br/>
Kabeláž 

## Software

Visual studio

## References

1. Microchip, [AVR 8-bit Toolchain for Windows, Linux, Mac OS X](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)
2. SG90, [schéma SG90](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)
3. HW-504, [HW-504 dataheet](http://www.energiazero.org/arduino_sensori/joystick_module.pdf)
4. [Servomotor](https://www.electronicwings.com/avr-atmega/servo-motor-interfacing-with-atmega16)
