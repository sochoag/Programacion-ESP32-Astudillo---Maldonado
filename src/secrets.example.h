#include <Arduino.h>

#ifndef secrets

#define secrets
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
const char* mqtt_server = "<MQTT HOST>";

String topico_raiz = "<MAIN TOPIC>";
const String modulos[] = {"<MODULE>","<MODULE>","<MODULE>","<MODULE>","<MODULE>"};
const byte tamanoModulos = sizeof(modulos) / sizeof(modulos[0]);
#endif
