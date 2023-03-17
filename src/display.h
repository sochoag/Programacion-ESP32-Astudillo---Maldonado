#include <ArduinoJson.h>

StaticJsonDocument<2000> doc;


void enviarDatos()
{
  String temp;
  // int cont = rand();
  serializeJson(doc, temp);
  char msg[300];
  temp.toCharArray(msg, temp.length()+1);
  xQueueSend(queue, &msg, portMAX_DELAY);
  // xQueueSend(queue, &cont, portMAX_DELAY);
}

void initValues()
{
  doc["Alerta"][0] = "V";
  doc["Alerta"][1] = "V";
  doc["Limpieza"][0] = false;
  doc["Limpieza"][1] = false;
  doc["Maquina"][0] = false;
  doc["Maquina"][1] = false;
  doc["Sensor"][0] = 0.0;
  doc["Sensor"][1] = 0.0;
}
// void setup() 
// {
//   Serial.begin(115200); 
// }

// void loop() 
// {

//   //serializeJsonPretty(doc, Serial);

//   enviarAPantalla();
//   delay(3000);
// }
