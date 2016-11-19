# RFID MFRC522 Access Control #

![Project](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/project.jpg?raw=true)

## Project and Goals ##

Made a simple and easy to use solution for door entry systems (or maybe other purposes) with rfid tag combined with keypad.
First i think i can complete this project in the already existing repository [Arduino RC522 RFID Access Control](https://github.com/omersiar/RFID522-Door-Unlock) but than i decided to make a new project with a STM32 F103RB microprocessor cause i got with all pins used only 1 pin open if a use a simple Arduino UNO Board and i only got some Nucleo Boards which will support the count of pins i had to use.
I build all hardware in a Hammond enclosure with the ability to position it next to a door or something.

### What Hardware is used? ###

* STM32F103RB as Microcontroller on Nucleo F103 Board as CPU
* MFRC522 RFID Reader Module
* 4x5 Keypad Matix (optionally you can use TTP229 based touch keys)
* A beeper for simple sound feedback
* Two LEDs for visual feedback (green and red)

* Hammond Enclosure 1594E (lil' big, but it looks good)

### Libraries used ###

* SPI Library for MFRC522 RFID Reader
* Modified KeyPad Matrix Library from Tilen Majerle
* Modified MFRC522 Library also from Tilen Majerle
* Feedback Library for the audiovisual feedbacks
* UART Library for Debug output to RS232 (only in debug releases)
* TTP229 Touch Controller Library (optional instead of keypad matrix)

### Pictures from assembling ###

![Enclosure](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo0.jpg?raw=true)
Enclosure

![Photo1](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo1.jpg?raw=true)
The KeyPad Matrix i used

![Photo2](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo2.jpg?raw=true)
The cheap china MFRC522 RFID Reader

![Photo3](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo3.jpg?raw=true)
TTP229 Touchpad Controller Test Board

![Photo4](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo4.jpg?raw=true)
The Nucleo Board with STM32F103RB as Central Unit

![Photo6](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo6.jpg?raw=true)
![Photo14](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo14.jpg?raw=true)
Groundplate for the Nucleo Board to attach inside of enclosure with double faced adhesive tape

![Photo8](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo8.jpg?raw=true)
I cutted some plastic screws and glued it in small drilled holes in the front of the enclosure, these pins will hold
the RFID Reader

![Photo7](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo7.jpg?raw=true)
Here you see the hole for the keypad matrix and the board for the two front leds

![Photo9](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo9.jpg?raw=true)
The RFID Reader fully mounted on front

![Photo10](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo10.jpg?raw=true)
The sensitive area from the RFID Reader is just under the keypad matrix

![Photo12](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo12.jpg?raw=true)
The buzzer was simply glued to an hole in the enclosure (down faced), so it uses the enclosure as additional 
resonating body
 
![Photo13](https://github.com/ninharp/STM32F103_RFID_Access_Control/blob/master/doc/images/photo13.jpg?raw=true)
These small plastic servo i use for testing purposes in this project

### License ###

This procject is released under the GNU General Public License, you find a copy of the whole license
in the LICENSE file in the root of this project.
