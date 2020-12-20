/*  
 Test the tft.print() viz embedded tft.write() function

 This sketch used font 2, 4, 7
 
 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 Note that yield() or delay(0) must be called in long duration for/while
 loops to stop the ESP8266 watchdog triggering.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */


#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define button0  0
#define button1  35
#define led  17
int f = 2;

void setup(void) {
  
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(led, OUTPUT);
  tft.init();
  tft.setRotation(1);
  tft.setTextColor(TFT_GREEN,TFT_BLACK); 
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  tft.println("IMSAI Guy");
  tft.println("Press Button...");
}

void loop() {
  while(digitalRead(button0) != 1){
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, f);
    if(f ==2 || f==4) tft.print("Font number ");
       else { tft.print(123);
              tft.print(" ");
       }       
    tft.println(f);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, 4);
    tft.println("Press Button");
    f++;
    if(f == 3 || f==5) f++;
    if(f >= 9) f = 2;
    }
  while(digitalRead(button1) != 1){
    tft.setTextColor(TFT_WHITE,TFT_BLACK); 
    tft.setTextSize(2);
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, 2);
    tft.println("Text Size 2");
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, 4);
    tft.println("Press Button");
    }
}
