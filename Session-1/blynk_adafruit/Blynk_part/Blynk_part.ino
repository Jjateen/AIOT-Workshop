#include <DHT.h>
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL5SV9vPoR"
#define BLYNK_DEVICE_NAME "first"
#define BLYNK_AUTH_TOKEN "DIe2X4x0kOrKFBmuegbzLNm7TQZhw8Zz"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define dtype DHT11
#define dpin 5
#define led 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "jjj";
char pass[] = "12345678";

DHT dht(dpin,dtype);
BlynkTimer timer;

BLYNK_WRITE(V0)
{
  int pinValue=param.asInt();
  digitalWrite(led,pinValue);
  }
void setup()
{
  pinMode(led,OUTPUT);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();
  int temp=dht.readTemperature();
  int hum=dht.readHumidity();
  Blynk.virtualWrite(V1,temp);
  Blynk.virtualWrite(V2,hum);
  Serial.print(temp); Serial.print("  :  "); Serial.println(hum);
}