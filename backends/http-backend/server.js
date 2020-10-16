const express = require('express')
const http = require('http')

const app = express()
const server = http.Server(app)

app.listen(3000, () => {
    console.log(`Run server in http://localhost:3000`)
})
