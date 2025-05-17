#include <Servo.h>

// IR sensors
const int IR_L = 2;
const int IR_R = 3;

// Motor A (Left)
const int speed_motor = 150;
const int IN1 = 8;
const int IN2 = 9;

// Motor B (Right)
const int IN3 = 10;
const int IN4 = 11;

// Sonar (HC-SR04)
const int trigPin = 6;
const int echoPin = 7;

// Servo
const int servoPin = 12;
Servo myServo;

// TCS3200 Color Sensor Pins
const int S0 = 4;
const int S1 = 5;
const int S2 = A3;
const int S3 = A4;
const int sensorOut = A5;

// Color LEDs
const int greenLED = A0;
const int blueLED = A1;
const int redLED = A2;

void setup() {
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);  // 20% scaling
  digitalWrite(S1, LOW);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  turnOffAllLEDs();

  myServo.attach(servoPin);
  myServo.write(180);  // Initial position

  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();

  if (distance <= 5) {
    Serial.print("Obstacle at ");
    Serial.print(distance);
    Serial.println(" cm. Stopping.");

    stopMotors();
    delay(5000);  // Let robot settle

    detectColor();  // Color action
    return;
  }

  int left = digitalRead(IR_L);
  int right = digitalRead(IR_R);

  if (left == LOW && right == LOW) {
    moveForward();
  } else if (left == LOW && right == HIGH) {
    turnRight();  // correct for left drift
  } else if (left == HIGH && right == LOW) {
    turnLeft();   // correct for right drift
  } else {
    stopMotors();
  }
}

// ----------------- Distance Sensor -----------------
int getDistance() {
  stopMotors();
  delay(50);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999;

  int distance = duration * 0.034 / 2;
  return distance;
}

// ----------------- Color Detection -----------------
void detectColor() {
  int red = readColor(LOW, LOW);       // Red
  int green = readColor(HIGH, HIGH);   // Green
  int blue = readColor(LOW, HIGH);     // Blue

  Serial.print("R= ");
  Serial.print(red);
  Serial.print(" G= ");
  Serial.print(green);
  Serial.print(" B= ");
  Serial.println(blue);

  if (red < green && red < blue) {
    Serial.println("Detected Color: Red");
    digitalWrite(redLED, HIGH);
    myServo.write(90);
    delay(1000);
    myServo.write(180);
    delay(5000);
  } else if (green < red && green < blue) {
    Serial.println("Detected Color: Green");
    digitalWrite(greenLED, HIGH);
    myServo.write(90);
    delay(1000);
    myServo.write(180);
    delay(5000);
  } else if (blue < red && blue < green) {
    Serial.println("Detected Color: Blue");
    digitalWrite(blueLED, HIGH);
    myServo.write(90);
    delay(1000);
    myServo.write(180);
    delay(5000);
  } else {
    Serial.println("Color is unclear.");
  }

  turnOffAllLEDs();
}

// ----------------- Color Sensor Frequency -----------------
int readColor(int s2, int s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(10);  // Allow sensor to settle
  return pulseIn(sensorOut, LOW);
}

// ----------------- LED Utility -----------------
void turnOffAllLEDs() {
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
}

// ----------------- Motor Functions -----------------
void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(10);
}

//
//void moveForward() {
//  Serial.println("Moving Forward");
//  analogWrite(IN1, LOW);
//  analogWrite(IN2, speed_motor);
//  analogWrite(IN3, LOW);
//  analogWrite(IN4, speed_motor);
//  delay(10);
//}

void turnLeft() {
  Serial.println("Turning Left");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(30);
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(30);
}

void stopMotors() {
  Serial.println("Stopping");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
