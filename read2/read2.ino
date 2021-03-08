#include <SoftwareSerial.h>
#include <math.h>
#include <Servo.h>

SoftwareSerial my_serial(10, 11);
Servo SB1;


int servo_pin = 4;
int pwm = 3;
int dir_pin = 8;

int flag = 0;

float data[2];

//float x = 0;
//float y = 0;
//float r = 0;

char char1[10];
float degree = 0;
float distance = 0;


int dir = 0;
int rc_degree = 0;
int power = 0;



void setup() {
  Serial.begin(57600);
  my_serial.begin(38400);

  SB1.attach(servo_pin);

  pinMode(pwm, OUTPUT);
  pinMode(dir_pin, OUTPUT);
}


void recvData(int i)
{

  byte m = my_serial.readBytesUntil(',', char1, 10);
  data[m] = '\0';
  data[i] = atof(char1);


  if (i == 0) {
    distance = data[i];
    Serial.print("distance=");
    Serial.println(data[i], 2);
  }
  if (i == 1)
  {
    degree = data[i];
    Serial.print("degree=");
    Serial.println(data[i], 2);
    Serial.println("=======================");
  }

}


void loop() {

  if (my_serial.available())
  {
    if (flag == 0)
    {
      recvData(0);
      flag = 1;
    }
    if (flag == 1)
    {
      recvData(1);
      flag = 0;
    }


    if (distance > 0.55) {
      if (degree < 75) {
        Serial.println('R');
        dir = 0;
        rc_degree = 140;
        power = 25;
      }

      else if (degree > 105) {
        Serial.println('L');
        dir = 0;
        rc_degree = 90;
        power = 25;
      }

      else if (degree >= 75 && degree <= 105) {
        Serial.println('F');
        dir = 0;
        rc_degree = 115;
        power = 25;
      }
    }

    else {
      Serial.println('S');
      dir = 0;
      rc_degree = 115;
      power  = 0;
    }


    SB1.write(rc_degree);
    digitalWrite(dir_pin, dir);
    analogWrite(pwm, power);

  }
}
