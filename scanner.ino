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
long distance_limit = 15;
int buzzer = 13 ;//the pin of the active buzzer


void setup() {
  pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
  Serial.begin(9600);
  delay(1000);
  myservo.attach(9);
  direction = 0;

}

void loop() {
  // Detect if there is something in front of the scanner
  a=sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  // delay(1000);

  Serial.println(a > distance_limit);

  // If nothing is there sweep left to right
  if (a > distance_limit) {
    move = 1;
    digitalWrite(buzzer, LOW);
  } else {
    move = 0;
    digitalWrite(buzzer, HIGH);
  }

  if (move) {
    if (direction == 0) {
      // Serial.println("Direction 0");
      // Serial.println(pos);
      if (pos < 180) {
        pos += 1;
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);
      }
      else {
        direction = 1;
      }
    }

    if (direction == 1) {
      // Serial.println("Direction 1");
      // Serial.println(pos);
      if (pos > 0) {
        pos -= 1;
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);
      }
      else {
        direction = 0;
      }
    }
  }
 
    // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // // in steps of 1 degree
    // myservo.write(pos);              // tell servo to go to position in variable 'pos'
    // delay(15);                       // waits 15ms for the servo to reach the position
    // }

    // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //   delay(15);                       // waits 15ms for the servo to reach the position
    // }
  
  
  
  // If something is there stop and make a noise
  


}
