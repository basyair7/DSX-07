//Code project : DSX-07
//Version      : v 1.3
//        BY Ahul07
/* before verify/Upload, don't forget to Install the libraries  
 * go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links
 */

/*
 **************************************************************************************************************************************************
 * Credit : Thanks Allah SWT., Nabi Muhammad SAW., Thanks My mother & father, Thanks My Brother, and Thanks My Friends electrical enginner'19 usk *
 *         Syiah Kuala University                                                                                                                 *
 **************************************************************************************************************************************************
*/

#include <DSXMotor.h>
#include <NewPing.h>
#include <Servo.h>

//サーボの定義をする サーボ機能を作成する
#define TRIG_PIN A0 
#define ECHO_PIN A1
#define MAX_DISTANCE 200 
#define MAX_SPEED 225 //sets speed of DC motors
#define MAX_SPEED_OFFSET 20 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

//可変モーターの作成
DSX_DCMotor motor_1(1, MOTOR12_1KHZ); //モーター 1
DSX_DCMotor motor_2(2, MOTOR12_1KHZ); //モーター 2

Servo myservo; //サーボ変数を作成する

//前進、距離、速度を設定する変数を作成する
boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  //サーボピンを挿入する
  myservo.attach(9);
  //サーボ角度を設定する
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
  //左右の距離変数を作成する
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if(distance <= 40){
    moveStop(); //移動停止()
    delay(200);
    moveBackward(); //後ろに移動()
    delay(800);
    moveStop();
    delay(200);
    distanceR = lookRight(); //距離R = 右に見て();
    delay(200);
    distanceL = lookLeft(); //距離L = 左を向く();
    delay(200);

    if(distanceR >= distanceL) //もし 距離R >= 距離L
    {
      turnRight(); //右に曲がる();
      moveStop(); 
    } else {
      turnLeft(); //左折してください();
      moveStop();
    }
    
  } else {
    moveForward(); //前進する();
  }
  
  distance = readPing();
}

int lookRight() //右に曲がる();
{
  myservo.write(50); //サーボをアングル50に設定
  delay(500);
  distance = readPing();
  delay(200);
  myservo.write(116); //サーボをアングル116に設定
  delay(500);
  return distance;
}

int lookLeft() //左を向く()
{
  myservo.write(171); //サーボをアングル171に設定
  delay(500); 
  distance = readPing();
  delay(200);
  myservo.write(116); //サーボをアングル116に設定
  return distance;
  delay(100);
}

//readPing 関数を作成する
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if(cm == 0){
    cm = 250;
  }
  return cm;
}

void moveStop() //移動停止()
{
  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
}

void moveForward() //前進する()
{
  if(!goesForward){
    goesForward = true;
    motor_1.run(FORWARD);
    motor_2.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor_1.setSpeed(speedSet);
      motor_2.setSpeed(speedSet+MAX_SPEED_OFFSET);
      delay(5);
    }
  }
}

void moveBackward() //後ろに移動()
{
  goesForward = false;
   motor_1.run(BACKWARD);
   motor_2.run(BACKWARD);
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor_1.setSpeed(speedSet);
    motor_2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
}

void turnRight() //右に曲がる()
{
  motor_1.run(FORWARD);
  motor_2.run(BACKWARD);
  delay(500);
  motor_1.run(FORWARD);
  motor_2.run(FORWARD);
}

void turnLeft() //左折してください()
{
  motor_1.run(BACKWARD);
  motor_2.run(FORWARD);
  delay(500);
  motor_1.run(FORWARD);
  motor_2.run(FORWARD);
}
