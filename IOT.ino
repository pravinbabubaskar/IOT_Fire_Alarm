

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "gwXLabc35yg3-Q9WH9X3ZiNU0dLABs";
char ssid[] = "OPPO A5 2020";
char pass[] = "1253765";

BlynkTimer timer;
int pinValue = 0;

#define REDLED D1
#define GREENLED D2
#define Buz D3
#define FireSensor D0
#define motor D4

void setup() {

  Serial.begin(9600);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(Buz, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(FireSensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, MOBILEnotification);

}
BLYNK_WRITE(V0) {

  pinValue = param.asInt();

}

void MOBILEnotification() {
  
  int sensor = digitalRead(FireSensor);
  
  if (pinValue == 1) {
    Serial.println("System is ON");
  
    if (sensor == 1) {
    
      digitalWrite(GREENLED, HIGH);
      digitalWrite(REDLED, LOW);
      digitalWrite(Buz, LOW);
      digitalWrite(motor, LOW);
    
    }
    else if (sensor == 0) {
    
      Blynk.notify("ALERT! fire detected !!");
      digitalWrite(GREENLED, LOW);
      digitalWrite(REDLED, HIGH);
      digitalWrite(Buz, HIGH);
      digitalWrite(motor, HIGH);
    
    }
  }
  else if (pinValue == 0) {
  
    Serial.println("System is OFF");
  
  }

}

void loop() {

  Blynk.run();
  timer.run();

}
