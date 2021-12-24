= Arduino Micro based led cube =

This project is a 4x4x4 led cube, inspired by the 4x4x4 LED Cube (Arduino Uno) by KyleTheCreator
https://www.instructables.com/4x4x4-LED-Cube-Arduino-Uno/

Hardware differences 
* Arduino Micro
* Different pinout
* The LEDs are connected the opposite way

This code uses a graphical approach to which LEDs should be lit, rapidly
interleaving between layers using a timer interrupt. The timer interrupt
handles all the GPIO for lighting the cube, allowing the main code to focus
entirely on what to draw graphically.

Implements a number of effects:
- Text
- Scrolling text
- A cross
- A box
- Shrinking box
- Propeller Y
- Propeller X
- Propeller Z
- random flood
- random xor
- random decay
- random flashes

And supporting graphics primitives

- line
- box
- char (2d bitmap)

