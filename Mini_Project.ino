#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     
#define DHTTYPE DHT11 

#define delayMS 1000
#define fanPin 9

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Temperature °C \t|\tFan Speed %");
  Serial.println("__________________________________");
  Serial.println();
}

void loop() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    float tempC = event.temperature;
    int mVal = map(tempC,24,30,0,255);
    Serial.print(tempC);
    Serial.print("°C\t\t|\t");
    Serial.print((mVal/255.0)*100);
    Serial.println("%");
    analogWrite(fanPin,mVal);
  }
  delay(delayMS);
}
