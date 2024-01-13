/*
 * **DIGITAL VOLTMETER AND SEGMENT DISPLAY 
 * WITH ATTINY13A**
 * 2020.06.28
 * Analog reading of four digit number represent in 7-segment display
 * 
 * Connect voltage divider between Vin,A0,GND.
 * Set Max value.
 * 
 * Segment display is controlled by 74LS595 shift registers
 * pin B to H of first shift register goes to 7 segments
 * pin B to F of second shift register goes to common pins
 * 
 * 
 */

#include <avr/pgmspace.h> 

#define SER_Pin 0
#define RCLK_Pin 1
#define SRCLK_Pin 2

 #define number_of_74ls595s 2

 #define numOfRegisterPins number_of_74ls595s * 8

boolean registers[numOfRegisterPins];

const byte pins[8]={1,2,3,4,5,6,7,8};

const boolean numbers[11][7]PROGMEM ={
  {1,1,1,1,1,1,0},  //0
  {0,1,1,0,0,0,0},  //1
  {1,1,0,1,1,0,1},  //2
  {1,1,1,1,0,0,1},  //3
  {0,1,1,0,0,1,1},  //4
  {1,0,1,1,0,1,1},  //5
  {1,0,1,1,1,1,1},  //6
  {1,1,1,0,0,0,0},  //7
  {1,1,1,1,1,1,1},  //8
  {1,1,1,1,0,1,1},  //9
  {0,0,0,0,1,0,0}   //.
  };

boolean Nom;

int Max = 3030;  // Set the hightest value can read

  #define mode 0 // 1-cathode , 0-anode
  

void setup() {
  pinMode(SER_Pin,OUTPUT);
  pinMode(RCLK_Pin,OUTPUT);
  pinMode(SRCLK_Pin,OUTPUT);
  pinMode(A2,INPUT);

 clearRegisters();

 writeRegisters();

}



void clearRegisters(){
  for(byte b = numOfRegisterPins; b>= 1; b--){
    registers[b-1] = LOW;
  }
  }


  void writeRegisters(){
    digitalWrite(RCLK_Pin,LOW);

   for(byte b = numOfRegisterPins; b>=1; b--){
   digitalWrite(SRCLK_Pin, LOW);
  digitalWrite(SER_Pin, registers[b-1]);
   digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
  }


  void setRegisterPin(byte index, boolean value){
    registers[index] = value;
  }



byte digits[]={0,0,0,0,10};

void loop() {

int val=analogRead(A2);
val=map(val,0,1023,0,Max);

digits[0]=val/1000;
digits[1]=(val-digits[0]*1000)/100;
digits[2]=(val-(digits[0]*1000+digits[1]*100))/10;
digits[3]=val-(digits[0]*1000+digits[1]*100+digits[2]*10);

writeDisplay();

}

byte a=0;
void writeDisplay(){

  
setRegisterPin(9+a,!mode);


for(byte i=0;i<7;i++){
  
Nom = pgm_read_byte(&numbers[digits[a]][i]);
 
  if(Nom){
   
    setRegisterPin(pins[i],mode);
  }else{
  
    setRegisterPin(pins[i],!mode);
  }
}

writeRegisters(); 

setRegisterPin(9+a,mode);

  a++;
  if(a>6){
   a=0;
  
  }
  delay(5);
 
}  





   
  
