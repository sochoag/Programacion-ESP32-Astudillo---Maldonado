
//////MODULO ALARMA 1///////
void ModuloAlarm1(String mensaje)
{
  Serial.println(mensaje);
  if (mensaje == "Amarillo1ONRojo1OFF")
  {
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    Serial.println("Rojo ON");
  }
  else if (mensaje == "Amarillo1OFFRojo1ON")
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Serial.println("Alarma Apagada");
  }
  else if (mensaje == "Amarillo1OFFRojo1OFF")
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
   Serial.println("Amarillo ON");
  }
}
/*
//////MODULO ALARMA 2///////
void ModuloAlarm2(String mensaje)
{
  Serial.println(mensaje);
  if (mensaje == "Amarillo2ONRojo2OFF")
  {
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    Serial.println("Rojo ON");
  }
  else if (mensaje == "Amarillo2OFFRojo2ON")
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Serial.println("Alarma Apagada");
  }
  else if (mensaje == "Amarillo2OFFRojo2OFF")
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
   Serial.println("Amarillo ON");
  }
}
*/
/*
//////MODULO ALARMA 3///////
void ModuloAlarm3(String mensaje)
{
  Serial.println(mensaje);
  if (mensaje == "Amarillo3ONRojo3OFF")
  {
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    Serial.println("Rojo ON");
  }
  else if (mensaje == "Amarillo3OFFRojo3ON")
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Serial.println("Alarma Apagada");
  }
  else if (mensaje == "Amarillo3OFFRojo3OFF")
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
   Serial.println("Amarillo ON");
  }
}
*/
/*
//////MODULO ALARMA 4///////
void ModuloAlarm4(String mensaje)
{
  Serial.println(mensaje);
  if (mensaje == "Amarillo4ONRojo4OFF")
  {
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    Serial.println("Rojo ON");
  }
  else if (mensaje == "Amarillo4OFFRojo4ON")
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Serial.println("Alarma Apagada");
  }
  else if (mensaje == "Amarillo4OFFRojo4OFF")
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
   Serial.println("Amarillo ON");
  }
}
*/
/*
//////MODULO ALARMA 5///////
void ModuloAlarm5(String mensaje)
{
  Serial.println(mensaje);
  if (mensaje == "Amarillo5ONRojo5OFF")
  {
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    Serial.println("Rojo ON");
  }
  else if (mensaje == "Amarillo5OFFRojo5ON")
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Serial.println("Alarma Apagada");
  }
  else if (mensaje == "Amarillo5OFFRojo5OFF")
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
   Serial.println("Amarillo ON");
  }
}
*/
