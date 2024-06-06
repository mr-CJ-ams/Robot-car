const int irPin1 = A3;
const int irPin2 = A2;
const int sensorPin = A0; 
const int analogPin1 = A4; // Define the analog pin you're using
const int analogPin2 = A5;

// if switchPin is less than the thresholdSwitch, the switchPin is LOW, else HIGH
int thresholdSwitch = 512; 
int irThreshold = 500;


#define MOTOR_SPEED_BASE 80 //80 // Base motor speed (minimum speed)
#define MIN_ATK_SPEED 100 //150
#define MIN_ATK_SPEED_SUMO 100//100
#define FULL_ATK_SPEED 255 // Maximum attack motor speed

const int ultraRightEcho = 10;
const int ultraRightTrig = 11;

const int ultraLeftEcho = 4;
const int ultraLeftTrig = 2;

const int ultraFrontEcho = 8;
const int ultraFrontTrig = 9;

// Left motor
int enableRightMotor = 5;
int rightMotorPin1 = 7;
int rightMotorPin2 = 6;

// Right motor
int enableLeftMotor = 3;
int leftMotorPin1 = 12;
int leftMotorPin2 = 13;

int timeInMicro;
int distanceInCm;

bool measureDistance = true;

void setup() {
  Serial.begin(9600);
  pinMode(ultraRightTrig, OUTPUT);
  pinMode(ultraRightEcho, INPUT);
  pinMode(ultraLeftTrig, OUTPUT);
  pinMode(ultraLeftEcho, INPUT);
  pinMode(ultraFrontTrig, OUTPUT);
  pinMode(ultraFrontEcho, INPUT);
  delay(5000);
}

void loop() {
  int switchPin1  = analogRead(analogPin1); // Read the analog input
  int switchPin2  = analogRead(analogPin2);


  if (switchPin1 > thresholdSwitch && switchPin2 < thresholdSwitch) { // Define your threshold here (512 is halfway for a 10-bit ADC)
    // --------------------------------SUMOBOT --------------------------------------------------------------------------------------------------------------
    int IR1 = analogRead(irPin1);
    int IR2 = analogRead(irPin2);
    int ltValue = analogRead(sensorPin);
    int distanceUltraFront = measureDistanceCentimeters(ultraFrontTrig, ultraFrontEcho);

    Serial.print("Front: ");
    Serial.print(distanceUltraFront);
    Serial.println(" cm");

    // rotateMotor(200, -200);
    if (distanceUltraFront > 35){
      rotateMotor(120, -120);
      Serial.print("Turn ");
      if (IR1 < irThreshold || IR2 < irThreshold) {
        rotateMotor(-FULL_ATK_SPEED, -FULL_ATK_SPEED);
        delay(400);
      }
      else if (ltValue < irThreshold) {
        rotateMotor(MIN_ATK_SPEED, MIN_ATK_SPEED);
        delay(600);
      }
    }
    else if (distanceUltraFront <= 35 && distanceUltraFront > 13) {
      rotateMotor(MIN_ATK_SPEED_SUMO, MIN_ATK_SPEED_SUMO);
      Serial.print("Attack ");
      if (IR1 < irThreshold || IR2 < irThreshold) {
        rotateMotor(-FULL_ATK_SPEED, -FULL_ATK_SPEED);
        delay(400);
      }
      else if (ltValue < irThreshold) {
        rotateMotor(MIN_ATK_SPEED, MIN_ATK_SPEED);
        delay(600);
      }
    }
     else if (distanceUltraFront <= 13 && distanceUltraFront > 0) {
      rotateMotor(FULL_ATK_SPEED, FULL_ATK_SPEED);
      Serial.print("Attack Bugha ");
      if (IR1 < irThreshold || IR2 < irThreshold) {
        rotateMotor(-FULL_ATK_SPEED, -FULL_ATK_SPEED);
        delay(400);
      }
      else if (ltValue < irThreshold) {
        rotateMotor(MIN_ATK_SPEED, MIN_ATK_SPEED);
        delay(600);
      }
    } 
    else if (IR1 < irThreshold || IR2 < irThreshold) {
      rotateMotor(-FULL_ATK_SPEED, -FULL_ATK_SPEED);
      delay(400);
    }
    else if (ltValue < irThreshold) {
        rotateMotor(MIN_ATK_SPEED, MIN_ATK_SPEED);
        delay(600);
    }

  } 
  else if (switchPin1 < thresholdSwitch && switchPin2 > thresholdSwitch) {

    // Serial.println("PATHFINDER");
    // --------------------------------PATHFINDER -----------------------------------------------------------------------------------------------------------
    int distanceUltraRight = 0;
    int distanceUltraLeft = 0;
    int distanceUltraFront = 0;

    if (measureDistance) {
      distanceUltraRight = measureDistanceCentimeters(ultraRightTrig, ultraRightEcho);
      distanceUltraLeft = measureDistanceCentimeters(ultraLeftTrig, ultraLeftEcho);
      distanceUltraFront = measureDistanceCentimeters(ultraFrontTrig, ultraFrontEcho);

      Serial.print("Right: ");
      Serial.print(distanceUltraRight);
      Serial.println(" cm");

      Serial.print("Left: ");
      Serial.print(distanceUltraLeft);
      Serial.println(" cm");

      Serial.print("Front: ");
      Serial.print(distanceUltraFront);
      Serial.println(" cm");
    }
  
    if ((distanceUltraRight <= 40 ) && (distanceUltraLeft <= 40 ) && distanceUltraFront > 30) {
      Serial.println(" FORWARD  ");
      // rotateMotor(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);
      // Calculate error (difference between left and right distances)
      int error = distanceUltraRight - distanceUltraLeft;

      // Declare motor speeds variables
      int leftMotorSpeed;
      int rightMotorSpeed;
      
      // Determine which side is closer to the obstacle
      int motorSpeedAdjustment = 0;

      if (error > 0) {
        motorSpeedAdjustment = error * 1.5; // Proportional gain for left motor
        // Calculate left and right motor speeds
        leftMotorSpeed = MOTOR_SPEED_BASE + motorSpeedAdjustment;
        rightMotorSpeed = MOTOR_SPEED_BASE - motorSpeedAdjustment;
      } else if (error < 0) {
        motorSpeedAdjustment = error * -1.5; // Proportional gain for right motor
        // Calculate left and right motor speeds
        leftMotorSpeed = MOTOR_SPEED_BASE - motorSpeedAdjustment;
        rightMotorSpeed = MOTOR_SPEED_BASE + motorSpeedAdjustment;
      }
      
      // // Apply speed limits
      leftMotorSpeed = constrain(leftMotorSpeed, 65, FULL_ATK_SPEED);
      rightMotorSpeed = constrain(rightMotorSpeed, 65, FULL_ATK_SPEED);
      
      // Apply motor speeds
      rotateMotor(rightMotorSpeed, leftMotorSpeed);
      
    } 


    
    else if (distanceUltraRight > 40 || distanceUltraLeft > 40) { 

      if (distanceUltraFront <= 10){
        Serial.println(" Back  ");
        rotateMotor(0, 0);
        delay(500);
        measureDistance = false;
        rotateMotor(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
        delay(400);
        measureDistance = true;
      }


      if ( ((distanceUltraRight > distanceUltraLeft) && (distanceUltraRight > distanceUltraFront))) {
        // Serial.print("---------------------------------\n");

        Serial.println(" RIGHT  ");
        rotateMotor(0, 0);
        delay(800);
        measureDistance = false;
        rotateMotor(-MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);
        delay(385);
        rotateMotor(0, 0);
        delay(1000);
        rotateMotor(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);
        delay(900);
        measureDistance = true;
      }


      // Turn Left
      else if ( ((distanceUltraLeft > distanceUltraRight) && (distanceUltraLeft > distanceUltraFront)) ) {
        Serial.println(" LEFT  ");
        rotateMotor(0, 0);
        delay(300);
        measureDistance = false;
        rotateMotor(MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
        delay(250);
        rotateMotor(0, 0);
        delay(1000);
        rotateMotor(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);
        delay(700);
        measureDistance = true;
      } 
      // Move straight to the front
      else if (((distanceUltraFront > distanceUltraRight) && (distanceUltraFront > distanceUltraLeft)) ) {
        rotateMotor(0, 0);
        delay(300);
        measureDistance = false;
        rotateMotor(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);
        delay(900);
        measureDistance = true;
        
      } 
    } 
    
    else if ((distanceUltraRight < 40 ) && (distanceUltraLeft < 40 ) && (distanceUltraFront <= 25 && distanceUltraFront > 10)){
      Serial.println(" U turn  ");
      rotateMotor(0, 0);
      delay(500);
      measureDistance = false;
      rotateMotor(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
      delay(500);
      rotateMotor(MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
      delay(550);
      rotateMotor(0, 0);
      delay(1000);
      // rotateMotor(MOTOR_SPEED_BASE, MOTOR_SPEED_BASE);
      // delay(300);
      measureDistance = true;
    }

    else if ((distanceUltraRight < 40 ) && (distanceUltraLeft < 40 ) && ( distanceUltraFront <= 10)){
      Serial.println(" Back  ");
      rotateMotor(0, 0);
      delay(500);
      measureDistance = false;
      rotateMotor(-MOTOR_SPEED_BASE, -MOTOR_SPEED_BASE);
      delay(400);
      measureDistance = true;
    }

  
    
  }
}


float measureDistanceCentimeters(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH, 20000);
  int distance_cm = duration * 0.034 / 2;
  return distance_cm;
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed ) {
  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed >= 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }

  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH); 
  } else if (rightMotorSpeed >= 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
}

