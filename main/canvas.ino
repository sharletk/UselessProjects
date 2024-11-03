// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET    -1 // Reset pin not used (can be -1)

// // Initialize the OLED display object
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// void setup() {
//   Serial.begin(115200);
  
//   // Initialize the OLED display
//   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is a common I2C address for these displays
//     Serial.println(F("SSD1306 allocation failed"));
//     for (;;); // Stop if display allocation failed
//   }

//   display.clearDisplay(); // Clear buffer
  
//   // Set text properties
//   display.setTextSize(1);      // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE); // Draw white text
  
//   // Draw text on the display
//   // display.setCursor(0, 0);     // Start at top-left corner
//   // display.println(F("Hello from ESP32!"));
  
//   // display.setCursor(0, 16);
//   // display.println(F("Displaying text on"));
  
//   // display.setCursor(0, 32);
//   // display.println(F("1.3-inch OLED screen"));
  
//   // display.setCursor(0, 48);
//   // display.println(F("Using I2C interface"));

//   display.display();            // Show the text on the screen
// }

// void loop() {
//   // Nothing to loop for this basic display example
// }
