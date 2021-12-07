void fAlarma(String mensaje)
{
  Serial.println("Alarma - Mensaje recibido con exito!: "+mensaje);

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
  pinMode(pinesAlarma[recepcionAlarma[0].toInt()+(tamanoPinesAlarma/2)-1],OUTPUT);
  

  if(recepcionAlarma[0].toInt()<=2)
  {
    if (recepcionAlarma[1]=="ON")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1],HIGH);
    }
    else if (recepcionAlarma[1]=="OFF")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1], LOW);
    }
    else if (recepcionAlarma[1]=="DES")
    {
        digitalWrite(pinesAlarma[recepcionAlarma[0].toInt()-1],LOW);
    }
  }
  else
  {
    Serial.println("Comando desconocido 2");
  }
}