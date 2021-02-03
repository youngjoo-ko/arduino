#include<SoftwareSerial.h>

SoftwareSerial my_serial(2,3);


float data[2];
char char1[10];
bool flag = false;



void setup() {
  Serial.begin(57600);
  my_serial.begin(57600);

}

void recvData(int i)
{
  byte m = my_serial.readBytesUntil(',', char1, 10);
  data[m] = '\0';
  //Serial.println(char1);
  data[i] = atof(char1);
  if (i == 0){
    Serial.print("x=");
    Serial.println(data[i], 6);
  }
  if (i == 1)
  {
    Serial.print("y=");
    Serial.println(data[i], 6);
    Serial.println("=======================");
  }
    }




void loop() {
 
 if(my_serial.available())
  { 
    if(flag == false)
    {
      recvData(0);
      flag = true;
    }
    else
    {
      recvData(1);
      flag = false;
    }
    
  }
}



      
 
