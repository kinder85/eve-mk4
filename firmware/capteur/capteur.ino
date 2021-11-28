/*
Measuring Current Using ACS712
*/

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int sensorPin1 = 8;
int sensorPin2 = 9;
int sensorPin3 = 10;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonard(4, 5, MAX_DISTANCE);
NewPing sonarg(6, 7, MAX_DISTANCE);
char input;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
void setup(){

   pinMode(INPUT,sensorPin1);
 pinMode(INPUT,sensorPin2);
 pinMode(INPUT,sensorPin3);
 Serial.begin(9600);
}

void loop(){
 
 
 int resultBinary = analogRead(A5);
  float resultVolts = resultBinary / 1024.0 * 5.0;
  int R1 = 9960;
  int R2 = 4680;
  float tension = resultVolts / R2 * (R1 + R2);

  sensorValue1 = digitalRead(sensorPin1); 
 sensorValue2 = digitalRead(sensorPin2); 
 sensorValue3 = digitalRead(sensorPin3); 
 
  
  
  if (sonar.ping_cm()>200){
    sonar.ping_cm()== 200;
  }
 if (sonard.ping_cm()>200){
    sonard.ping_cm()== 200;
  }
  if (sonarg.ping_cm()>200){
    sonarg.ping_cm()== 200;
  }
  
 input = Serial.read();
    switch (input) {

//       "t" command: returns time in millis since reset/powerup
      case 't':
 
  Serial.print(tension,2);
  Serial.print(",");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(",");
  Serial.print(sonard.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(",");
  Serial.print(sonarg.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println();
  //delay(1000);
 break;




  case 'l':
 
  Serial.print(tension,2);
  Serial.print(",");
  Serial.print(sensorValue2); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(",");
  Serial.print(sensorValue1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(",");
  Serial.print(sensorValue3); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println();
  //delay(1000);
 break; 
    }
}
