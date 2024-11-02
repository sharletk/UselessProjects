#include <Wire.h>
#include <DS3231.h>
#include <BMP280.h>

int LED_BUILTIN = 2;

#define IR_SENSOR_PIN 36
#define TRIG_US_SENSOR_PIN 25
#define ECHO_US_SENSOR_PIN 26

DS3231 rtc;
BMP280 bmp;

void setup() {
  // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello from ESP32!");
  pinMode(TRIG_US_SENSOR_PIN, OUTPUT);
  pinMode(ECHO_US_SENSOR_PIN, INPUT);
  Wire.begin(); 
  //bmp.begin();
}

void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);
  int IR_SENSOR_OUT = analogRead(IR_SENSOR_PIN);
  // Serial.println(IR_SENSOR_OUT);

  if (IR_SENSOR_OUT < 50) {
    Serial.println("Object Close");
  }

  DateTime dt = RTClib::now();
  // Serial.println(dt.second());

  // uint32_t pressure = bmp.getPressure();
  // Serial.println(pressure);

  digitalWrite(TRIG_US_SENSOR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_US_SENSOR_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_US_SENSOR_PIN, LOW);
  int duration = pulseIn(ECHO_US_SENSOR_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.println(duration);
  Serial.println("Distance: " + String(distance) + " cm");

  delay(500);
}