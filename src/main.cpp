#include <Arduino.h>

#define DEBUGLEVEL 1

#if DEBUGLEVEL == 1 
    #define debugln(x)
    #define debug(x) 
#elif DEBUGLEVEL == 0
    #define debugln(x) Serial.println(x)
    #define debug(x) Serial.print(x)
#endif

QueueHandle_t queue;
BaseType_t xStatus;

#include "secrets.h"
#include "variables.h"
#include "display.h"
#include "functionsHeader.h"
#include "conexionesInalambricas.h"
#include "functions.h"


void WatchdogConexiones(void *nada);
void MaquinaPolling(void *nada);
void SensoresPublish(void *nada);
void AlertaTask(void *nada);
void ExtractorTask(void *parameters);
void SenderTask(void *parameters);

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    queue = xQueueCreate(10, sizeof(char[300]));
    if(queue == NULL){
        debugln("Error creando el queue");
    }
    initValues();
    setup_connections();
    reconnect();
    xTaskCreate(WatchdogConexiones, "MQTT_Task", 10240, NULL, 3, NULL);
    xTaskCreate(SensoresPublish, "SensoresPublish", 10240, NULL, 2, NULL);
    xTaskCreate(MaquinaPolling, "Maquina_Polling", 10240, NULL,2, NULL);
    xTaskCreate(AlertaTask, "Task Alerta", 10240, NULL, 2, NULL);
    xTaskCreate(ExtractorTask, "Task Extractor", 10240, NULL, 2, NULL);
    xTaskCreate(SenderTask, "Sender Task", 10240, NULL, 1, NULL);
}

void loop()
{
}

void WatchdogConexiones(void *nada)
{
    while (true)
    {
        if (!client.connected())
        {
            reconnect();
        }
        client.loop();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void MaquinaPolling(void *nada)
{
    bool lastValues[] = {false, false};
    bool values[] = {true, true};

    for (int i = 0; i < tamanoPinesMaquina; i++)
    {
        pinMode(pinesMaquina[i], INPUT);
    }

    while (true)
    {
        for (int i = 0; i < tamanoPinesMaquina; i++)
        {
            values[i] = digitalRead(pinesMaquina[i]);
            if (lastValues[i] != values[i])
            {
                fMaquina(i + 1, pinesMaquina[i]);
            }

            lastValues[i] = values[i];
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void SensoresPublish(void *nada)
{
    for (int i = 0; i < tamanoPinesSensor; i++)
    {
        pinMode(digitalPinsSensor[i], OUTPUT);
        pinMode(analogPinsSensor[i], INPUT);
    }

    while (true)
    {
        for (int i = 0; i < tamanoPinesSensor; i++)
        {
            float valor = adquisicionDatos(digitalPinsSensor[i], analogPinsSensor[i]);
            fSensor(i + 1, valor);
        }
        enviarDatos();
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void AlertaTask(void *nada)
{
    int conts[2] = {0,0};
    String values[2] = {"V","V"};

    for (int i = 0; i < tamanoPinesMaquina; i++)
    {
        pinMode(pinesAlerta[i], INPUT);
    }

    while (true)
    {
        for (int i = 0; i < tamanoPinesAlerta; i++)
        {
            if (digitalRead(pinesAlerta[i]))
            {
                vTaskDelay(250 / portTICK_PERIOD_MS);
                switch (conts[i])
                {
                    case 0: values[i] = "V"; conts[i]++; break;
                    case 1: values[i] = "A"; conts[i]++; break;
                    case 2: values[i] = "R"; conts[i] = 0; break;
                    default: break;
                }
                fAlerta(i + 1, values[i]);
            }
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void ExtractorTask(void *parameters)
{
    bool lastValues[] = {false, false};
    bool values[] = {true, true};

    for (int i = 0; i < tamanoPinesExtractor; i++)
    {
        pinMode(pinesExtractor[i], INPUT);
    }

    while (true)
    {
        for (int i = 0; i < tamanoPinesExtractor; i++)
        {
            values[i] = digitalRead(pinesExtractor[i]);
            if (lastValues[i] != values[i])
            {
                fExtractor(i + 1, pinesExtractor[i]);
            }

            lastValues[i] = values[i];
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void SenderTask(void *parameters)
{
    while (true)
    {
        char elemento[300];
        xStatus = xQueueReceive(queue, &elemento, portMAX_DELAY);
        if(xStatus != errQUEUE_EMPTY)
        {
            Serial.println("Enviando desde Queue");
            Serial.println(elemento);
            Serial2.println(elemento);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}