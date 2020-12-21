/*  
 uBlox GPS Neo 6M used
 
 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */
#include <TFT_eSPI.h>              // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();         // Invoke library, pins defined in User_Setup.h

#include <TinyGPS.h> 
TinyGPS gps;                       // create gps object 

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long age;
char sz[32];

void setup(void) {
  Serial.begin(115200);  
  Serial2.begin(9600, SERIAL_8N1, 38, 37); // connect GPS TX to IO38
  tft.init();
  tft.setRotation(1);                   // rotate display every 90 degrees 1...3
  tft.setTextColor(TFT_GREEN,TFT_BLACK); 
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);               // size 4 font
  tft.println("GPS Demo"); 
}

void loop() {
  while(Serial2.available()) {          // check for gps data 
    if(gps.encode(Serial2.read())) {    // encode gps data 
      gps.f_get_position(&lat,&lon);    // get latitude and longitude 
      gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 0, 4);           // size 4 font 
      tft.println("GPS Location"); 
      tft.print(" LAT:  "); 
      tft.println(lat); 
      tft.print("LON:  "); 
      tft.println(lon); 
      tft.print(3.281*gps.f_altitude());
      tft.println(" Feet");
      sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d   ",
        month, day, year, hour, minute, second);
      tft.println(sz);                  // GMT date/time
    }
  } 
  delay(800);
}
 
