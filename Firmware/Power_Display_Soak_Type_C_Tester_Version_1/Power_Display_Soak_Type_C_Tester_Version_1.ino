/*
    MAX7219 Power Display Type B - Tester and Soak Tester
    Version 2 - 3rd December 2018
    Board: ESP8266 Backboard

    Pin connections
    Name      ESP8266     MAX7219 7 Segment display
    -----------------------------------------------
              +5V         VCC
              GND         GND
    DIN       GPIO13/MOSI DIN
    CS        GPIO15/SS   CS
    CLK       GPio14/SCK  CLK

    Speaker   GPIO12       -

    David Mottram
*/

// SPI library needed for the MAX7219 library
#include <SPI.h>
#include <MAX7219_Digits.h>
#define MAX7219_CS 15                  // CS pin used on Arduino
MAX7219_Digit My_Display(MAX7219_CS); // Make an instance of MAX7219_Digit called My_Display and set CS pin

// There are 16 LED's in the bar display the array below is 0-17 where 0 (all off) to 17 (all on)
int Bar_1[17] {0, 128, 192, 224, 240, 248, 252, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int Bar_2[17] {0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 192, 224, 240, 248, 252, 254, 255};

// speaker
const int Speaker =  12;
#include <ESP8266_Tones.h>
ESP8266_Tones Mytone(Speaker);

void setup(void) {

  Serial.begin(115200); Serial.println(""); Serial.println("Clackin!");

  // startup display and LED test
  My_Display.Begin();           // Set's all the registers and clears the display
  My_Display.Brightness(15);    // Set brightness 0-15

  My_Display.Display_Text(1, 0x08, 0x08, 0x08, 0x08, 0b1111); // (Display_Line, Char_1, Char_2, Char_3, Char_4, 0b0000)
  My_Display.Display_Text(2, 0x08, 0x08, 0x08, 0x08, 0b1111); // (Display_Line, Char_1, Char_2, Char_3, Char_4, 0b0000)
  Mytone.Close_Encounters(Speaker);

  delay(2000);
  My_Display.Begin();           // Set's all the registers and clears the display

} // End of setup

void loop() {

  for (int yy = 0; yy < 5; yy++) {

    for (float zz = 0; zz < 100.1;) {

      delay(1);

      // digit display
      My_Display.Display_Value(1, zz, 1, 0x00);

      int xx = zz;
      Serial.println(xx);

      xx = map(xx, 0, 100, 0, 17);
      My_Display.MAX7219_Write(5, Bar_1[xx]);
      My_Display.MAX7219_Write(6, Bar_2[xx]);

      zz = zz + 0.1;

    } // bar loop

  } // end of bar test

  My_Display.Begin();         // Set's all the registers and clears the display
  delay(1000);

  My_Display.MAX7219_Write(7, 128);
  delay(500);
  My_Display.MAX7219_Write(7, 64);
  delay(500);
  My_Display.MAX7219_Write(7, 32);
  delay(500);
  My_Display.MAX7219_Write(7, 16);
  delay(500);
  My_Display.MAX7219_Write(7, 0);
  delay(500);

  My_Display.Brightness(0);   // Set brightness 0-15

  My_Display.Display_Text(1, 0x08, 0x08, 0x08, 0x08, 0b1111); // (Display_Line, Char_1, Char_2, Char_3, Char_4, 0b0000)
  My_Display.Display_Text(2, 0x08, 0x08, 0x08, 0x08, 0b1111); // (Display_Line, Char_1, Char_2, Char_3, Char_4, 0b0000)

  // brightness test
  for (int aa = 0; aa < 16; aa++) {
    My_Display.Brightness(aa);  // Set brightness 0-15
    delay(500);
  } // end brightness test

  delay(500);
  My_Display.Begin();           // Set's all the registers and clears the display

}// end of loop
