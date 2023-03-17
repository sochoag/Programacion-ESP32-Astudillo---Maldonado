#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  // Tokening del topic
  int it=0;
  token = strtok(topic, "/");
  recepcion[it] = token;
  while(token != NULL)
  {
    it++;
    token = strtok(NULL, "/");
    recepcion[it] = token;
  }
  
  // Lectura del mensaje
  String mensaje;
  for (int i = 0; i < length; i++)
  {
    mensaje = mensaje + (char)payload[i];
  }

  switch (modulosEval(recepcion[1]))
  {
    case 0: fLimpieza(recepcion[2].toInt(), mensaje); break;
    case 1: fAlarma(mensaje); break;
    case 2: confirmacion(2, mensaje); break;
    case 4: confirmacion(4, mensaje); break;
    case 3: confirmacion(3, mensaje); break;
    case 5: confirmacion(5, mensaje); break;
    default: debugln("No command"); break;
  }
}

void setup_connections()
{
  // Coneccion con la red Wifi -- We start by connecting to a WiFi network
  debugln();
  debug("Connecting to ");
  debugln(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    debug(".");
  }

  randomSeed(micros());

  debugln("");
  debugln("WiFi connected");
  debugln("IP address: ");
  debugln(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect()
{
  // Ciclo repetitivo hasta que se coecte al MQTT -- Loop until we're reconnected
  while (!client.connected())
  {
    debug("Attempting MQTT connection...");
    // Creacion de ID Random -- Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Intento de Conexion -- Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      debugln("connected");

      /////////////////////////Suscripcion a Topicos/////////////////////////////////////
      for (int i = 0; i < tamanoModulos; i++)
      {
        client.subscribe((topico_raiz + "/" + modulos[i] + "/#").c_str());
        debugln("Suscrito a:" + topico_raiz + "/" + modulos[i] + "/#");
      }
    }
    else
    {
      debug("failed, rc=");
      debug(client.state());
      debugln(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      vTaskDelay(5000/portTICK_PERIOD_MS);
    }
  }
}