const express = require('express');
const http = require('http');
const WebSocket = require('ws');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

app.use(express.json());
app.use(express.static(__dirname + '/public'));

// Endpoint to receive data from ESP32
app.post('/data', (req, res) => {
  const data = req.body;
  console.log("Data received from ESP32:", data);

  // Broadcast data to all connected clients
  wss.clients.forEach(client => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });

  res.sendStatus(200);
});

// Serve the web interface
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/public/index.html');
});

// WebSocket connection
wss.on('connection', ws => {
  console.log('Client connected');
  ws.on('close', () => console.log('Client disconnected'));
});

server.listen(3000, () => {
  console.log('Server listening on http://localhost:3000');
});
