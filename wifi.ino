#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <WiFi.h>


#define LED D3 // Led in NodeMCU at pin GPIO16 (D0).
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//SSID of your network
char ssid[] = "Eval";
//password of your WPA Network
char pass[] = "one1";
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // set the digital pin as output.
  
  Serial.println("ESP8266 WiFi Signal Strength Checker");

//  // Set WiFi to station mode and disconnect from an AP if it was previously connected
//  WIFI_MODE_STA;
//  WiFi.disconnect();
//  delay(10);

  WiFi.begin(ssid, pass);
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print("\nConnected to: ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("");}
}


void loop() {
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);
  delay(1000);

  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}
