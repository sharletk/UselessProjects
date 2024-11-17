[Video Google Drive Link](https://drive.google.com/file/d/1BM9XkCTqSJDIoxF78CrqXCmW3M8M-xxR/view?usp=sharing)

<img width="1280" alt="readme-banner" src="https://github.com/user-attachments/assets/35332e92-44cb-425b-9dff-27bcf1023c6c">

# WildAlert: Nature's Smartwatch (Real Time Monitoring & Alert System) 🎯


## Basic Details
### Team Name: Sharlet Kurien's Team

### Team Members
- Team Lead: Sharlet George Kurien - Saintgits College of Engineering (Autonomous), Kottayam, Kerala

### Project Description
A real-time monitoring and alert system that tracks wildlife species, evaluates their state, and assesses environmental conditions to better monitor and protect wildlife.

### The Problem (that doesn't exist)
What if animals felt left out of the smartwatch revolution? Wildlife needs personalized fitness tracking too!

### The Solution (that nobody asked for)
Introducing "FitBit for Fauna" — a real-time system that monitors wildlife movements, emotional states, and environmental vibes, sending alerts for when a lion needs yoga or a panda craves cooler bamboo. 🌿

## Technical Details  

### Technologies/Components Used  

#### For Software:  
- **Languages Used**: JavaScript, HTML, CSS  
- **Frameworks Used**: Express.js  
- **Libraries Used**: WebSockets (ws), Chart.js  
- **Tools Used**: Arduino IDE  

#### For Hardware:  
- **Main Components**:  
  - ESP 32 with WROOM  
  - B840 Breadboard (840 Points)  
  - Jumper Wires  
  - Robodo BE0033 BMP280 Pressure Sensor Module  
  - INVNETO GY-291 ADXL345 3-Axis Accelerometer Gyroscope Module  
  - Robocraze Banggood HC-SR04 Ultrasonic Module  
  - Robocraze IR Proximity Sensor Module  
  - Robocraze 1.3-inch I2C OLED Display  
  - Robocraze DS3231 AT24C32 RTC Memory Module  
  - Robodo Active Buzzer Module  

- **Specifications**:  
  - Sensors with IIC/I2C interfaces for efficient data communication.  
  - OLED display resolution of 128x64 for clear data visualization.  
  - Wi-Fi capability for seamless connectivity.  

- **Tools Required**:  
  - Precision Screwdriver Set  
  - Soldering Kit  
  - Multimeter  

### Implementation  

#### For Software:  

**Installation**  
1. Install **Node.js** and **npm**.  
   ```bash  
   sudo apt install nodejs npm   # For Linux  
   brew install node             # For macOS  
   ```  
2. Install dependencies in the monitor directory:  
   ```bash  
   npm install
   ```  

**Run**  
1. Start the server:  
   ```bash  
   node server.js  
   ```  
2. Open the browser and navigate to the provided server URL.  

#### For Hardware:  
1. Assemble components on the breadboard as per the circuit design.  
2. Write and upload the Arduino sketch via **Arduino IDE** to the ESP32:  
   - Ensure Wi-Fi credentials are set in the sketch.  
   - Use the installed libraries for interfacing with sensors and the OLED display.  
3. Verify data transmission from ESP32 to the server via WebSocket.  
4. Use the web application to visualize data and interact with the system.  

### Project Documentation  

#### For Software:  

##### Screenshots  

1. **Dashboard View**  
   ![Dashboard](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Dashboard.jpg)  
   *This screenshot shows the real-time dashboard displaying wildlife sensor data, including temperature, pressure, and gyroscope readings.*  

2. **Graph Visualization**  
   ![Visualization](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Visualization.jpg)
   *This image highlights the Chart.js implementation, plotting sensor data over time for easy analysis.*  

3. **WebSocket Connection Status**  
   ![WebSocket](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/WebSocket.jpg)
   *This screenshot displays the WebSocket connection established between the ESP32 and the server, confirming successful data transmission.*  

##### Diagrams  

1. **Workflow Diagram**  
   ![Workflow](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Workflow.png)  
   *This diagram explains the system architecture, showing how data flows from hardware sensors to the ESP32, then to the server, and finally to the web interface for visualization.*  

#### For Hardware:  

##### Schematic & Circuit  

1. **Circuit Diagram**  
   ![Circuit](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Circuit.png)  
   *This diagram shows the connections between the ESP32, sensors, and other components, including power supply and I2C communication lines.*  

2. **Schematic**  
   ![Schematic](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Schematic.png)  
   *This schematic provides a detailed overview of the hardware setup, including pin configurations and component specifications.*  

### Build Photos  

1. **Components**  
   ![Components-1](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Components-1.jpg)
   ![Components-2](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/Components-2.jpg)  
   *Components shown include: ESP32 with WROOM, breadboard, jumper wires, BMP280 pressure sensor module, ADXL345 accelerometer, ultrasonic module, IR proximity sensor, 1.3-inch OLED display, DS3231 RTC module, active buzzer, soldering kit, and multimeter.*  

2. **Build Process**   
   *Step 1: Assemble sensors and modules on the breadboard.  
   Step 2: Connect components using jumper wires based on the circuit diagram.  
   Step 3: Solder key connections for stability.  
   Step 4: Load the Arduino sketch onto the ESP32 using the Arduino IDE.  
   Step 5: Test individual components (e.g., sensor data) before full integration.*  

3. **Final Product**  
   ![Final Product](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/final_product.jpg)  
   ![Final Product Full](https://raw.githubusercontent.com/sharletk/UselessProjects/refs/heads/master/assets/final_product_full.jpg) 
   *The final build integrates all components into a compact unit, connected wirelessly to the server. The OLED display shows real-time data, while the web application visualizes trends and alerts in the monitoring system.*  

### Project Demo  
#### Video  
[Google Drive Link](https://drive.google.com/file/d/1BM9XkCTqSJDIoxF78CrqXCmW3M8M-xxR/view?usp=sharing)
*The video demonstrates the project's end-to-end functionality, starting with hardware setup and data collection. It shows the ESP32 transmitting real-time sensor data to the server, visualizing it on the web dashboard using graphs, and triggering alerts for specific conditions. The seamless connection via WebSocket and the user-friendly interface highlight the system's effectiveness.*  

## Team Contributions
- Sharlet George Kurien: Core Contributor

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProject--24-24?link=https%3A%2F%2Fwww.tinkerhub.org%2Fevents%2FQ2Q1TQKX6Q%2FUseless%2520Projects)

