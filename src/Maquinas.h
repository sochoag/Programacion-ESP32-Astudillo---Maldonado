void activarMaquina(int maquina, bool estado)
{
    String mensaje = estado ? "Encendido" : "Apagado";
    //char topico[50];
    //snprintf(topico,50,"%s/%s/%d", topico_raiz.c_str(), modulos[2], maquina);
    String topico = topico_raiz + "/" + modulos[2] + "/" + String(maquina);
    Serial.println(topico);
    client.publish(topico.c_str(), mensaje.c_str());
}