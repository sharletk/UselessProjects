int LED_BUILTIN = 2;

#define IR_SENSOR_PIN 36

void setup() {
  // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello from ESP32!");
}

void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);
  int IR_SENSOR_OUT = analogRead(IR_SENSOR_PIN);
  // Serial.println(IR_SENSOR_OUT);

  if (IR_SENSOR_OUT < 50) {
    Serial.println("Object Close");
  }

  delay(500);
}