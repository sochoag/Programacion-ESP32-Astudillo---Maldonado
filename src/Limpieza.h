void initLimpieza()
{
  for(int i = 0; i < tamanoPinesLimpieza; i++)
  {
    pinMode(pinesLimpieza[i],OUTPUT);
  }
}

void fLimpieza(int elemento, String mensaje)
{
  if (mensaje == "Encendido")
  {
    digitalWrite(pinesLimpieza[elemento-1], HIGH);
  }
  else if (mensaje == "Apagado")
  {
    digitalWrite(pinesLimpieza[elemento-1], LOW);
  }
  else
  {
    Serial.println("Comando desconocido");
    return;
  }
  Serial.println("LED "+ String(pinesLimpieza[elemento-1]) +" "+ mensaje);
}
