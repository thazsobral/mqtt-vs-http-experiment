const aedes = require("aedes")();
const server = require("net").createServer(aedes.handle);
const port = 1883;

aedes.subscribe("esp8266/pump", function (packet, cb) {
  console.log(packet.payload.toString());
});

aedes.subscribe("esp8266/humidity", function (packet, cb) {
  console.log(packet.payload.toString());
});

server.listen(port, function () {
  console.log("server started and listening on port " + port);
});
