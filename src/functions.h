void fAlarma(String mensaje)
{
    debugln("Alarma - Mensaje recibido con exito!: " + mensaje);

    int i = 0;

    String recepcionAlarma[4];

    char *mensajeC = strdup(mensaje.c_str());
    char *tokenAlarma = strtok(mensajeC, "-");

    recepcionAlarma[i] = tokenAlarma;

    while (tokenAlarma != NULL)
    {
        i++;
        tokenAlarma = strtok(NULL, "-");
        recepcionAlarma[i] = tokenAlarma;
    }

    pinMode(pinesAlarma[recepcionAlarma[0].toInt()], OUTPUT);
    pinMode(pinesAlarma[recepcionAlarma[0].toInt() - 1], OUTPUT);
    pinMode(pinesAlarma[recepcionAlarma[0].toInt() + (tamanoPinesAlarma / 2) - 1], OUTPUT);

    if (recepcionAlarma[0].toInt() <= 2)
    {
        if (recepcionAlarma[1] == "ON")
        {
            digitalWrite(pinesAlarma[recepcionAlarma[0].toInt() - 1], HIGH);
        }
        else if (recepcionAlarma[1] == "OFF")
        {
            digitalWrite(pinesAlarma[recepcionAlarma[0].toInt() - 1], LOW);
        }
        else if (recepcionAlarma[1] == "DES")
        {
            digitalWrite(pinesAlarma[recepcionAlarma[0].toInt() - 1], LOW);
        }
    }
    else
    {
        debugln("Comando desconocido 2");
    }
}

void fAlerta(int alerta, String value)
{
    String mensaje = value;
    String topico = topico_raiz + "/Alerta/" + String(alerta);
    client.publish(topico.c_str(), mensaje.c_str());
    doc["Alerta"][alerta-1] = value;
    enviarDatos();
}

void fLimpieza(int elemento, String mensaje)
{
    debugln("Limpieza - Mensaje recibido con exito!: " + (String)elemento + " " + mensaje);
    if (elemento<=tamanoPinesLimpieza)
    {
        pinMode(pinesLimpieza[elemento - 1], OUTPUT);
        if (mensaje == "Encendido")
        {
            digitalWrite(pinesLimpieza[elemento - 1], HIGH);
        }
        else if (mensaje == "Apagado")
        {
            digitalWrite(pinesLimpieza[elemento - 1], LOW);
        }
        else
        {
            debugln("Comando desconocido");
            return;
        }
        doc["Limpieza"][elemento-1] = mensaje == "Encendido" ? true : false;
        enviarDatos();
    }
}

void fExtractor(int maquina, int pin)
{   
    String mensaje = digitalRead(pin) ? "Encendido" : "Apagado";
    String topico = topico_raiz + "/Extractor/" + String(maquina);
    client.publish(topico.c_str(), mensaje.c_str());
    topico = topico_raiz + "/Limpieza/" + String(maquina);
    client.publish(topico.c_str(), mensaje.c_str());
}

void fMaquina(int maquina, int pin)
{   
    String mensaje = digitalRead(pin) ? "Encendido" : "Apagado";
    String topico = topico_raiz + "/Maquina/" + String(maquina);
    client.publish(topico.c_str(), mensaje.c_str());
    doc["Maquina"][maquina-1] = mensaje == "Encendido" ? true : false;
    enviarDatos();
}

void fSensor(int sensor, float vsensor)
{
    //String mensaje = estado ? "Encendido" : "Apagado";
    // char topico[50];
    //snprintf(topico,50,"%s/%s/%d", topico_raiz.c_str(), modulos[2], maquina);
    String mensaje = String(vsensor,0);
    // mensaje.replace(".",",");
    String topico = topico_raiz + "/Sensor/" + String(sensor);
    client.publish(topico.c_str(), mensaje.c_str());
    doc["Sensor"][sensor-1] = mensaje;
}

int modulosEval(String modulo)
{
    if (modulo == "Limpieza") return 0;
    if (modulo == "Alarma") return 1;
    if (modulo == "Maquina") return 2;
    if (modulo == "Sensor") return 3;
    if (modulo == "Alerta") return 4;
    if (modulo == "Extractor") return 5;
    return 999;
}

void confirmacion(int i, String mensaje)
{
    debugln("Mensaje enviado con exito!: "+modulos[i]+" -> "+ mensaje);
}

float adquisicionDatos(int ledPower, int measurePin)
{
    digitalWrite(ledPower, LOW);
    delayMicroseconds(samplingTime);

    voMeasured = analogRead(measurePin); // Lectura de emision de Polvo

    delayMicroseconds(deltaTime);
    digitalWrite(ledPower, HIGH); //
    delayMicroseconds(sleepTime);

    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    calcVoltage = voMeasured * (5.0 / 1024.0);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    dustDensity = 170 * calcVoltage - 0.1;

    //debug("Emision = ");
    //debug(dustDensity);
    //debugln(" mg/m3 ");

    return dustDensity;
}