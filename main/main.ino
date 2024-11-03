#include <Wire.h>
#include <DS3231.h>
#include <BMP280.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int LED_BUILTIN = 2;

#define IR_SENSOR_PIN 36
#define TRIG_US_SENSOR_PIN 25
#define ECHO_US_SENSOR_PIN 26

DS3231 rtc;
// BMP280 bmp;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define ADXL345_CS_PIN 5
#define ADXL345_SPI_CLOCK 500000

// ADXL345 Register Addresses
#define POWER_CTL 0x2D
#define DATA_FORMAT 0x31
#define DATAX0 0x32
#define DATAY0 0x34
#define DATAZ0 0x36

void initADXL345() {
  pinMode(ADXL345_CS_PIN, OUTPUT);
  digitalWrite(ADXL345_CS_PIN, HIGH);

  // Set ADXL345 to measurement mode
  writeRegister(POWER_CTL, 0x08);

  // Set data format to full resolution and 16g range
  writeRegister(DATA_FORMAT, 0x0B);
}

void writeRegister(uint8_t reg, uint8_t value) {
  // Pull CS low to start SPI transaction
  digitalWrite(ADXL345_CS_PIN, LOW);
  SPI.beginTransaction(SPISettings(ADXL345_SPI_CLOCK, MSBFIRST, SPI_MODE3));
  
  // Send register address with the write flag (clear MSB to write)
  SPI.transfer(reg & 0x3F);

  // Write the value
  SPI.transfer(value);

  // End the SPI transaction
  SPI.endTransaction();
  digitalWrite(ADXL345_CS_PIN, HIGH);
}

uint16_t read16(uint8_t reg) {
  digitalWrite(ADXL345_CS_PIN, LOW);
  SPI.beginTransaction(SPISettings(ADXL345_SPI_CLOCK, MSBFIRST, SPI_MODE3));

  // Send register address with the read flag (set MSB to read)
  SPI.transfer(reg | 0x80);  
  uint8_t low = SPI.transfer(0x00);
  uint8_t high = SPI.transfer(0x00);

  SPI.endTransaction();
  digitalWrite(ADXL345_CS_PIN, HIGH);

  int16_t value = (high << 8) | low;
  if (value > 32767) value -= 65536; // Two's complement for signed values
  return value;
}

void readAccelerometer(int16_t &x, int16_t &y, int16_t &z) {
  x = read16(DATAX0);
  y = read16(DATAY0);
  z = read16(DATAZ0);
}

void setup() {
  // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello from ESP32!");
  pinMode(TRIG_US_SENSOR_PIN, OUTPUT);
  pinMode(ECHO_US_SENSOR_PIN, INPUT);
  Wire.begin(); 
  //bmp.begin();
  SPI.begin();
  initADXL345();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Replace 0x3C with your display's address
        Serial.println("Couldn't find SSD1306");
        while (1);
  }

  display.clearDisplay();
  display.setTextSize(1); // Set text size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Hello, World!"); // Test static text
  display.display();
}

void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);
  int IR_SENSOR_OUT = analogRead(IR_SENSOR_PIN);
  // Serial.println(IR_SENSOR_OUT);

  if (IR_SENSOR_OUT < 50) {
    Serial.println("Object Close");
  }

  DateTime dt = RTClib::now();
  Serial.println(dt.second());

  // uint32_t pressure = bmp.getPressure();
  // Serial.println(pressure);

  digitalWrite(TRIG_US_SENSOR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_US_SENSOR_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_US_SENSOR_PIN, LOW);
  int duration = pulseIn(ECHO_US_SENSOR_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.println("Distance: " + String(distance) + " cm");

  int16_t x, y, z;

  // Read accelerometer values
  readAccelerometer(x, y, z);

  // Print values
  Serial.print("X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  Serial.print(" | Z: "); Serial.println(z);

  // display.clearDisplay();
  // display.setCursor(0, 0);
  // display.print("Time: ");
  // display.print(dt.second());
  // display.display();

  delay(1000);
}