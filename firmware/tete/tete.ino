#include "LedControl.h"
#include <Arduino.h>
#include <ESP8266RTTTLPlus.h>
#define PIN_BUZZER    A0
#define ledPin 25
#define ledPina 24
#define ledPinb 23

uint8_t const pin_buzzer = PIN_BUZZER;
int i = 0;
int rx_byte = 0;
LedControl lc=LedControl(12,13,15,2);  // Pins: DIN,CLK,CS, # of Display connected



char *song1 = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
char *song = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
//char *song = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
//char *song = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
//char *song = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
//char *song = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
//char *song = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
//char *song = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
//char *song = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
//char *song = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
//char *song = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
//char *song = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
//char *song = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
//char *song = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
//char *song = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
//char *song = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
//char *song = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
//char *song = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
//char *song = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
//char *song = "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#";
//char *song = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
//char *song = "smbdeath:d=4,o=5,b=90:32c6,32c6,32c6,8p,16b,16f6,16p,16f6,16f.6,16e.6,16d6,16c6,16p,16e,16p,16c";
//char *song = "Monty P:d=4,o=5,b=200:f6,8e6,d6,8c#6,c6,8b,a#,8a,8g,8a,8a#,a,8g,2c6,8p,8c6,8a,8p,8a,8a,8g#,8a,8f6,8p,8c6,8c6,8p,8a,8a#,8p,8a#,8a#,8p,8c6,2d6,8p,8a#,8g,8p,8g,8g,8f#,8g,8e6,8p,8d6,8d6,8p,8a#,8a,8p,8a,8a,8p,8a#,2c6,8p,8c6";
//char *song = "Yaketysax:d=4,o=5,b=125:8d.,16e,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8a4,16a4,16a#4,16b4,16d,16e,16d,g,p,16d,16e,16d,8g,8g,16e,16d,16a4,16b4,16d,16b4,8e,16d,16b4,16a4,16b4,8d,16d,16d,16f#,16a,8f,d,p,16d,16e,16d,8g,16g,16g,8g,16g,16g,8g,8g,16e,8e.,8c,8c,8c,8c,16e,16g,16a,16g,16a#,8g,16a,16b,16a#,16b,16a,16b,8d6,16a,16b,16d6,8b,8g,8d,16e6,16b,16b,16d,8a,8g,g;"
//char *song = "YMCA:d=4,o=5,b=160:8c#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8a#,2p,8a#,8g#,8f#,8g#,8a#,c#6,8a#,c#6,8d#6,8b,2p,8b,8a#,8g#,8a#,8b,d#6,8f#6,d#6,f.6,d#.6,c#.6,b.,a#,g#";
//char *song = "BarbieGirl:d=4,o=5,b=125:8g#,8e,8g#,8c#6,a,p,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#";
//char *song1 = "r2d2_nokia:d=4,o=5,b=450:17c8,480p,17c#8,480p,17d8,480p,17d#8,480p,17e8,480p,17f8,480p,17f#8,480p,17g8,480p,17g#8,480p,1a8,480p,34g#8,480p,34g8,480p,34f#8,480p,34f8,480p,34e8,480p,34d#8,480p,34d8,480p,34c#8,480p,17c8,480p,17c#8,480p,17d8,480p,17d#8,480p,17e8,480p,17f8,480p,f#8,480p,17a8,480p,17g#8,480p,17g8,480p,17f#8,480p,17f8,480p,17e8,480p,2d#8,480p,17b6,480p,17d7,480p,17d#6,480p,17f#8,480p,17c#7,480p,17g#7,480p,17f6,480p,17a#7,480p,17e7,480p,17g#8,480p,17e8,480p,17g#6,480p,17g7,480p,17c#7,480p,17g7,480p,17f#8,480p,17c#7,480p,17f#6,480p,17f8,480p,17g#7,480p,17g6,480p,17a8,480p,17c#8,480p,17g6,480p,17f#8,480p,17g7,480p,17f8,480p,17a#6,480p,17f#8,480p,17d8,480p,17g7,480p,17g8,480p,17c8,480p,17g#6,480p,17a8";













int randomArray2[4] =  {
  
             // Length of time in milliseconds of a whole note (i.e. a full bar).
           
  500,      
  250,        
 120,
  160,
  
  
  };


byte eyeOff[] =

{

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000

};



byte eyeOpened[] =

{

   B00111100,

   B01100110,

   B01000010,

   B11011011,

   B11011011,

   B01000010,

   B01100110,

   B00111100

};

byte pligauche[]
{ 
 B00011000,
B01111110,
B11000001,
B10000010,
B10011100,
B10011000,
B01110000,
B00010000,
  
   
};

byte plidroit[]
{ 
B00100000,
B01110000,
B01110000,
B11011000,
B10011100,
B10000010,
B01111110,
B00011000,
  
 
  
  
  
  
  
};

byte eyeClosed[] =

{

  B00011000,

  B00011000,

  B00111100,

  B00111100,

  B00111100,

  B00111100,

  B00011000,

  B00011000

};

 

byte eyeToLeft[] =

{

   B00111100,

   B01100110,

   B01000010,

   B11000011,

   B11011011,

   B01011010,

   B01100110,

   B00111100

};

 

byte eyeToRight[] =

{

   B00111100,

   B01100110,

   B01011010,

   B11011011,

   B11000011,

   B01000010,

   B01100110,

   B00111100

};



byte love[] =

{

   B00001100,

   B00011110,

   B00111110,

   B01111100,

   B01111100,

   B00111110,

   B00011110,

   B00001100

};



byte happy[] =

{

   B00111100,
   B01000010,
   B10010101,
   B10100001,
   B10100001,
   B10010101,
   B01000010,
   B00111100

};



byte eye2Opened[] =

{

   B00111100,
   B01111110,
   B11111111,
   B11100111,
   B11100111,
   B11111111,
   B01111110,
   B00111100

};

 

byte eye2Closed[] =

{

  B00011000,

  B00011000,

  B00111100,

  B00111100,

  B00111100,

  B00111100,

  B00011000,

  B00011000

};

byte quest[]
{
  B00000000,
  B00001100,
  B00001110,
  B00000011,
  B10110011,
  B10111110,
  B00001100,
  B00000000 
};

byte eye2ToUpperLeft[] =

{

   B00111100,

   B01111110,

   B11111111,

   B11111111,

   B11111111,

   B11110011,

   B01110010,

   B00111100

};

 

byte eye2ToRight[] =

{

   B00111100,

   B01100110,

   B11100111,

   B11111111,

   B11111111,

   B11111111,

   B01111110,

   B00111100

};

 

void setup()

{
  Serial.begin(9600);
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,1);  // Set intensity levels
  lc.setIntensity(1,1);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  

}

 

void SetLeftEye(byte* mood)

{

  for (int i = 0; i < 8; i++)  

  {
    lc.setRow(1,i,mood[i]);
  }

}



void SetRightEye(byte* mood)

{

  for (int i = 0; i < 8; i++)

  {

    lc.setRow(0,i,mood[i]);

  }

}

void normal(){
    SetLeftEye(eyeOpened);
    SetRightEye(eyeOpened);
    i += 1;
    delay(1000);

    if (i == 3)
{
    SetLeftEye(eyeClosed);
    SetRightEye(eyeClosed);
    delay(100);
}

if(i >= 4)
{
  i = 0;
  
  }

    

    

    

    
  } 
void lov()
{
  digitalWrite(ledPin, LOW);
   digitalWrite(ledPinb, LOW);
   digitalWrite(ledPina, HIGH);
  SetLeftEye(love);
  SetRightEye(love);
    delay(2000);
    
}

void colere()
{digitalWrite(ledPin, LOW);
   digitalWrite(ledPinb, LOW);
   digitalWrite(ledPina, HIGH);
   
  SetLeftEye(plidroit);
  SetRightEye(pligauche);
    delay(1000);
    
}
void triste()
{
  digitalWrite(ledPinb, HIGH);
   digitalWrite(ledPina, LOW);
   digitalWrite(ledPin, LOW);
  SetLeftEye(pligauche);
  SetRightEye(plidroit);
    delay(1000);
    
}
void joix()
{
  digitalWrite(ledPinb, HIGH);
   //digitalWrite(ledPina, HIGH);
  SetLeftEye(happy);
  SetRightEye(happy);
    delay(1000);
   
   //digitalWrite(ledPina, LOW); 
}

void question()
{
  digitalWrite(ledPin, HIGH);
   digitalWrite(ledPina, LOW);
   digitalWrite(ledPinb, LOW);
  SetLeftEye(quest);
  SetRightEye(quest);
    delay(2000);
    
}
void check(){
  digitalWrite(ledPina, LOW);
  digitalWrite(ledPinb, HIGH);
  SetLeftEye(eyeToRight);

    SetRightEye(eyeToRight);

    delay(500);
   
    SetLeftEye(eyeToLeft);

    SetRightEye(eyeToLeft);
   
    delay(500);
   
   
}

     
void exa(){
 

    SetLeftEye(eye2ToUpperLeft);
    SetRightEye(eye2ToUpperLeft);
    delay(1000);
    SetLeftEye(eyeClosed);
    SetRightEye(eyeClosed);
    delay(1000);

   
}

void core_debug(char *p_msg)
{
  Serial.printf("core%d - %s",get_core_num(),p_msg);
}

void core_print_uint32(uint32_t data)
{
  Serial.printf("core%d - 0x%08x (%d)\n",get_core_num(),data,data);
}

bool write_to_other_core(uint32_t data)
{
  if (rp2040.fifo.push_nb(data)==false)
  {
    core_debug((char*)"failed to push\n");
    return false;
  }
  return true;
}

bool read_from_other_core(uint32_t *p_data)
{
  if (rp2040.fifo.available())
  {
    if (rp2040.fifo.pop_nb(p_data)==false)
    {
      core_debug((char*)"failed to pop\n");
      return false;
    }
    return true;
  }
  return false;
}


//void m1(){
 // long randIndex = random(0, 4);
    //  long randIndex2 = random(0, 3);
      // int randElem4 = randomArray2[randIndex2];
           
  //    int randElem = randomArray[randIndex];
      
   
 // Serial.println(randElem);
//Serial.println(randElem4);
//}


void loop()

{
  
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPinb, LOW);
   digitalWrite(ledPina, HIGH); 
 uint32_t message = 0;
if(Serial.available() > -1){
    
   
int rx_byte = Serial.read();  
 
 
 
 
 if (rx_byte == 'l') {
      
      lov();
      
    }
    
    if (rx_byte == 'e') {
      exa();
                  

    }
   if (rx_byte == 'c') {
      
      
      check();
    }
    if (rx_byte == 'r') {
      
      colere();
                  

    }
    if (rx_byte == 'j') {
      joix();
                  

    }
    if (rx_byte == 't') {
      triste();
                  

    }
    if (rx_byte == 'q') {
      question();
                  

    }
if (rx_byte == 'd') {
      write_to_other_core('d');
                  

    }
    if (rx_byte == 'w') {
      write_to_other_core('w');
      
      
    }
    if (rx_byte == 's') {
      write_to_other_core('s');
      
      
    }
    if (rx_byte == 'h') {
      write_to_other_core('l');
                  

    }
    if (rx_byte == 'n') {
      write_to_other_core('c');
                  

    }
else{
  normal();
}
}


}

void setup1(){
  pinMode(pin_buzzer, OUTPUT);
  digitalWrite(pin_buzzer, LOW);
  randomSeed(analogRead(A1));
  pinMode(ledPin, OUTPUT);
  pinMode(ledPina, OUTPUT);
  pinMode(ledPinb, OUTPUT);
}

void phrase1() {
    
    int k = random(1000,2000);
    digitalWrite(ledPin, HIGH);
    for (int i = 0; i <=  random(100,2000); i++){
        
        tone(pin_buzzer, k+(-i*2));          
        delay(random(.9,2));             
    } 
    digitalWrite(ledPin, LOW);   
    for (int i = 0; i <= random(100,1000); i++){
        
        tone(pin_buzzer, k + (i * 10));          
        delay(random(.9,2));             
    } 
}


void phrase2() {
    
    int k = random(1000,2000);
    digitalWrite(ledPin, HIGH);  
    for (int i = 0; i <= random(100,2000); i++){
        
        tone(pin_buzzer, k+(i*2));          
        delay(random(.9,2));             
    } 
    digitalWrite(ledPin, LOW);   
    for (int i = 0; i <= random(100,1000); i++){
        
        tone(pin_buzzer, k + (-i * 10));          
        delay(random(.9,2));             
    } 
}


void loop1() {
  uint32_t message = 0;
  e8rtp::loop();
if (read_from_other_core(&message)==true)
  {
    if (message == 'c')
    {
     int K = 2000;
    switch (random(1,4)) {
        
        case 1:phrase1(); break;
        case 2:phrase2(); break;
        case 3:phrase1(); phrase2(); break;
    }
    
    for (int i = 0; i <= random(3, 9); i++){
        
        digitalWrite(ledPin, HIGH);  
        tone(pin_buzzer, K + random(-1700, 2000));          
        delay(random(70, 170));  
        digitalWrite(ledPin, LOW);           
        noTone(pin_buzzer);         
        delay(random(0, 30));             
    } 
    noTone(pin_buzzer);         
    delay(random(2000, 4000));
    
    
    
    
    
    
    }
    if (message == 'l')
    {
  
    int K = 2000;
    switch (random(1,4)) {
        
        case 1:phrase1(); phrase2(); phrase1();break;
        case 2:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();break;
        case 3:phrase2(); phrase1(); phrase2(); break;
    }
    
    for (int i = 0; i <= random(3, 9); i++){
        
        digitalWrite(ledPin, HIGH);  
        tone(pin_buzzer, K + random(-1700, 2000));          
        delay(random(70, 170));  
        digitalWrite(ledPin, LOW);           
        noTone(pin_buzzer);         
        delay(random(0, 30));             
    } 
    noTone(pin_buzzer);         
    delay(random(2000, 4000));
    
    
    }
 if (message == 'd')
    {
   int K = 2000;
    switch (random(1,5)) {
        
        case 1:phrase1(); phrase2(); phrase1();phrase2(); phrase1(); phrase2();break;
        case 2:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();phrase2(); phrase1(); phrase2();break;
        case 3:phrase2(); phrase1(); phrase2();phrase1(); phrase2(); break;
        case 4:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();break;
    }
    
    for (int i = 0; i <= random(3, 9); i++){
        
        digitalWrite(ledPin, HIGH);  
        tone(pin_buzzer, K + random(-1700, 2000));          
        delay(random(70, 170));  
        digitalWrite(ledPin, LOW);           
        noTone(pin_buzzer);         
        delay(random(0, 30));             
    } 
    noTone(pin_buzzer);         
    delay(random(2000, 4000));
    
    }
 if (message == 'w')
    {
      
      
  e8rtp::setup(PIN_BUZZER, 8, song);
   // e8rtp::setup(PIN_BUZZER, 5, "Georgia on my mind: d=4,o=5,b=120: 8e,2g.,8p,8e,2d.,8p,p,e,a,e,2d.,8c,8d,e,g,b,a,f,f,8e,e,1c");

    
    e8rtp::start();
  
    }


    if (message == 's')
    {
      e8rtp::setup(PIN_BUZZER, 8, song1);
   // e8rtp::setup(PIN_BUZZER, 5, "Georgia on my mind: d=4,o=5,b=120: 8e,2g.,8p,8e,2d.,8p,p,e,a,e,2d.,8c,8d,e,g,b,a,f,f,8e,e,1c");

    
    e8rtp::start();
    }
  }
  // One second pause before repeating the loop and playing
 
}
