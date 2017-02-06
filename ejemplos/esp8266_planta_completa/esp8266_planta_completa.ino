/*Codigo Treefi*/

#include <ESP8266WiFi.h>
#include <SimpleDHT.h>

const char* ssid = "INSERTAR_SSID_WIFI";
const char* password = "CONTRASEÑA_WIFI";

const char* thingSpeakAddress = "api.thingspeak.com"; // Your domain
const int httpPort = 80;
String thingtweetAPIKey = "NM7RO7OSO6YQQONN";
String THINGSPEAK_API_KEY = "4HUUELKEO5H3NRGX";

int pinDHT11 = 2;

SimpleDHT11 dht11;

//VARIABLES DE LA PLANTA
byte temperature, relative_humidity;
float soil_humidity;

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
      Serial.println("Tweet: "+String(tsData));
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

void updateThingSpeak(String tsData) {
  WiFiClient client;
  if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + THINGSPEAK_API_KEY + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);

    if (client.connected()) {
      Serial.println("Dato enviado correctamente: "+ tsData);
      Serial.println();
    }
  }
}

void ActualizarVariables(){
  //Lectura de sensor DHT11
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  if (dht11.read(pinDHT11, &temperature, &relative_humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }

  long raw_lecture = 0;

  for (int i=0; i < 50; i++)
  {
    raw_lecture = raw_lecture + analogRead(A0);
    delay(20);
  }
  raw_lecture = raw_lecture/50; //hago una media
  
  soil_humidity = map(raw_lecture, 0, 500, 0, 100);
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)relative_humidity); Serial.println(" %");
  Serial.println("Soil: "+String(soil_humidity)+" %");
}

void setup() {
  Serial.begin(115200);
  delay(10);

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

  ActualizarVariables(); //Actualizo temperature, relative_humidity_soil humidity
  
  String tsData = "&field1="+String(temperature)+"&field2="+String(relative_humidity)+"&field3="+String(soil_humidity);
  updateThingSpeak(tsData);

  //Condiciones
  if (soil_humidity < 50) UpdateTwitterStatus("Treefi: ¡¡¡Necesito agua!!! :( @JaimeLaborda");
  if(temperature < 15) UpdateTwitterStatus("Treefi: ¡¡¡Tengo frío!!! :( @JaimeLaborda");

  delay(60000); //Esperamos 1 minuto
}




