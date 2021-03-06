#include <Arduino.h>
#include "secrets.h"
#include "variables.h"
#include "conexionesInalambricas.h"
#include "Estaciones.h"
#include "Maquinas.h"
#include "Alarma.h"
#include "Limpieza.h"

void callback(char* topic, byte* payload, unsigned int length) 
{
  // Tokening del topic
  int it=0;
  token = strtok(topic, "/");
  recepcion[it] = token;
  while(token != NULL)
  {
    it++;
    //Serial.println(token);
    token = strtok(NULL, "/");
    recepcion[it] = token;
  }

  // Lectura del mensaje
  String mensaje;
  for (int i = 0; i < length; i++) {
    mensaje = mensaje+(char)payload[i];
  }
  //Serial.println("Topico:"+String(topic)+"\t Mensaje:"+mensaje);

  // Logica del programa
  if(recepcion[0]==topico_raiz)
  {
    if(recepcion[1]==modulos[0])
    {
      Serial.println("Estas en el modulo:Limpieza");
      if(recepcion[2].toInt() >= 1 && recepcion[2].toInt() <= tamanoPinesLimpieza)
      {
        fLimpieza(recepcion[2].toInt(), mensaje);
      }
      else
      {
        Serial.println("No existe el elemento");
      }
    }
    if(recepcion[1]==modulos[1])
    {
      Serial.println("Estas en el modulo:Alarma");
      fAlarma(mensaje);
    }
    // if(recepcion[1]==modulos[2])
    // {
    //   Serial.println("Estas en el modulo:Maquina");
    // }
    if(recepcion[1]==modulos[3])
    {
      Serial.println("Estas en el modulo:Sensor");
    }
    if(recepcion[1]==modulos[4])
    {
      Serial.println("Estas en el modulo:Alerta");
    }
  }
}

void setup ()
{  
  Serial.begin(115200);
////////////////////////////Pines Usados ///////////////////////////////
  
  pinMode(15,INPUT);        //Maqquina1--Pulsante
  pinMode(16,INPUT);        //Maqquina2--Pulsante
  initLimpieza();
  //initAlarma();           //Descomentar cuando se tenga los pines que son


/////////////////////////////////////////////////////////////////////////  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() 
{
  if (!client.connected()) 
  {
    reconnect();
  }
  unsigned long now = millis();

  // Envio de datos desde ESP hacia el broker cada 2 segundos
  if ((now - lastMsg) > 5000) 
  {
    lastMsg = now;
    activarMaquina(1, estadoMaquina);
    estadoMaquina = !estadoMaquina;
  }
  client.loop();
}
