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

void confirmacion(int i)
{
    Serial.println("Mensaje enviado con exito!: "+modulos[i]);
}