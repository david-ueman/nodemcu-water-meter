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
   Serial.println("Connecting...");
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
     {
     delay(500);
     Serial.print(".");
     }
    
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
   HTTPClient http;
   WiFiClient client;
   String url;

   distance = sonar.ping_cm();
   volume = -30 * distance + 5341; //These values correspond 

   url = storage_routines_url +  "?water_volume=" + String(volume);
   url = url + "&tank_id=1";

   /*****/
   if (WiFi.status() != WL_CONNECTED)   // If connection is lost, re-connect!
     {
     Serial.println("Connection lost... Re-connecting...");
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED)
       {
       delay(500);
       Serial.print(".");
       }
    Serial.println("");
    Serial.print("Re-connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    }
    /*****/

    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = url;
      Serial.println(serverPath);
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath);
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi is not connected");
    }

   //wait 5 minutes until next reading...
   delay(300000);
}
