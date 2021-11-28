
int dir1PinA = 5;
int dir2PinA = 4;
int speedPinA = 14; // Needs to be a PWM pin to be able to control motor speed
int dir1PinB = 0;
int dir2PinB = 13;
int speedPinB = 12;
const char EOPmarker = '.'; 
char serialbuf[128];


#include <string.h> 
#define MAX_STRING_LEN 40 
#include <ESP8266WiFi.h> 
const char* ssid = "OpenWrt n";
const char* password = "goodlife";
int ledPin = 16;
int ledPin2 = 15;
// ATTENTION GPIO13 correspond à la PIN 07
WiFiServer server(80);

void setup() {
  pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(speedPinB,OUTPUT);  
Serial.begin(115200);
//analogWriteRange(255);
//analogWriteFreq(1000);
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, 0);
pinMode(ledPin2, OUTPUT);
digitalWrite(ledPin2, 0);
// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

   // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

}
void sharp_Right(char a,char b,char z)
{
analogWrite(speedPinA, a);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, b);
digitalWrite(dir1PinB, HIGH);
digitalWrite(dir2PinB, LOW);
delay(z*10);
}

void sharp_Left(char a,char b,char z)
{
analogWrite(speedPinA, a);//Sets speed variable via PWM 
digitalWrite(dir1PinA, HIGH);
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB, b);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
delay(z*10);
}

void stop()                    //Stop
{
analogWrite(speedPinA, 0);
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 0);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);


}   
void advance(char a,char b,char z)          //Move forward
{
analogWrite(speedPinA, a);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, b);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
Serial.println("avan");
delay(z*10);

}  
void back_off (char a,char b,char z)          //Move backward
{
analogWrite(speedPinA, a);
digitalWrite(dir1PinA, HIGH);
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB, b);
digitalWrite(dir1PinB, HIGH);
digitalWrite(dir2PinB, LOW);;
Serial.println("arr");
delay(z*10);

}
void turn_L (char a,char z)             //Turn Left
{
analogWrite(speedPinA, 0);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, a);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
//Serial.print("droit");
delay(z*10);

}
void turn_R (char a,char z)             //Turn Right
{
analogWrite(speedPinA, a);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 0);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
delay(z*10);
}
void loop() {
  WiFiClient client = server.available();
 
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        static int bufpos = 0; //starts the buffer back at the first position in the incoming serial.read
      char inchar = client.read(); //assigns one byte (as serial.read()'s only input one byte at a time
      if (inchar != EOPmarker) { //if the incoming character is not the byte that is the incoming package ender
        serialbuf[bufpos] = inchar; //the buffer position in the array get assigned to the current read
        bufpos++; //once that has happend the buffer advances, doing this over and over again until the end of package marker is read.
       }
      else { //once the end of package marker has been read 
        serialbuf[bufpos] = 0; //restart the buff
        bufpos = 0; //restart the position of the buf
        int rx_byte = atoi(subStr(serialbuf, ",", 1));
        int y = atoi(subStr(serialbuf, ",", 2));
        int p = atoi(subStr(serialbuf, ",", 3));
     Serial.print(rx_byte);
      Serial.print(y);
       Serial.println(p);
      if (rx_byte == 1) {
      advance(y,y,p);
         

    }
    // if it's an L (ASCII 76) turn off the LED:
    if (rx_byte == 2) {
              back_off (y,y,p);
                  

    }//move back in max speed
  if (rx_byte == 4){
    turn_L(y,p);
    
    }
    if (rx_byte == 3){
      turn_R(y,p);
          
    }
    if (rx_byte == 5){
      stop();
    }
  if (rx_byte == 6){
      sharp_Left(y,y,p);
    }
    if (rx_byte == 7){
      sharp_Right(y,y,p);
    }
     if (rx_byte == 8){
      digitalWrite(ledPin, 1);
    digitalWrite(ledPin2, 1);
    
    }
    if (rx_byte == 9){
      digitalWrite(ledPin, 0);
    digitalWrite(ledPin2, 0);
   
    }

}
      
      
      
      
      }
 
     
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }


}


char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[MAX_STRING_LEN];
  int i;
  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
}
 return sub;
}
