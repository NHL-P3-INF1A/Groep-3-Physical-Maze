void readIrOutput()
{
  for (int sensorPin : IR_SENSORS)
  {
    Serial.print(analogRead(sensorPin));
    Serial.print(" ");
  }
  Serial.print(" 800");
  Serial.println();
}

void getIrColors()
{
    int i = 0;
    for (int sensorPin : IR_SENSORS)
    {
      int value = analogRead(sensorPin);
      if (value > sensorTresholds[i][1])
      {
        sensorColor[i] = false;

      }
      else if (value < sensorTresholds[i][0])
      {
        sensorColor[i] = true;
      }

      if(sensorColor[i])
      {
        Serial.print("White");  
      }
      else
      {
        Serial.print("Black");          
      }
      i++;
      Serial.print(" ");
    }
    Serial.println();
}

void setIrThresholds(int time)
{
  // Lijst structuur voor thresholds opslaan [[200, 300], [100, 293]] : [[whiteThreshold, blackThreshold], ...]
  
  // Zet witte tresholds
  int runtime = millis() + time;
  Serial.println("Detecting white");
  while (runtime > millis())
  {
    updateThreshold(0);
  }

  // Wacht op hogere waarden
  while (true)
  {
    int i = 0;
    bool detectedWhite = false;
    for (int sensorPin : IR_SENSORS)
    {
      if (sensorTresholds[i][0] + 200 > analogRead(sensorPin))
      {
        detectedWhite = true;
        break;
      }  
      i++;
    }
    if(!detectedWhite)
    {
      break;  
    }
  }
 
  // Zet zwarte tresholds
  runtime = millis() + time;
  Serial.println("Detecting black");
  while (runtime > millis())
  {
    updateThreshold(1);
  }
}

void updateThreshold(int index)
{
    int i = 0;
    for (int sensorPin : IR_SENSORS)
    {
      int value = analogRead(sensorPin);
      if(value > sensorTresholds[i][index])
      {
        sensorTresholds[i][index] = value;
      }
      i++;
    }
}
