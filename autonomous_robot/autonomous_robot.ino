#include <Servo.h>
#include <SharpIR.h>

// define servos and input pins
Servo leftWheel, rightWheel;
int leftPin=6, rightPin=5;

// define model and input pin
#define IRPin A0
#define model 1080 //GP2Y0A21YK0F --> 1080

// create new instance of the SharpIR class
SharpIR sensor1=SharpIR(A0, 1080);
SharpIR sensor2=SharpIR(A1, 1080);

// create variable to store the distance in cm
int distance1; //for sensor 1 (in the front)
int distance2; //for sensor 2 (on the right side)

void setup() {
  // put your setup code here, to run once:

  // begin serial communication at a baudrate of 9600
  Serial.begin(9600); 

  //attach and write stopped servos
  leftWheel.attach(leftPin);
  rightWheel.attach(rightPin);
  leftWheel.write(65);
  rightWheel.write(160);
}

// individual (left, right) wheel movements (to be included in later methods)
void leftAnticlockwise(){
  leftWheel.write(180);
}

void leftClockwise(){
  leftWheel.write(0);
}

void rightAnticlockwise(){
  rightWheel.write(180);
}

void rightClockwise(){
  rightWheel.write(0);
}

void rightStop(){
  rightWheel.write(160);
}

void leftStop(){
  leftWheel.write(65);
}

// synchronous wheel movements (forward, backward)
void forward(int steps){
  for(int i=0;i<steps;i++){
    leftAnticlockwise();
    rightClockwise();
  }
}

void backward(int steps){
  for(int i=0;i<steps;i++){
    leftClockwise();
    rightAnticlockwise();
  }
}

// synchronous wheel movements (turning) 
//not sure if I actually need these methods though
void turnLeft(){
  for(int i=0;i<10;i++){
    leftAnticlockwise();
  }
}

void turnRight(){
  for(int i=0;i<10;i++){
    rightClockwise();
  }
}

void loop() {
  // put your main code here, to run repeatedly:  
  
  // get distance measurements and store them
  distance1=sensor1.distance(); 
  distance2=sensor2.distance();
  
  // print measured distances to serial monitor (CTRL+Shift+M)
  Serial.print("Sensor 1 Mean Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Sensor 2 Mean Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");
  delay(1000);

  // NOTE: here's the code for moving the robot in a continuous square:
  // forward(10); delay(3000); stopLeft(); delay(2400)

  // movement based on distance on serial monitor
  if (distance1>30.48){ //30.48 cm = 1 foot
    forward(10);
    delay(3000); // will need to adjust either delay time or the max/closest distance after testing
  }
  else if (distance1<=30.48 and distance2<=30.48){
    leftStop();
  } 
  else if (distance1<=30.48 and distance2>30.48){
    rightStop();
  }
  else{
    backward(10);
  }
}
