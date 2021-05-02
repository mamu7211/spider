#include <Arduino.h>


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Serial.println("Waiting...");
}


bool connected = false;


void loop() {
  while(!Serial.available()); // Do nothing...
  
  while(!connected) {
    String s = Serial.readString();
    if (s == "CONN"){
      connected = true;
      delay(100);
      Serial.println("RDY:Connected....");
    }
  }

  while(Serial.available()) {
    String s = Serial.readString();
    Serial.println("RCV:" + s);
    Serial.flush();
  }
  
}