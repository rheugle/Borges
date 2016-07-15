/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
// create servo object to control a servo
// twelve servo objects can be created on most boards

float persistence;

int pos0 = 0;    // variable to store the servo position
int tag0 = 100;

int pos1 = 0;
int tag1 = 100;

//Servo 1 
int servo1_min = 60;
int servo1_max = 130;

//Servo 2
int servo2_min = 80;
int servo2_max = 140;

//Servo 3
int servo3_min = 60;
int servo3_max = 120;

//Servo 4
int servo4_min = 70;
int servo4_max = 158;

//Servo 5 
int servo5_min = 0;
int servo5_max = 40;


int arrg1[] = {10,20,40};

int currentConf[] = {70,90,120};
int n=0;

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(11);  // attaches the servo on pin 9 to the servo object
  
  Serial.begin(9600);
  
  myservo1.write(currentConf[0]);
  myservo2.write(currentConf[1]);
  myservo3.write(currentConf[2]);

  //Affects degree to which finer noise is seen - more persistence 
  //gives smoother results
  persistence = 0.25;
  
}

void loop() {

  if (Serial.available()>0){
  
  String readdat = Serial.readString();  
  Serial.println(readdat);
  Serial.println();
  
  if (readdat=="found"){
  }
  else{
    GoToPosition();
    Serial.println("hello");
  }
  
  }

  
}

void GoToPosition(){

    int s1 = int(random(servo1_min, servo1_max));
    int s2 = int(random(servo2_min, servo2_max));
    int s3 = int(random(servo3_min, servo3_max));

    int futureConf[] = {s1,s2,s3};

    int a = currentConf[0];
    int b = currentConf[1];
    int c = currentConf[2];

    for (int i=0;i<3;i++){
      
      if(currentConf[i] > futureConf[i]){
     
        while(currentConf[i] != futureConf[i]){
          currentConf[i] -= 1;
          if(i==0){
            myservo1.write(currentConf[i]);
          }
          if(i==1){  
            myservo2.write(currentConf[i]);
          }
          if(i==2){
            myservo3.write(currentConf[i]);
          }
          delay(40);
        } 
     }
     
     else if(currentConf[i] < futureConf[i]){
        while(currentConf[i] != futureConf[i]){
          currentConf[i] += 1;
          if(i==0){
            myservo1.write(currentConf[i]);
          }
          if(i==0){
            myservo2.write(currentConf[i]);
          }
          if(i==0){          
            myservo3.write(currentConf[i]);
          }
          delay(40);
        } 
      }     
     }
     delay(50);  
}



//  char readBytes = Serial.read(); 
//  if (readBytes=="h"){
//  Serial.print(readBytes);
//  for (int i=0;i<5;i++){
//  char readBytes = Serial.read(); 
//  Serial.print(readBytes);
//  }
//  }
//  Serial.println();
//
// CONTROL ROBOT MOTION VIA SERIAL COMMAND
//  if (Serial.available() > 0) {
//    pos0 = Serial.parseInt(); //read int or parseFloat for ..float...  
//  }
//
// if (pos0 != tag0 && pos0 != 0) {
//
//  //Code to make add delay into servo motion with user input.
//  if (tag0>=pos0){
//    while(tag0!=pos0){
//      tag0-=1;
//      myservo1.write(tag0);
////      myservo2.write(tag0);
////      myservo3.write(tag0);
//      delay(10);
//    }
//  }
//  else{
//    while(tag0!=pos0){
//      tag0+=1;
//      myservo1.write(tag0);
////      myservo2.write(tag0);
////      myservo3.write(tag0);
//      delay(10);
//    }
//  }  
//  
//  myservo1.write(tag0);
////  myservo2.write(tag0);
////  myservo3.write(tag0);
//  Serial.println(tag0);
//  
// }
//




//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
//    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
//    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
//    myservo3.write(0);              // tell servo to go to position in variable 'pos' 
//    delay(1);                       // waits 15ms for the servo to reach the position
//  }
  
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
//    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
//    myservo3.write(0);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//}
