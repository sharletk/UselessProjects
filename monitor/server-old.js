const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 3000; // Port for the server

// Middleware
app.use(cors());
app.use(bodyParser.json());

// Data storage (in-memory for this example)
let sensorData = {};

// Route to receive data from ESP32
app.post('/data', (req, res) => {
    // Assuming ESP32 sends data in the following format:
    // { "time": "2024-11-03T12:00:00Z", "distance": 50, "ir": 25, "gyro": {"x": 1, "y": 2, "z": 3} }
    sensorData = req.body; // Store the received data
    console.log('Data received:', sensorData);
    res.status(200).send('Data received');
});

// Route to serve HTML page displaying the sensor data
app.get('/', (req, res) => {
    res.send(`
        <!DOCTYPE html>
        <html>
        <head>
            <title>ESP32 Sensor Data</title>
            <script>
                async function fetchData() {
                    const response = await fetch('/data');
                    const data = await response.json();
                    document.getElementById('sensor-data').innerText = JSON.stringify(data, null, 2);
                }

                setInterval(fetchData, 1000); // Fetch data every second
            </script>
        </head>
        <body>
            <h1>ESP32 Sensor Data</h1>
            <pre id="sensor-data">Waiting for data...</pre>
        </body>
        </html>
    `);
});

// Route to get the latest sensor data
app.get('/data', (req, res) => {
    res.json(sensorData);
});

// Start the server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
