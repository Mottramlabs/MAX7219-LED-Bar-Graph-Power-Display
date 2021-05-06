/*
    MAX7219 Power Display Round Type - Tester and Soak Tester
    Version 1 - 6th May 2021
    Board: Arduino UNO

    Pin connections
    Name      Arduino     MAX7219 7 Segment display
    -----------------------------------------------
              +5V         VCC
              GND         GND
    DIN       D11/MOSI    DIN
    CS        D10/SS      CS
    CLK       D13/SCK     CLK

    Speaker   D7          -

    David Mottram
*/

// SPI library needed for the MAX7219 library
#include <SPI.h>
#include <MAX7219_Digits.h>
#define MAX7219_CS 10                   // CS pin used on Arduino
MAX7219_Digit My_Display(MAX7219_CS);   // Make an instance of MAX7219_Digit called My_Display and set CS pin

int Bar_1[25] {0, 128, 192, 224, 240, 248, 252, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int Bar_2[25] {0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 192, 224, 240, 248, 252, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int Bar_3[25] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 192, 224, 240, 248, 252, 254, 255};

// speaker
const int Speaker =  7;


void setup(void) {

  Serial.begin(115200); Serial.println(""); Serial.println("Clackin!");

  // startup display and LED test
  My_Display.Begin();           // Set's all the registers and clears the display
  My_Display.Brightness(15);    // Set brightness 0-15

  tone(Speaker, 4000, 100);

} // End of setup

void loop() {

  for (int yy = 0; yy < 5; yy++) {

    for (float zz = 0; zz < 100.1;) {

      delay(1);

      // digit display
      My_Display.Display_Value(1, zz, 1, 0x00);

      int xx = zz;
      Serial.println(xx);

      xx = map(xx, 0, 100, 0, 25);
      My_Display.MAX7219_Write(5, Bar_1[xx]);
      My_Display.MAX7219_Write(6, Bar_2[xx]);
      My_Display.MAX7219_Write(7, Bar_3[xx]);

      zz = zz + 0.1;

    } // bar loop

  } // end of bar test

  // brightness test
  // brightness test
  My_Display.Display_Text(1, 0x08, 0x08, 0x08, 0x08, 0b1111); // (Display_Line, Char_1, Char_2, Char_3, Char_4, 0b0000)
  My_Display.MAX7219_Write(5, Bar_1[24]);
  My_Display.MAX7219_Write(6, Bar_2[24]);
  My_Display.MAX7219_Write(7, Bar_3[24]);

  for (int aa = 0; aa < 16; aa++) {
    My_Display.Brightness(aa);    // Set brightness 0-15
    delay(500);
  } // end brightness test

  delay(500);
  My_Display.Begin();             // Set's all the registers and clears the display

}// end of loop
