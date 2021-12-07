void fLimpieza(int elemento, String mensaje)
{
  pinMode(pinesLimpieza[elemento-1], OUTPUT);
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
}
