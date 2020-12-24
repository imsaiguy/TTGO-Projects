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
#include <Wire.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define I2C_SDA 21
#define I2C_SCL 22

void setup(void) {
  tft.init();
  tft.setRotation(1);  // rotate display every 90 degrees 1...3
  tft.setTextColor(TFT_GREEN,TFT_BLACK); 
  Wire.begin(I2C_SDA, I2C_SCL);
}

void loop() {
  byte error, address;
  int nDevices; 
  nDevices = 0;
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);    // size 4 font
  tft.println("I2C Addresses:");
  
  for(address = 1; address < 127; address++ ) { 
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      tft.print("0x"); 
      if (address<16) tft.print("0");
      tft.print(address, HEX);
      tft.print(" ");
      nDevices++;
    }
    else 
    if (error==4) {
      tft.print("error@ 0x");
      if (address<16) tft.print("0");
      tft.println(address,HEX);
    }    
  }
  if (nDevices == 0) tft.println("None");
  
  delay(2000);           // wait 2 seconds for next scan  
}
