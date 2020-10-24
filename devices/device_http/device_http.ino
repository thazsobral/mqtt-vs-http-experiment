#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Bischoff";
const char* password = "Kryptos12";
const char* httpServer = "192.168.0.109/sensor";
const int httpPort = 3000;

WiFiClient client;
HTTPClient http;

const int pinPump = 4;
const int pinHumidity = 0;

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;


void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}


float readHumidity(void) {
  int value = analogRead(pinHumidity);
  float valuePercent;
  valuePercent = 100 * ((978-(float)value) / 978);
  return valuePercent;
}

void setup() {
  pinMode(pinPump, OUTPUT);
  digitalWrite(pinPump, HIGH);
  Serial.begin(115200);

  setupWifi();

  
}

void loop() {
  now = millis();
  if (now - lastMeasure > 5000) {
    lastMeasure = now;

    if ((WiFi.status() == WL_CONNECTED)) {

      char json[80];
      float humidity;
      humidity = readHumidity();

      sprintf(json, "{\"humidity\":%f}", humidity);
  
      http.begin(client, "http://192.168.0.109:3000/sensor/");
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(json);
      http.end();
    }
  }
}
