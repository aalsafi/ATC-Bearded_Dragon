// setting up display
#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define MAXDO   6
#define MAXCS   7
#define MAXCLK  8
#define RELAY1 9

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.write("Welcome Safi");
  delay(1000);
  Serial.begin(9600);

while (!Serial) delay(1); 
Serial.println("MAX31855 test");
 
delay(500);
  
Serial.print("Initializing sensor...");
  if (!thermocouple.begin()) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }

  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, HIGH);

  Serial.println("DONE.");  
}

void loop() {  
   Serial.print("Internal Temp: ");
   double int_temp = thermocouple.readInternal();
   Serial.println(int_temp);

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong!");
   } else {
     Serial.print("C = ");
     Serial.println(c);
   }

   lcd.clear();
   lcd.setCursor(0,1);
   lcd.write("Temp (C): ");
   lcd.print(c);

   if(c < 38){
    digitalWrite(RELAY1, LOW);
    Serial.println("Light On");
   }
   else if(c > 42){
    digitalWrite(RELAY1, HIGH);
    Serial.println("Light Off");
   }
   delay(1000);

}
