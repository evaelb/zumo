#include <Wire.h>
#include <ZumoShield.h>


//Motor
ZumoMotors motors;

//Reflectance Sensor
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
#define Mark_qtr  1500 

ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

//Distance
#define echoPin 1 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

const int numReadings = 10;

//averaging
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;


void setup()
{
 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3"); 
}



void loop()
{



  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  delay(1);        // delay in between reads for stability
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  sensors.read(sensor_values);

  if ((sensor_values[0] < Mark_qtr) or (sensor_values[5] < Mark_qtr)){
    if (sensor_values[0] < Mark_qtr) 
    {
      
      motors.setLeftSpeed(-200);
      motors.setRightSpeed(-200);
      delay(200);
      motors.setLeftSpeed(200);
      motors.setRightSpeed(-200);
      delay(300);
      motors.setLeftSpeed(200);
      motors.setRightSpeed(200);
    }
    else if (sensor_values[5] < Mark_qtr)
    {
      
      motors.setLeftSpeed(-200);
      motors.setRightSpeed(-200);
      delay(200);
      motors.setLeftSpeed(-200);
      motors.setRightSpeed(200);
      delay(300);
      motors.setLeftSpeed(200);
      motors.setRightSpeed(200);
  
    }
  }
  /*
  else if (distance < 4)
  {
    
    //if distance is less than 4cm, go faster
    if (sensor_values[0] < Mark_qtr) 
    {
      
      motors.setLeftSpeed(-200);
      motors.setRightSpeed(-200);
      delay(200);
      motors.setLeftSpeed(200);
      motors.setRightSpeed(-200);
      delay(300);
      motors.setLeftSpeed(200);
      motors.setRightSpeed(200);
    }
    else if (sensor_values[5] < Mark_qtr)
    {
      
      motors.setLeftSpeed(-200);
      motors.setRightSpeed(-200);
      delay(200);
      motors.setLeftSpeed(-200);
      motors.setRightSpeed(200);
      delay(300);
      motors.setLeftSpeed(200);
      motors.setRightSpeed(200);
  
    }
    else
    {
    motors.setLeftSpeed(400);
    motors.setRightSpeed(400);
   delay(200);
  }
}*/
  else
  {
    // otherwise, go straight
    motors.setLeftSpeed(300);
    motors.setRightSpeed(300);
  }

}
