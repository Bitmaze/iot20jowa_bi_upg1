//
//ESP32 användes för uppgiften. 
// 

#include <SPI.h>
#include <DHT.h>
#include <WiFi.h>

#include <AzureIoTHub.h>            //Version 1.5.0
#include <AzureIoTUtility.h>        //Version 1.5.0
#include <AzureIoTProtocol_MQTT.h>  //Version 1.5.0
#include "iothubtransportmqtt.h"    

#include <ArduinoJson.h>            //Version 6.17.3

IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;
IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;

#include "ignored.h" //Git ignore på löserord och connectionstring. 
#include "globals.h"
#include "WiFiSetup.h"
#include "sensorVarianceFunctions.h"
#include "functions.h"
#include "time.h"

void setup() 
{
  initSerial();
  initWifi(ssid, pass);
  initDht();
  (void)IoTHub_Init();
  configTime(3600, 0, "pool.ntp.org", "time.nist.gov"); //TimeServer
  delay(2000); 
  initIotDevice();
}

void loop() 
{
   float newTempReading = dht.readTemperature();
   float newHumidityReading = dht.readHumidity();
   int newLightReading = analogRead(33);
   if((checkForTempChange(newTempReading) || checkForHumidityChange(newHumidityReading)) && isConnectedToIotHub)
   {
     if(!messagePending) 
     {
        messagePending = true;
        char payload[256];

        DynamicJsonDocument doc(sizeof(payload));
        doc["dId"] = DEVICE_ID;
        doc["tmp"] = newTempReading;
        doc["hum"] = newHumidityReading;
        doc["light"] = newLightReading;
        doc["lts"] = time(NULL);     // lts, local time stamp tänkte jag. 
        serializeJson(doc,payload);
        Serial.println(payload);
        sendTheMessage(payload);
        IoTHubDeviceClient_LL_DoWork(device_ll_handle);
      }
   }
   IoTHubDeviceClient_LL_DoWork(device_ll_handle); 
   

   delay(5000);  //Delay så att ifall det sker snabba tempskillnader så spammar den inte in ny data för ofta. 
   
}
