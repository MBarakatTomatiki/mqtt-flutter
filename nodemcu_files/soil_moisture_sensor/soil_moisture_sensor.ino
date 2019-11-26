int sensorPin = A0; 
int sensorValue;  
int limit = 300; 
void setup() {
Serial.begin(115200);
pinMode(sensorPin, INPUT);
}
void loop() {  
sensorValue = analogRead(sensorPin); 

// We define the sensorValue as being the value read by the Arduino.

Serial.println("Analog Value : ");
Serial.println(sensorValue);

// We display the sensorValue on the serial monitor.
delay(1000);
}
