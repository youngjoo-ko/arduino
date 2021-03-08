
#include<SoftwareSerial.h>

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/Float64MultiArray.h>


SoftwareSerial my_serial(10,11);
ros::NodeHandle  nh;

float data[2];


void msg_cb(const std_msgs::Float64MultiArray& min_obj_msg){
    data[0] = min_obj_msg.data[0];
    data[1] = min_obj_msg.data[1];
    
    my_serial.print(data[0], 6);
    my_serial.print(',');
    my_serial.print(data[1], 6);
    my_serial.print(',');
  }


ros::Subscriber<std_msgs::Float64MultiArray> sub("min_position",&msg_cb);


void setup() {
  my_serial.begin(38400); 
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {

  
  nh.spinOnce();
  delay(10);
 


}
