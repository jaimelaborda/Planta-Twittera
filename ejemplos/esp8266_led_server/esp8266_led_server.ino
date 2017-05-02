/* ************************************************* *
 * -------- EJEMPLO SERVIDOR LED THINGSPEAK ---------- *
 * ----------- Jaime Laborda Macario --------------- *
 * ------------Taller Planta Twittera IoT----------- *
 *  https://github.com/jaimelaborda/Planta-Twittera  *
 * ************************************************* */

#include <ESP8266WiFi.h> //Incluimos la librería para del WiFi
 
//Credenciales del WiFi
const char* ssid = "INSERTAR WIFI_SSID";
const char* password = "INSERTAR PASSWORD";
 
int ledPin = D0; // D0 is the LEDBUILDIN (Active LOW)
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200); //Inicio el puerto serie 
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Conecto con la red WiFi en modo estación (STA)
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
 
  // Inicializo el servidor
  server.begin();
  Serial.println("Servidor iniciado");
 
  // Muestro la IP local asignada. URL del servidor
  Serial.print("Usa esta URL para conectar al servidor: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Compruebo si hay un cliente disponible (una petición)
  WiFiClient client = server.available();
  if (!client) {
    return; // En caso de no haber un cliente, no hago nada
  }
 
  // Espero hasta que el cliente realice una petición
  Serial.println("¡Nuevo cliente!");
  while(!client.available()){
    delay(1);
  }
 
  // Leo la primera linea de la petición del cliente
  String request = client.readStringUntil('\r'); // Leo hasta retorno de carro
  Serial.println(request); //Imprimo la petición
  client.flush(); //Limpio el buffer
 
  // Interpreto lo que he recibido
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Pongo ledPin al valor que ha solicitado el cliente en la petición
 
  // Devuelvo la respuesta al cliente -> Todo ha ido bien, el mensaje ha sido interpretado correctamente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  
  // A partir de aquí creo la página en raw HTML
  client.println("<!DOCTYPE HTML>"); 
  client.println("<html>");
 
  client.print("El LED esta:  ");
 
  if(value == HIGH) {
    client.print("ON");
  } else {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Encender </button></a>"); // Los botones con enlace
  client.println("<a href=\"/LED=OFF\"\"><button>Apagar </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Cliente desconectado"); // Nos desconectamos del cliente
  Serial.println("");
 
}
 
