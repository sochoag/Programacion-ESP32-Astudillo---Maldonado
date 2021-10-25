void initAlarma()
{
  for(int i = 0; i < tamanoPinesAlarma; i++)
  {
    pinMode(pinesAlarma[i],OUTPUT);
  }
}

void fAlarma(String mensaje)
{
  int i=0;
  Serial.println(mensaje);

  String recepcionAlarma[4];
  char* mensajeC = strdup(mensaje.c_str());
  char*tokenAlarma = strtok(mensajeC, "-");
  recepcionAlarma[i] = tokenAlarma;
  while(tokenAlarma != NULL)
  {
    i++;
    tokenAlarma = strtok(NULL, "-");
    recepcionAlarma[i] = tokenAlarma;
  }
  if(recepcionAlarma[0].toInt() && recepcionAlarma[0].toInt()>0 && recepcionAlarma[0].toInt()<=tamanoPinesAlarma/2)
  {
    if (recepcionAlarma[1]=="ON")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1],HIGH);
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1],LOW);
        Serial.println("Pin: "+String(pinesAlarma[recepcionAlarma[0].toInt()-1])+":HIGH");
        Serial.println("Pin: "+String(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1])+":LOW");
    }
    else if (recepcionAlarma[1]=="OFF")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1], LOW);
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1], HIGH);
        Serial.println("Pin: "+String(pinesAlarma[recepcionAlarma[0].toInt()-1])+":LOW");
        Serial.println("Pin: "+String(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1])+":HIGH");
    }
    else if (recepcionAlarma[1]=="DES")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1],LOW);
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1],LOW);
        Serial.println("Pin: "+String(pinesAlarma[recepcionAlarma[0].toInt()-1])+":LOW");
        Serial.println("Pin: "+String(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1])+":LOW");
    }
    else
    {
      Serial.println("Comando desconocido");
    }
  }
  else
  {
    Serial.println("Comando desconocido");
  }
}