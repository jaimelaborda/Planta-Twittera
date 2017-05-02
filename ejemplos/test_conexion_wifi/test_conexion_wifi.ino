/* ************************************************* *
 * -------- EJEMPLO TEST CONEXIÓN WIFI ESP---------- *
 * ----------- Jaime Laborda Macario --------------- *
 * ------------Taller Planta Twittera IoT----------- *
 *  https://github.com/jaimelaborda/Planta-Twittera  *
 * ************************************************* */


#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("ssid", "password");  
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
