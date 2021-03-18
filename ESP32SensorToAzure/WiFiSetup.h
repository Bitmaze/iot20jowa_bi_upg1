void initWifi(char* ssid, char* pass) 
{
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi.");
  delay(100);
}
