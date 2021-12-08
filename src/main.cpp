#include <Arduino.h>
#include "secrets.h"
#include "variables.h"
#include "functionsHeader.h"
#include "conexionesInalambricas.h"
#include "functions.h"

void WatchdogConexiones(void *nada);
void MaquinaPolling(void *nada);
void SensoresPublish(void *nada);
void AlertaTask(void *nada);
void ExtractorTask(void *parameters);

void setup()
{
    Serial.begin(115200);
    setup_connections();
    reconnect();
    xTaskCreate(WatchdogConexiones, "MQTT_Task", 10240, NULL, 4, NULL);
    xTaskCreate(SensoresPublish, "SensoresPublish", 10240, NULL, 2, NULL);
    xTaskCreate(MaquinaPolling, "Maquina_Polling", 10240, NULL, 1, NULL);
    xTaskCreate(AlertaTask, "Task Alerta", 10240, NULL, 2, NULL);
    xTaskCreate(ExtractorTask, "Task Extractor", 10240, NULL, 2, NULL);
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
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void AlertaTask(void *nada)
{
    bool lastValues[] = {false, false};
    bool values[] = {true, true};

    for (int i = 0; i < tamanoPinesMaquina; i++)
    {
        pinMode(pinesAlerta[i], INPUT);
    }

    while (true)
    {
        for (int i = 0; i < tamanoPinesAlerta; i++)
        {
            values[i] = digitalRead(pinesAlerta[i]);
            if (lastValues[i] != values[i])
            {
                fAlerta(i + 1, pinesAlerta[i]);
            }
            lastValues[i] = values[i];
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