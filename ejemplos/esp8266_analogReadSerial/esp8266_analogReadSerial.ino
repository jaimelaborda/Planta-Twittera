/* ************************************************* *
 * -------- ANALOG READ SERIAL EXAMPLE--- ---------- *
 * ----------- Jaime Laborda Macario --------------- *
 * ------------Taller Planta Twittera IoT----------- *
 *  https://github.com/jaimelaborda/Planta-Twittera  *
 * ************************************************* */


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115220);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
