#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NewPing.h>
#include "LocalConnectionInfo.h"

const int EchoPin= D5;
const int TriggerPin= D6;
const int MaxDistance = 200;
int distance = 0;
int volume = 0;

NewPing sonar(TriggerPin, EchoPin, MaxDistance);

void setup()
{
   Serial.begin(115200);
   delay(10);

   //Connect to WIFI
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
      delay(500);
}

void loop()
{
   HTTPClient http;
   WiFiClient client;

   distance = sonar.ping_cm();
   volume = -30 * distance + 5341; //These values correspond 

   url = url + "?water_volume=" + String(volume);
   url = url + "&tank_id=1";

   if (http.begin(client, url)) //Beginns connection
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();  // Sends the request

      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);

         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();   // Obtaining the response
            Serial.println(payload);   // Printing the response to the serial monitor
         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }

   delay(30000);
}
