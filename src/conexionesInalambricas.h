#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
  delay(10);
  // Coneccion con la red Wifi -- We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect()
{
  // Ciclo repetitivo hasta que se coecte al MQTT -- Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Creacion de ID Random -- Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Intento de Conexion -- Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");

      // Anuncio de Conexion exitosa -- Once connected, publish an announcement...//

      client.publish("8cBAzaR8Jiya7Fq/mensaje", "Coneccion exitosa a topico Limpieza");
      client.publish("30M3qAhyF0GsxTL/mensaje", "Coneccion exitosa a topico Alarmas");

      /////////////////////////Suscripcion a Topicos/////////////////////////////////////
      for(int i=0; i<tamanoModulos ; i++)
      {
        client.subscribe((topico_raiz+"/"+modulos[i]+"/#").c_str());
        Serial.println("Suscrito a:" + topico_raiz +"/"+modulos[i]+"/#");
      }
      /*client.subscribe(topico_1.c_str());
      client.subscribe(topico_2.c_str());
      client.subscribe(topico_3.c_str());
      client.subscribe(topico_4.c_str());
      client.subscribe(topico_5.c_str());
      client.subscribe(topico_6.c_str());
      client.subscribe(topico_7.c_str());
      client.subscribe(topico_8.c_str());
      client.subscribe(topico_9.c_str());
      client.subscribe(topico_10.c_str());*/
      ///////////////////////////////////////////////////////////////////////////////////
      // Resuscripcion -- and resubscribe
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
