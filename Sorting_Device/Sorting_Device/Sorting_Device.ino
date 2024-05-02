// AUTHOR : Christianus Yanuar Instagram : @__cece14
#include <Servo.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

Servo colorServo; // Creating an object of the Servo class for color control
Servo doorServo;  // Creating an object of the Servo class for door control

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red, green, and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

const int doorOpenAngle = 90;  // Angle for open door
const int doorClosedAngle = 0; // Angle for closed door

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Attaching color control servo to pin 9
  colorServo.attach(9);
  // Attaching door control servo to pin 10
  doorServo.attach(10);
  
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remapping the value of the RED (R) frequency from 0 to 255
  redColor = map(redFrequency, 39, 103, 0, 180); // Mapping the frequency to servo angle
  
  // Moving color control servo to the angle according to red color
  colorServo.write(10); // Angle 10° if red color is detected
  
  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remapping the value of the GREEN (G) frequency from 0 to 255
  greenColor = map(greenFrequency, 61, 109, 0, 180); // Mapping the frequency to servo angle
  
  // Moving color control servo to the angle according to green color
  colorServo.write(90); // Angle 90° if green color is detected
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remapping the value of the BLUE (B) frequency from 0 to 255
  blueColor = map(blueFrequency, 38, 125, 0, 180); // Mapping the frequency to servo angle
  
  // Moving color control servo to the angle according to blue color
  colorServo.write(180); // Angle 180° if blue color is detected
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);

  // Checks the current detected color and prints
  // a message in the serial monitor
  if (redColor > greenColor && redColor > blueColor) {
    Serial.println(" - RED detected!");
    openDoor();  // Open the door if red color is detected
    delay(5000); // Wait 5 seconds after opening the door
  }
  else if (greenColor > redColor && greenColor > blueColor) {
    Serial.println(" - GREEN detected!");
    openDoor();  // Open the door if green color is detected
    delay(5000); // Wait 5 seconds after opening the door
  }
  else if (blueColor > redColor && blueColor > greenColor) {
    Serial.println(" - BLUE detected!");
    openDoor();  // Open the door if blue color is detected
    delay(5000); // Wait 5 seconds after opening the door
  }
  else {
    closeDoor(); // Close the door if no color is detected
    delay(5000); // Wait 5 seconds after closing the door
  }
}

// Function to open the door
void openDoor() {
  doorServo.write(doorOpenAngle);  // Move door control servo to open angle
}

// Function to close the door
void closeDoor() {
  doorServo.write(doorClosedAngle);  // Move door control servo to closed angle
}
