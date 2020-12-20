/*  
 12 bit ADC
 full range 4095
 8 bit DAC1 DAC2
 full range 255
 
 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define button0    0 
#define button1   35
#define ADC        2 // input pin for ADC
#define bat_volts 34 // ready battery volts/2
#define DAC1      25 // output DAC
#define DAC2      26 // output DAC
#define backlit    4 // LCD Backlight, set low to turn off

int volts = 64;      // DAC bit setting (8 bits)

void setup(void) {
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  tft.init();
  tft.setRotation(1);  // rotate display every 90 degrees 1...3
  tft.setTextColor(TFT_GREEN,TFT_BLACK); 
}

void loop() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);    // size 4 font
  dacWrite(DAC1, 128);       // fixed DAC
  dacWrite(DAC2, volts);     // varying DAC
  tft.print(3.68*float(analogRead(ADC))/4095);
  tft.println(" Volts Pin 2");
  tft.println();
  tft.println("DAC1 set at 128");
  tft.println("DAC2 up/down");
  tft.print(2*3.68*float(analogRead(bat_volts))/4095);
  tft.println(" Volts Battery");
  if(digitalRead(button1) != 1) if (volts<255) volts++;
  if(digitalRead(button0) != 1) if (volts>0)   volts--;
  delay(500);
}
