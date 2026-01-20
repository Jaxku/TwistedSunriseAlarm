#include <ESP8266WiFi.h>      // Use <WiFi.h> for ESP32
#include <PubSubClient.h>
#include <Servo.h>

// WiFi credentials
const char* ssid = "SSID HERE PLS";
const char* password = "PASSWORD HERE PLS";

// HiveMQ Cloud credentials
const char* mqtt_server = "broker.hivemq.com";  // Your HiveMQ cluster URL (Current is public cluster)
const int mqtt_port = 1883; // Change port if using your own
//const char* mqtt_user = "USER"; // Add username if you are using your own HiveMQ Cluster and not the public one
//const char* mqtt_password = "PASS"; // Add password if you are using your own HiveMQ Cluster and not the public one

// MQTT Topic
const char* topic = "UNIQUE TOPIC NAME"; // Create a unique topic name 

WiFiClient espClient;
PubSubClient client(espClient);
Servo myservo;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(">>> MESSAGE RECEIVED - MOVING SERVO <<<");
  
  // Your original sweep code
  myservo.write(150);
  delay(1000);
  myservo.write(-10);
  delay(1000);
  
  Serial.println(">>> SWEEP DONE <<<");
}

void setup() {
  Serial.begin(115200);
  myservo.attach(D2);
  myservo.write(0);

  // Connect WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED!");

  // Connect MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266_Servo_Client")) {
      Serial.println(" CONNECTED!");
      client.subscribe(topic);
      Serial.print("Subscribed to: ");
      Serial.println(topic);
    } else {
      Serial.println(" FAILED. Retrying...");
      delay(3000);
      return;
    }
  }
  client.loop();
}