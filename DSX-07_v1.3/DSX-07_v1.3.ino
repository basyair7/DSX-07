//Code project : DSX-07
//Version      : v 1.3
//         BY Ahul07
/*before verify/Upload, don't forget to Install the libraries  
 *go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links
 */

/*Credit : Thanks Allah SWT., Nabi Muhammad SAW., Thanks My mother & father, Thanks My Brother, and Thank you my friends from Electrical Engineering'19 USK,  
 *         Syiah Kuala University.
 */
 
#include <DSXMotor.h>
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 225 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

DSX_DCMotor motor1(1, MOTOR12_1KHZ); 
DSX_DCMotor motor2(2, MOTOR12_1KHZ);

Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(9);  
  myservo.write(116); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=40)
 {
  moveStop();
  delay(200);
  moveBackward();
  delay(800);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    distance = readPing();
    delay(200);
    myservo.write(116);
    delay(500); 
    return distance;
}

int lookLeft()
{
    myservo.write(171);
    delay(500);
    distance = readPing();
    delay(200);
    myservo.write(116); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);     
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}  
