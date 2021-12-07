#include <Arduino.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;

void enviarAPantalla()
{
  doc["sensor1"] = random(999);
  // doc["time"] = random(20);
  // doc["data"][0] = 4;
  // doc["data"][1] = 3;

  serializeJson(doc, Serial);
}

void setup() 
{
  Serial.begin(115200); 
}

void loop() 
{

  //serializeJsonPretty(doc, Serial);

  enviarAPantalla();
  delay(3000);
}
