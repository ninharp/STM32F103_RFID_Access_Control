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

### Pictures from assembling ###

![doc/images/photo0.jpg](Enclosure)
![doc/images/photo0.jpg](Photo1)
![doc/images/photo0.jpg](Photo2)
![doc/images/photo0.jpg](Photo3)
![doc/images/photo0.jpg](Photo4)
![doc/images/photo0.jpg](Photo5)
![doc/images/photo0.jpg](Photo6)
![doc/images/photo0.jpg](Photo7)
![doc/images/photo0.jpg](Photo8)
![doc/images/photo0.jpg](Photo9)
![doc/images/photo0.jpg](Photo10)
![doc/images/photo0.jpg](Photo11)
![doc/images/photo0.jpg](Photo12)
![doc/images/photo0.jpg](Photo13)
![doc/images/photo0.jpg](Photo14)
