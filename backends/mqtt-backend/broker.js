const port = 1883;
const wsPort = 9001;

const aedes = require("aedes")();
const ws = require("websocket-stream");

const server = require("net").createServer(aedes.handle);
const httpServer = require("http").createServer();
ws.createServer({ server: httpServer }, aedes.handle);

server.listen(port, function () {
  console.log("server started and listening on port " + port);
});

httpServer.listen(wsPort, function () {
  console.log("Aedes MQTT-WS listening on port " + wsPort);
  aedes.publish({ topic: "aedes/hello", payload: "I'm broker " + aedes.id });
});
