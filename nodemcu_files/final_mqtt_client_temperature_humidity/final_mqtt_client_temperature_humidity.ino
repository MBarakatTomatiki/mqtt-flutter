/*
  @created by Sachin Kumar
  @mail sachinkum123567@gmail.com
  NodeMCU code for MQTT client broker
  That sends the data to cloud and further an flutter application can be used to view the data
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS D4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Soil moisture inputs
int sensorPin = A0; 
int sensorValue;  
int limit = 500;

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
  pinMode(D8, OUTPUT);
 
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
  // client.subscribe("esp/test");
 
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
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(500);
  
  sensorValue = analogRead(sensorPin); 

// We define the sensorValue as being the value read by the Arduino.

Serial.println("Analog Value : ");
Serial.println(sensorValue);

// We display the sensorValue on the serial monitor.

if (sensorValue>limit) {
digitalWrite(D8, HIGH); 
}
else {
digitalWrite(D8, LOW);
 }
delay(1000); 
  int temp = sensors.getTempCByIndex(0);
  int humid = sensorValue;
  int humid_extra;
  if (humid > 999){
    humid_extra = 999;
    }
  else {
    humid_extra = humid;
    }
  String temp2 = String(temp);
  String humid2 = String(humid);
  char cstr[16];
  itoa(temp, cstr, 10);
  char hstr[16];
  itoa(humid, hstr, 10);
  client.publish("temp", cstr);
  client.publish("humd", hstr);
  delay(500);
}
