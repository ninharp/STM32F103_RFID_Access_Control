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

![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo0.jpg?raw=true](Enclosure)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo1.jpg?raw=true](Photo1)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo2.jpg?raw=true](Photo2)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo3.jpg?raw=true](Photo3)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo4.jpg?raw=true](Photo4)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo5.jpg?raw=true](Photo5)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo6.jpg?raw=true](Photo6)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo7.jpg?raw=true](Photo7)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo8.jpg?raw=true](Photo8)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo9.jpg?raw=true](Photo9)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo10.jpg?raw=true](Photo10)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo11.jpg?raw=true](Photo11)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo12.jpg?raw=true](Photo12)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo13.jpg?raw=true](Photo13)
![https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo14.jpg?raw=true](Photo14)