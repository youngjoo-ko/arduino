#include<SoftwareSerial.h>

SoftwareSerial my_serial(10,11);

float data[3];

char char1[10];
int flag = 0;
float degree = 0.0;
float x = 0.0;
float y = 0.0;
float distance = 0.0;



void setup() {
  Serial.begin(57600);
  my_serial.begin(38400);

}



void recvData(int i)
{
  byte m = my_serial.readBytesUntil(',', char1, 10);
  //data[m] = '\0';
  data[i] = atof(char1);

  
  if (i == 0){
    x = data[i];
    Serial.print("x=");
    Serial.println(data[i], 2);
  }
  if (i == 1)
  {
    y = data[i];
    Serial.print("(x,y)=");
    Serial.print(" (");
    Serial.print(x, 2);
    Serial.print(" , ");
    Serial.print(y, 2);
    Serial.println(") ");
    
  }
  if (i == 2)
  {
    Serial.print("radian=");
    Serial.println(data[i], 2);
    degree = data[i]* 57.295792;
    Serial.print("degree=");
    Serial.println(degree, 2);
    distance = sqrt((x*x) + (y*y));
    Serial.print("distance=");
    Serial.println(distance, 2);   
    Serial.println("=======================");
  }
    }




void loop() {
 
 if(my_serial.available())
  { 
    if(flag == 0)
    {
      recvData(0);
      flag = 1;
    }
    if(flag==1)
    {
      recvData(1);
      flag = 2;
    }
    if(flag==2)
    {
      recvData(2);
      flag = 0;
    }
    
    //Serial.println("=======================");
  }
  
}



      
 
