float adquisicionDatos(int ledPower, int measurePin)
{
  digitalWrite(ledPower,LOW); 
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // Lectura de emision de Polvo

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // 
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;

  //Serial.print("Emision = ");
  //Serial.print(dustDensity);
  //Serial.println(" mg/m3 ");

  return dustDensity;
}