bool checkForTempChange(float temp)
{
  if((temp - lastPostedTemp) >= tempThreshold || (temp - lastPostedTemp) <= -tempThreshold)
  {
    lastPostedTemp = temp;
    return true; 
  }
  return false;
}

bool checkForHumidityChange(float humidity)
{
 if((humidity - lastPostedHumidity) >= humidityThreshold || (humidity - lastPostedHumidity) <= -humidityThreshold)
  {
    lastPostedHumidity = humidity;
    return true; 
  }
  return false;
}
