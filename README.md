# RFID MFRC522 Access Control #

## Goal ##

Made a simple and easy to use solution for door entry systems (or maybe other purposes) with rfid tag combined with keypad.
First i think i can complete this project in the already existing repository [Arduino RC522 RFID Access Control](https://github.com/omersiar/RFID522-Door-Unlock) but than i decided to make a new project with a STM32 F103RB microprocessor cause i got with all pins used only 1 pin open if a use a simple Arduino UNO Board and i only got some Nucleo Boards which will support the count of pins i had to use.
I build all hardware in a Hammond enclosure with the ability to position it next to a door or something.

### What Hardware is used? ###

* STM32F103RB as Microcontroller on Nucleo F103 Board as CPU
* MFRC522 RFID Reader Module
* 4x5 Keypad Matix (optionally you can use TTP229 based touch keys)
* A beeper for simple sound feedback
* Two LEDs for visual feedback

