#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50
#define SERVO_MIN 100
#define SERVO_MAX 470

#define SERVO_CENTER (SERVO_MIN + SERVO_MAX) / 2


void setup() {
  Serial.begin(9600);
  Serial.println("Booting.");
  Serial.println("PWM servo driver initialization.");
  pwm.begin();
  pwm.setOscillatorFrequency(27000000); //TODO - needs some calibration for PCA9685 (int.osc. around 23-27MHZ)
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
  Serial.println("Boot finished.");
}


int dir = 1;
int current = 90;

int servoHip = 2;
int servoLeg = 1;
int servoTip = 0;

int range = SERVO_MAX-SERVO_MIN;
int speed = 15;


void loop_a() {
  pwm.setPWM(15, 0, SERVO_MIN); // 80 - 470
}

int degToServo(int degree) {
  return (int) map(degree, 0, 180, SERVO_MIN, SERVO_MAX);
}

void setServo(int servo, int degrees) {
  pwm.setPWM(servo, 0, degToServo(degrees));
}

void loop() {
  current = 0;
  setServo(servoTip,60);
  setServo(servoLeg, 115);
  setServo(15, current);
}

void loop_5() {
  //setServo(servoHip, 90);
  // setServo(servoLeg, 0);
  // setServo(servoTip, 0);
  // setServo(servoHip, 45);

  current += dir * speed;

  if (current < 0) {
    current = 0;
    dir = 1;
  }
  if (current > 180) {
    current = 180;
    dir = -1;
  }
  current = 360;
  setServo(servoHip, 135);
  setServo(servoLeg, 45);
  setServo(servoTip, 25);
  setServo(15, current);
  //setServo(servoTip, 90);
  delay(1000);

  //setServo(servoHip, 135);
  setServo(servoLeg, 0);
  setServo(servoTip, 0);
  setServo(15, current);
  delay(1000);
  
  setServo(servoHip, 45);
  delay(1000);

  setServo(servoLeg, 45);
  setServo(servoTip, 25);
  delay(1000);

  setServo(servoHip, 135);
  delay(1000);

  // setServo(servoHip, 90);
  // setServo(servoLeg, 45);
  // setServo(servoTip, 0);
  // setServo(15, current);
}



void loop_4() {
  current += dir; // * speed;
  if (current < 0) {
    current = 0;
    dir = 1;
  }
  if (current > 180) {
    current = 180;
    dir = -1;
  }
  pwm.setPWM(15, 0, degToServo(current));
  delay(5);
}


void loop_3() {
  pwm.setPWM(15, 0, SERVO_CENTER); // 80 - 470
  delay(1000);
  pwm.setPWM(15, 0, SERVO_MIN); // 80 - 470
  delay(1000);
  pwm.setPWM(15, 0, SERVO_CENTER); // 80 - 470
  delay(1000);
  pwm.setPWM(15, 0, SERVO_MAX); // 80 - 470
  delay(1000);
}





void loop_2() {
  // put your main code here, to run repeatedly:
  //pwm.setPWM(servoHip, 0, SERVO_MIN + range/2);
  //pwm.setPWM(servoLeg, 0, SERVO_MIN + range/2);
  current = current + dir * speed;
  if (current > range) {
    current = range;
    dir = -1;
    Serial.println("Maximum reached, turning around...");
  }
  if (current < 0) {
    current = 0;
    Serial.println("Minimum reached, turning around...");
    dir = 1;
  }
  Serial.print("Current "); Serial.println(current);
  pwm.setPWM(servoLeg, 0, SERVO_MIN + current);
  pwm.setPWM(servoTip, 0, SERVO_MAX - current);
  pwm.setPWM(servoHip, 0, SERVO_MIN + current - 50);
  delay(15);
}


