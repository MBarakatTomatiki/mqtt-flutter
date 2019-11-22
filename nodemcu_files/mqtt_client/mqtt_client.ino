/*
  @created by Sachin Kumar
  @mail sachinkum123567@gmail.com
  NodeMCU code for MQTT client broker
  That sends the data to cloud and further an flutter application can be used to view the data
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Redmi 6";
const char* password =  "123456789";
const char* mqttServer = "soldier.cloudmqtt.com";
const int mqttPort = 10755;
const char* mqttUser = "aypgvnsq";
const char* mqttPassword = "vsbiDXU4OIlB";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
