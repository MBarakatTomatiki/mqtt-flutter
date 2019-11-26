int sensorPin = A0; 
int sensorValue;  
int limit = 300; 
void setup() {
Serial.begin(9600);
pinMode(13, OUTPUT);
}
void loop() {  
sensorValue = analogRead(sensorPin); 

// We define the sensorValue as being the value read by the Arduino.

Serial.println("Analog Value : ");
Serial.println(sensorValue);

// We display the sensorValue on the serial monitor.

if (sensorValue<limit) {
digitalWrite(13, HIGH); 
}
else {
digitalWrite(13, LOW);
 }
delay(1000); 
}
