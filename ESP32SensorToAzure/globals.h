#define DEVICE_ID "IotDevice1"
#define tempThreshold 1      //Hur många grader får avvika i temperatur innan vi skickar upp ny data.
#define humidityThreshold 5  //Hur många procent får avvika i luftfuktighet innan vi skickar upp ny data.
#define DHTPIN 32           

#define SEND_EVENT_RETRY_COUNT 5 //definar om/overridar den för mer retries, hade problem med att vissa meddelanden fick timeout
#define EVENT_TIMEOUT_MS 20000 //definar om/overridar så den fårlängre tid på sig. 

DHT dht(DHTPIN, DHT11);   //Create DHT objekt på pin 32

///Defines för dessa ligger i ignored.h som har .gitignore på sig. 
char* ssid = SECRET_WIFI_PASSWORD;
char* pass = SECRET_SSID;
char* conn = CONNECTION_STRING;

///
bool  isConnectedToIotHub = false;
float lastPostedTemp = -100.0;
float lastPostedHumidity = -100.0;
bool messagePending = false;
