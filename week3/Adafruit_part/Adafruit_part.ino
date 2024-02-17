#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define Switch1 4
#define Switch2 5

#define WLAN_SSID  "Internet"
#define WLAN_PASS  "internet"

// defining neccessary information to connect to adafruit.com 

#define Server       "io.adafruit.com"                          // website url
#define SeverPort    1883                                       
#define UserName    "Nirbhaysora"                              // username to connect to my own dashboard
#define KEY         "aio_xuGB869hIjkp4IYFx5pqVbwRpAdw"         // unique key to connect to a perticular dashboard

/************ Global State (you don't need to change this!) ******************/

// Create an ESP32 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, Server, SeverPort, UserName, KEY) ;

/****************************** Feeds ***************************************/

Adafruit_MQTT_Subscribe device1 = Adafruit_MQTT_Subscribe(&mqtt, UserName"/feeds/device-1") ;
Adafruit_MQTT_Subscribe device2 = Adafruit_MQTT_Subscribe(&mqtt, UserName "/feeds/device-2") ;

void MQTT_connect();

void setup() {
  Serial.begin(115200);
 
  pinMode(Switch1, OUTPUT);
  pinMode(Switch2, OUTPUT);
 
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&device1);
  mqtt.subscribe(&device2);
}

void loop() {
 
  MQTT_connect();
 

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) 
  {
    if (subscription == &device1) 
    {
      Serial.print(F("Got: "));
      Serial.println((char *)device1.lastread);

      int device1_State = atoi((char *)device1.lastread);
      digitalWrite(Switch1, device1_State);
     
    }

    if (subscription == &device2) 
    {
      Serial.print(F("Got: "));
      Serial.println((char *)device2.lastread);

      int device2_State = atoi((char *)device2.lastread);
      digitalWrite(Switch2, device2_State);
    }
  }
}
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

