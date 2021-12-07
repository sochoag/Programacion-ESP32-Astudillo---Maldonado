void fAlarma(String mensaje)
{
  int i=0;

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
  
  pinMode(pinesAlarma[recepcionAlarma[0].toInt()],OUTPUT);
  pinMode(pinesAlarma[recepcionAlarma[0].toInt()-1],OUTPUT);
  
  if(recepcionAlarma[0].toInt() && recepcionAlarma[0].toInt()>0 && recepcionAlarma[0].toInt()<=tamanoPinesAlarma/2)
  {
    pinMode(pinesAlarma[recepcionAlarma[0].toInt()-1],OUTPUT);
    pinMode(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1],OUTPUT);
    if (recepcionAlarma[1]=="ON")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1],HIGH);
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1],LOW);
    }
    else if (recepcionAlarma[1]=="OFF")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1], LOW);
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1], HIGH);
    }
    else if (recepcionAlarma[1]=="DES")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1],LOW);
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1],LOW);
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