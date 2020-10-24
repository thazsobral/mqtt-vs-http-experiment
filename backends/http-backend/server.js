const express = require("express");

const app = express();

app.use(express.json());

app.post("/sensor", (req, res) => {
  console.log(req.body);
  res.send("OK");
});

app.listen(3000, () => {
  console.log(`Run server in http://localhost:3000`);
});
