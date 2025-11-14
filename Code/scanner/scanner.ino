#include <SR04.h>
#include <Servo.h>

#define TRIG_PIN 12
#define ECHO_PIN 11

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
Servo myservo;

int pos = 0;
int direction = 0;
int move = 0;

long distance_limit = 15;   // trigger range in cm of when to stop the scanner for a detection
int buzzer = 13;            // the pin of the active buzzer


void setup() {
  pinMode(buzzer, OUTPUT);  // initialize the buzzer pin as an output
  Serial.begin(9600);
  delay(1000);
  myservo.attach(9);        // attach servo motor to pin 9
  direction = 0;            // initialize direction that servo motor is turning

}

void loop() {
  a=sr04.Distance();        // Detect if there is something in front of the scanner

  // Debug print statements to see the distance to the object in front of the sensor
  // Serial.print(a);
  // Serial.println("cm");
  
  if (a > distance_limit) {  // If no object is detected there sweep left to right and turn off buzzer
    move = 1;
    digitalWrite(buzzer, LOW);
  } else {                   // If an object is detected stop moving and turn on the buzzer
    move = 0;
    digitalWrite(buzzer, HIGH);
  }

  if (move) {
    if (direction == 0) {    // rotate up from 0 degrees
      if (pos < 180) {
        pos += 1;
        myservo.write(pos);              
        delay(15);
      }
      else {
        direction = 1;
      }
    }

    if (direction == 1) {    // rotate down from 180 degrees
      if (pos > 0) {
        pos -= 1;
        myservo.write(pos);              
        delay(15);
      }
      else {
        direction = 0;
      }
    }
  }
}
