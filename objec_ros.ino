#include <Servo.h>
#include <ros.h>
#include <std_msgs/Int8.h>

Servo Myservo;
#define trigPin 9          // Trig Pin Of HC-SR04
#define echoPin 8          // Echo Pin Of HC-SR04
#define MLa 4              // left motor 1st pin
#define MLb 5              // left motor 2nd pin
#define MRa 6              // right motor 1st pin
#define MRb 7              // right motor 2nd pin

long duration, distance;

ros::NodeHandle nh;             // Instantiate the node handle to create publisher and subscriber
std_msgs::Int8 str_msg;         // Message object to hold ultrasonic sensor data
ros::Publisher chatter("chatter", &str_msg);  // Instantiate the publisher with the name chatter

void setup() {
  Serial.begin(9600);
  nh.initNode();                // Initialize the ROS node handle
  nh.advertise(chatter);        // Declare the topic "chatter"
  
  pinMode(MLa, OUTPUT);         // Set Motor Pins As O/P
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(trigPin, OUTPUT);     // Set Trig Pin As O/P To Transmit Waves
  pinMode(echoPin, INPUT);      // Set Echo Pin As I/P To Receive Reflected Waves
  
  Myservo.attach(10);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);      // Transmit Waves For 10us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // Receive Reflected Waves
  distance = duration / 58.2;        // Get Distance
  Serial.println(distance);
  
  // Publish ultrasonic sensor data
  str_msg.data = distance;
  chatter.publish(&str_msg);
  nh.spinOnce();
  
  delay(10);
  
  if (distance > 15) {  // Condition For Absence Of Obstacle
    Myservo.write(90);
    digitalWrite(MRb, HIGH);  // Move Forward
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, HIGH);
    digitalWrite(MLa, LOW);
  } else if ((distance < 10) && (distance > 0)) {  // Condition For Presence Of Obstacle
    digitalWrite(MRb, LOW);   // Stop
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(100);

    Myservo.write(0);
    delay(500);
    Myservo.write(180);
    delay(500);
    Myservo.write(90);
    delay(500);

    digitalWrite(MRb, LOW);   // Move Backward
    digitalWrite(MRa, HIGH);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, HIGH);
    delay(500);
    digitalWrite(MRb, LOW);   // Stop
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(100);
    digitalWrite(MRb, HIGH);  // Move Left
    digitalWrite(MRa, LOW);
    digitalWrite(MLa, LOW);
    digitalWrite(MLb, LOW);
    delay(500);
  }
}
