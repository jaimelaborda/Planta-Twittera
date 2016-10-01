#include <ESP8266WiFi.h>

const char* ssid = "MOVISTAR_5F22";
const char* password = "aCTuXmJGcNUjmtychhMX";

const char* thingSpeakAddress = "api.thingspeak.com"; // Your domain
const int httpPort = 80;
//String ApiKey = "THINGSPEAK_API_KEY";
String thingtweetAPIKey = "CKYAIYFDPTBAOQHP";

int gpio_pin = 13; // GPIO13
WiFiServer server(80);

void UpdateTwitterStatus(String tsData)
{
  WiFiClient client;
  
  if (client.connect(thingSpeakAddress, httpPort))
  { 
    // Create HTTP POST Data ->Componemos en mensaje
    tsData = "api_key="+thingtweetAPIKey+"&status="+tsData;
            
    client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");

    client.print(tsData);
    
    
    if (client.connected())
    {
      Serial.println("Conectando a ThingSpeak...");
      Serial.println("El estado de Twitter ha sido actualizado!");
      Serial.println("Tweet: "+String(tsdata));
      Serial.println();
    }
    else
    {
  
      Serial.println("Conexión a ThingSpeak fallida");   
      Serial.println();
    }
    
  }
  else
  {
    Serial.println("Conexión a ThingSpeak fallida");   
    Serial.println();
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, INPUT);

  // Conectar a la red WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //Espera hasta que nos conectemos
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {

  //Analizamos el GPIO
  int estado_gpio = digitalRead(13);

  if(estado_gpio){ //Si el pin está a HIGH mansamos el tweet
    UpdateTwitterStatus("Twitteando desde ESP8266: El pin 13 está en HIGH!! @JaimeLaborda");
  }
  delay(30000); //Esperamos 10 segundos
}




