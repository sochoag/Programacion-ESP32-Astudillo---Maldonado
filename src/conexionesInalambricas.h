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

      /////////////////////////Suscripcion a Topicos/////////////////////////////////////
      for(int i=0; i<tamanoModulos ; i++)
      {
        client.subscribe((topico_raiz+"/"+modulos[i]+"/#").c_str());
        Serial.println("Suscrito a:" + topico_raiz +"/"+modulos[i]+"/#");
      }
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