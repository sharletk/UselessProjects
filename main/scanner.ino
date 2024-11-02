// #include <Wire.h>

// void setup() {
//   Wire.begin();           // Initialize I²C communication
//   Serial.begin(115200);   // Start serial communication at 115200 baud
//   while (!Serial);        // Wait for Serial Monitor to open (optional for ESP32)

//   Serial.println("I2C Scanner - Scanning for devices...");
// }

// void loop() {
//   byte error, address;
//   int devicesFound = 0;

//   // Scan all possible addresses from 1 to 127
//   for (address = 1; address < 127; address++) {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0) {
//       Serial.print("Device found at address: 0x");
//       if (address < 16) Serial.print("0");  // Add leading zero for single-digit hex
//       Serial.println(address, HEX);
//       devicesFound++;
//     } else if (error == 4) {
//       Serial.print("Unknown error at address 0x");
//       if (address < 16) Serial.print("0");
//       Serial.println(address, HEX);
//     }
//   }

//   if (devicesFound == 0) {
//     Serial.println("No I2C devices found.");
//   } else {
//     Serial.print("Total I2C devices found: ");
//     Serial.println(devicesFound);
//   }

//   delay(5000); // Wait 5 seconds before scanning again
// }
