/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://www.trollmaker.com/article3/arduino-and-hc-sr04-ultrasonic-sensor
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(9,8,5,4,3,2);

#define trigPin 13
#define echoPin 12

#define redLed 11
#define greenLed 10

#define minDistance 4
#define maxDistance 100

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  //Inicializamos la pantalla
   lcd.begin(16, 2);
   lcd.clear();
   lcd.print("Distancia:");
}

void printDistance(int distance){
  Serial.print(distance);
  Serial.println(" cm");

  //Borro las letras antes de escribir
  lcd.setCursor(0,1);
  lcd.print("           ");
  lcd.setCursor(0,1);
  
  lcd.print(distance);
  lcd.print(" cm");
}
void loop() {
  lcd.setCursor(0,1);
  
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //The Pace of Sound is approximately 29.1 microseconds per centimetre. 
  distance = (duration/2) / 29.1;
  
  if (distance < minDistance) {
    digitalWrite(redLed,HIGH); 
    digitalWrite(greenLed,LOW);
  } else {
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);
  }
  
  if (distance >= maxDistance || distance <= 0){
    Serial.println("Out of range");
  } 
    printDistance(distance);
  
  delay(500);
}
