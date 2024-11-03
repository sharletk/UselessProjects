#include <Wire.h>
#include <DS3231.h>
#include <BMP280.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SK";
const char* password = "sharletk";

int LED_BUILTIN = 2;

#define IR_SENSOR_PIN 36
#define TRIG_US_SENSOR_PIN 32
#define ECHO_US_SENSOR_PIN 33
#define BUZZER_IO_PIN 25

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

void setRTCTime() {
  // Convert the system compile date and time to DateTime format
  DateTime now(
    atoi(__DATE__ + 7),              // Year
    getMonth(__DATE__),               // Month
    atoi(__DATE__ + 4),               // Day
    atoi(__TIME__),                   // Hour
    atoi(__TIME__ + 3),               // Minute
    atoi(__TIME__ + 6)                // Second
  );
  rtc.setEpoch(now.unixtime()); 
}

uint8_t getMonth(const char* monthStr) {
  if (strncmp(monthStr, "Jan", 3) == 0) return 1;
  if (strncmp(monthStr, "Feb", 3) == 0) return 2;
  if (strncmp(monthStr, "Mar", 3) == 0) return 3;
  if (strncmp(monthStr, "Apr", 3) == 0) return 4;
  if (strncmp(monthStr, "May", 3) == 0) return 5;
  if (strncmp(monthStr, "Jun", 3) == 0) return 6;
  if (strncmp(monthStr, "Jul", 3) == 0) return 7;
  if (strncmp(monthStr, "Aug", 3) == 0) return 8;
  if (strncmp(monthStr, "Sep", 3) == 0) return 9;
  if (strncmp(monthStr, "Oct", 3) == 0) return 10;
  if (strncmp(monthStr, "Nov", 3) == 0) return 11;
  if (strncmp(monthStr, "Dec", 3) == 0) return 12;
  return 0;
}

String formatTwoDigits(int value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}

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
  pinMode(BUZZER_IO_PIN, OUTPUT);
  Wire.begin(); 
  //bmp.begin();
  SPI.begin();
  initADXL345();
  setRTCTime();
  Serial.println("RTC time set to current system time.");

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

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  digitalWrite(BUZZER_IO_PIN, LOW);
  delay(1000);
  digitalWrite(BUZZER_IO_PIN, HIGH);
}

int readUltrasonicDistance() {
  digitalWrite(TRIG_US_SENSOR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_US_SENSOR_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_US_SENSOR_PIN, LOW);
  int duration = pulseIn(ECHO_US_SENSOR_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.println("Distance: " + String(distance) + " cm");
  return distance;
}

void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);
  int IR_SENSOR_OUT = analogRead(IR_SENSOR_PIN);
  // Serial.println(IR_SENSOR_OUT);
  int distance = readUltrasonicDistance();

  if (IR_SENSOR_OUT < 50) {
    Serial.println("Object Close");
    digitalWrite(BUZZER_IO_PIN, LOW);
    delay(2000);
    digitalWrite(BUZZER_IO_PIN, HIGH);
  }

  DateTime dt = RTClib::now();
  Serial.println(dt.second());

  // uint32_t pressure = bmp.getPressure();
  // Serial.println(pressure);

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

    String timeString = String(dt.year()) + "-" + 
                      formatTwoDigits(dt.month()) + "-" + 
                      formatTwoDigits(dt.day()) + "T" + 
                      formatTwoDigits(dt.hour()) + ":" + 
                      formatTwoDigits(dt.minute()) + ":" + 
                      formatTwoDigits(dt.second()) + "Z";


   // Create JSON object for transmission
     String jsonData = "{\"time\":\"" + timeString + "\",\"distance\":" + 
                      String(distance) + ",\"ir\":" + 
                      String(IR_SENSOR_OUT) + 
                      ",\"gyro\":{\"x\":" + String(x) + 
                      ",\"y\":" + String(y) + 
                      ",\"z\":" + String(z) + "}}";

    // Send data to Node.js server
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://192.168.137.1:3000/data"); // Change localhost to your server's IP if needed
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonData);
        if (httpResponseCode > 0) {
            String response = http.getString(); // Get the response
            Serial.println(response); // Print response
        } else {
            Serial.printf("Error on sending POST: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end(); // Close connection
    }

  delay(1000);
}