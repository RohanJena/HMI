#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include <SoftwareSerial.h>
int trig=0;
SoftwareSerial nxt(2, 3);
//SoftwareSerial sc(4, 5);
ros::NodeHandle nh;

void boolMsgCb(const std_msgs::Bool& msg) {
  if (msg.data) {
    setNextionText("trig","1");
  } else {
    setNextionText("trig","0");
  }
}

void taskMsgCb(const std_msgs::String& msg) {
  String receivedString = String(msg.data);
  int index1 = receivedString.indexOf(',');
  int index2 = receivedString.indexOf(',', index1 + 1);
  int index3 = receivedString.indexOf(',', index2 + 1);
  int index4 = receivedString.indexOf(',', index3 + 1);

  String component1 = receivedString.substring(0, index1);
  String component2 = receivedString.substring(index1 + 1, index2);
  String component3 = receivedString.substring(index2 + 1, index3);
  String component4 = receivedString.substring(index3 + 1, index4);
  String component5 = receivedString.substring(index4 + 1);
//  if(component1=="1"){
//    setNextionText("trig","1");
//  }
//  else{
//    setNextionText("trig","0");
//  }
  setNextionText("tsk", component1);
  setNextionText("sta", component2);
  setNextionText("itm", component3);
  setNextionText("bat", component4);
  setNextionText("dist", component5);
  
}
  

ros::Subscriber<std_msgs::Bool> boolSub("trig_topic", &boolMsgCb);
ros::Subscriber<std_msgs::String> taskSub("task_topic", &taskMsgCb);
ros::Publisher pub("task_trig_topic", new std_msgs::Bool);


void setup() {
  Serial.begin(9600);  // For Serial Monitor
  nh.initNode();
  nh.subscribe(boolSub);
  nh.subscribe(taskSub);
  nh.advertise(pub);
  nxt.begin(9600); 
//  sc.begin(115200);
}

void loop() {
  nh.spinOnce();
  readNextionButton();
  delay(1);
}

void readNextionButton() {
  std_msgs::Bool msg;
  if (nxt.available()) {
    int buttonValue = nxt.read();  // Read as an integer
    if (buttonValue != -1) {  // Check if a valid value is received
      if(buttonValue <= 1){
        msg.data = 1;
      }
      else{
        msg.data = 0;
      }
      pub.publish(&msg);
      nh.spinOnce();
    } else {
      msg.data = 0;
      pub.publish(&msg);
      nh.spinOnce();
    }
  }
}

void setNextionText(String component, String text) {
  String command = component + ".txt=\"" + text + "\"";
  sendNextionCommand(command);
}

void sendNextionCommand(String command) {
  nxt.print(command);
  nxt.write(0xFF);
  nxt.write(0xFF);
  nxt.write(0xFF);
  delay(1);
}
