# Arduino Micro based led cube

This project is a 4x4x4 led cube, inspired by the 4x4x4 LED Cube (Arduino Uno) by KyleTheCreator
https://www.instructables.com/4x4x4-LED-Cube-Arduino-Uno/

Hardware differences 
* Arduino Pro Mini
* Different pinout
* The LEDs are connected the opposite way

This code uses a graphical approach to which LEDs should be lit, interleaving between layers.

The timing of the interleaving and graphical effects are implemented using protothreads

Implements only a single effect with a bitmap drawn cube
