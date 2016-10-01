/* ************************************************* *
 * -------- EJEMPLO BRILLO LED THINGSPEAK ---------- *
 * ----------- Jaime Laborda Macario --------------- *
 * ------------Taller Planta Twittera IoT----------- *
 *  https://github.com/jaimelaborda/Planta-Twittera  *
 * ************************************************* */

#include <ESP8266WiFi.h>

const char* ssid = "MOVISTAR_5F22";
const char* password = "aCTuXmJGcNUjmtychhMX";

const char* thingSpeakAddress = "api.thingspeak.com"; // Dirección del cliente
const int httpPort = 80; //Puerto de comunicación
//String ApiKey = "THINGSPEAK_API_KEY";
String APIKey = "6MEB86QN4VHCZAD5";

int ledPin = 13; // GPIO13
WiFiServer server(80);

int lectura_analogica, brillo_led;

void updateThingSpeak(String tsData) {
  WiFiClient client;
  if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + APIKey + "\n");
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

void setup() {
  Serial.begin(115200);
  delay(10);

  //Configuramos el GPIO
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
}

void loop() {
  //Leemos el valor del potenciomentro
  lectura_analogica = analogRead(0);

  brillo_led = map(lectura_analogica, 0, 1023, 0, 255);

  analogWrite(13, brillo_led);

  updateThingSpeak(String("field1=") + String(brillo_led));

  delay(5000);
}

