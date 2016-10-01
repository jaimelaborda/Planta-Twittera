#include <ESP8266WiFi.h>

const char* ssid = "MOVISTAR_5F22";
const char* password = "aCTuXmJGcNUjmtychhMX";

const char* host = "api.thingspeak.com"; // Your domain
const int httpPort = 80;
//String ApiKey = "THINGSPEAK_API_KEY";
String ApiKey = "C14V6R4XP363PR9A";
String path = "/update?key=" + ApiKey + "&field1=";

int ledPin = 13; // GPIO13
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  /*// Start the server
    server.begin();
    Serial.println("Server started"); NO NEED TO START A SERVER*/

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {

  //Analizamos el GPIO
  int estado_gpio = digitalRead(13);

  //Nos conectamos a un cliente
  WiFiClient client;
  if (!client.connect (host, httpPort)) {
    Serial.println("Conexion fallida");
    return;
  }

  client.print(String("GET ") + path + String(estado_gpio) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");


  Serial.println("Dato enviado correctamente: " + String(estado_gpio));
  Serial.println("Client disonnected");
  Serial.println("");
  delay(30000); //Esperamos 10 segundos
}

