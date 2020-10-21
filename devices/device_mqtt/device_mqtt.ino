#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bischoff";
const char* password = "Kryptos12";
const char* mqttServer = "192.168.0.109";
const int mqttPort = 1883;

const int pinPump = 4;
//const int pinPump = LED_BUILTIN;
const int pinHumidity = 0;

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

WiFiClient espClient;
PubSubClient client(espClient);


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

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();


  if(topic=="esp8266/pump"){
      Serial.print("Changing Pump to ");
      if(messageTemp == "on"){
        digitalWrite(pinPump, LOW);
        Serial.print("On");
      }
      else if(messageTemp == "off"){
        digitalWrite(pinPump, HIGH);
        Serial.print("Off");
      }
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("esp8266/pump");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

float readHumidity(void) {
  int value = analogRead(pinHumidity);
  float valuePercent;
  valuePercent = 100 * ((978-(float)value) / 978);
  return valuePercent;
}

void setup() {
  pinMode(pinPump, OUTPUT);
  
  Serial.begin(115200);

  setupWifi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("esp8266");

  now = millis();

  if (now - lastMeasure > 30000) {
    lastMeasure = now;

    float humidityPercent = readHumidity();
    char humidity[10];
    sprintf(humidity, "%f", humidityPercent);

    client.publish("esp8266/humidity", humidity);
    
    Serial.print("Humidity: ");
    Serial.println(humidity);
  }
}
