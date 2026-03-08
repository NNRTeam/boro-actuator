#include <Arduino.h>
#include <Config.h>
#include <Logger.h>
#include <ColorSensor.h>
#include <Deployer/ActuatorDeployer.h>
#include <ActuatorStateMachine/ActuatorStateMachine.h>

Logger logger(Logger::Level::INFO, "Main");
ActuatorDeployer actuatorDeployer;
ActuatorStateMachine* actuatorStateMachine;

void setup() {
    Serial.begin(config::SERIAL_BAUDRATE);
    actuatorStateMachine = actuatorDeployer.deployActuators();
}

void loop() {
    actuatorStateMachine->run();
}



// #include <Servo.h>

// #define enable 2

// #define stp1 4
// #define dir1 7

// #define stp2 8
// #define dir2 12

// #define  home1 14
// #define home2 15

// Servo srv1;  // create Servo object to control a servo
// Servo srv2;  // create Servo object to control a servo

// Servo srv3;
// Servo srv4;


// Servo srv5;
// Servo srv6;

// void setup() {
//   srv1.attach(3);  // attaches the servo on pin 9 to the Servo object
//   srv2.attach(5);  // attaches the servo on pin 9 to the Servo object

//   srv3.attach(6);  // attaches the servo on pin 9 to the Servo object
//   srv4.attach(9);  // attaches the servo on pin 9 to the Servo object

//   srv5.attach(10);  // attaches the servo on pin 9 to the Servo object
//   srv6.attach(11);  // attaches the servo on pin 9 to the Servo object


//     srv1.write(100);                  // sets the servo position according to the scaled value
//   srv2.write(50);  // attaches the servo on pin 9 to the Servo object

//   srv3.write(0);
//   srv4.write(180);

//   srv5.write(90);
//   srv6.write(90);


//   pinMode(enable, OUTPUT);
//   pinMode(stp1, OUTPUT);
//   pinMode(dir1, OUTPUT);
//   pinMode(stp2, OUTPUT);
//   pinMode(dir2, OUTPUT);

//   pinMode(home1, INPUT);
//   pinMode(home2, INPUT);


//     digitalWrite(dir1, HIGH);
//   digitalWrite(dir2, LOW);
//   while(!digitalRead(home1))
//   {
//       digitalWrite(stp1, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       delay(4);
//   }
//     while(!digitalRead(home2))
//   {
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }

//   digitalWrite(dir1, LOW);
//   digitalWrite(dir2, HIGH);
//   for (int i = 0; i < 460; i++)
//   {
//       digitalWrite(stp1, HIGH);
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }
// }

// void loop() {

//   delay(7000);
//   srv1.write(70);                  // sets the servo position according to the scaled value
//   srv2.write(80);  // attaches the servo on pin 9 to the Servo object
//   delay(300);                           // waits for the servo to get there
//   srv3.write(0);
//   srv4.write(180);
//   digitalWrite(dir1, HIGH);
//   digitalWrite(dir2, LOW);
//   for (int i = 0; i < 100; i++)
//   {
//       digitalWrite(stp1, HIGH);
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }
//   srv3.write(180);
//   srv4.write(0);
//   delay(1000);

//   digitalWrite(dir1, LOW);
//   digitalWrite(dir2, HIGH);
//   for (int i = 0; i < 80; i++)
//   {
//       digitalWrite(stp1, HIGH);
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }

//   // CHECK DE LA COULEUR
//   delay(400);
//   srv3.write(180);
//   srv4.write(0);
//   delay(400);
//       srv5.write(70);
//   srv6.write(110);
//   delay(1000);

//   digitalWrite(dir1, HIGH);
//   digitalWrite(dir2, LOW);
//   for (int i = 0; i < 440; i++)
//   {
//       digitalWrite(stp1, HIGH);
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }

//     delay(400);

//   srv5.write(180);
//   srv6.write(0);
//   delay(1000);

//     srv1.write(100);                  // sets the servo position according to the scaled value
//   srv2.write(50);  // attaches the servo on pin 9 to the Servo object
//   delay(500);

//   digitalWrite(dir1, LOW);
//   digitalWrite(dir2, HIGH);
//   for (int i = 0; i < 200; i++)
//   {
//       digitalWrite(stp1, HIGH);
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }
//     srv3.write(0);
//   srv4.write(180);
//     for (int i = 0; i < 260; i++)
//   {
//       digitalWrite(stp1, HIGH);
//       digitalWrite(stp2, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stp1, LOW);
//       digitalWrite(stp2, LOW);
//       delay(4);
//   }
// }