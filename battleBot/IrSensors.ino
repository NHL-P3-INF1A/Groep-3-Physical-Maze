// Variabel voor hoogste waarde
// Variabel voor laagste waarde

// Hytsteresis maken die de hoogste met laagste waarde gebruikt

// Dit per sensor doen

// void readIrOutput()
// {
//   for (int element : IrSensors)
//  {
//    Serial.print(analogRead(element));
//    Serial.print(" ");
//  }
//  Serial.println();
// }
void calibrateIrSensors(int time)
{

  int runtime = millis() + time;
  int count = 0;
  while(runtime > millis())
  {
    int base = 0;
    int i = 0;
    for (int element : IrSensors)
    {
      if(base == 0)
      {
        base = analogRead(element);
        continue;
      }

      int offset = base - analogRead(element);
      sensorOffsets[i] += offset;
      i++;
    }
    count++;
  }

  Serial.println(count);
  Serial.println();
  int i = 0;
  for (int element : sensorOffsets)
  {
    Serial.println(element);
    sensorOffsets[i] = element / count; 
    // Serial.println(sensorOffsets[i]);
    i++;
  }
}

void readIrOutput()
{

  // Loop door alle sensoren heen
    // Pak sensor 0 als "base"
    // pak het verschil tussen de base en elke andere sensor
      // sla dit op
  int i = 0;
  for (int element : IrSensors)
  {
    int value = analogRead(element); // + sensorOffsets[i];
    bool isDark = value > 650;
    // Serial.print(isDark);
    // Serial.print(":");
    // Serial.print(value);
    // Serial.print(" ");

    i++;
  }
  // Serial.println();
}