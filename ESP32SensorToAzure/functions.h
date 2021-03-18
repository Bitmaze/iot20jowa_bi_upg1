void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
  (void)userContextCallback;
  Serial.println("ConfirmationCallback Called");
  if(result == IOTHUB_CLIENT_CONFIRMATION_OK) 
  {
    Serial.println("Callback OK");
    messagePending = false;
  }
}

void initIotDevice() 
{
device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(conn, protocol);
 if (device_ll_handle == NULL)
    {
      Serial.println("Failed to create device handle.");
    }
    else
    {
      Serial.println("Device handle created!");
     
     if (IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_TRUSTED_CERT, certificates) == IOTHUB_CLIENT_OK) //Verkade krävas i senaste versionen av IoTHub? Fick connectionproblem annars. 
     {
     Serial.println("Cert Set."); 
     }
     else
     {
     Serial.println("Cert Error.");
     }
    
    }

isConnectedToIotHub = true;
}

void initDht(){
  dht.begin();
}

void initSerial()
{
  Serial.begin(9600);  
}

void sendTheMessage(char *payload) {
  Serial.println("Sending Message...");
  int result = 0;
  IOTHUB_MESSAGE_HANDLE message = IoTHubMessage_CreateFromByteArray((const unsigned char *) payload, strlen(payload));
  (void)IoTHubMessage_SetProperty(message, "Name", "StudentJowa");
  (void)IoTHubMessage_SetProperty(message, "School", "Nackademin");
  result = IoTHubClient_LL_SendEventAsync(device_ll_handle, message, SendConfirmationCallback, NULL);
  messagePending = true;
  IoTHubMessage_Destroy(message);
}
