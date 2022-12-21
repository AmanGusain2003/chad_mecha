// This code has movement of the motor in it.

#include <Servo.h>

// All pins
const int motor_pin1 = 8; // move grip forward
const int motor_pin2 = 7; // move grip reverse
const int servo_pin = 9;
const int pulley_pin1 = 10;        // move pulley down
const int pulley_pin2 = 11;        // move pulley up
const int pulley_pin3 = 6;        // move pulley up
const int pulley_pin4 = 5;        // move pulley up

const int motor_move_robot1 = 13; // move the robot forward * 
const int motor_move_robot2 = 12; // move the robot backward
const int ultrasonic1_trig = 22; //forward ultrasonic trig 
const int ultrasonic1_echo = 23; //forward ultrasonic echo
const int ultrasonic2_trig = 53; //backward ultrasonic trig
const int ultrasonic2_echo = 52; //backward ultrasonic echo

//*****
// some values
const int forward_delay = 2300; // delay required for moving the grip motors forward.
const int pulley_delay = 2000;  // delay required to completely pull pulley down or up.
const int servo_low = 80;       // servo low limit for the claw
const int servo_high = 120;     // servo high limit for the claw
const int claw_speed = 20;      // decrease the value to increase the claw speed
const int safe_distance = 30;   // safe distance for the ultrasonic (in cm)
//***

Servo servo1;

void setup()
{
    pinMode(motor_pin1, OUTPUT);
    pinMode(motor_pin2, OUTPUT);
    pinMode(ultrasonic1_echo, INPUT);
    pinMode(ultrasonic1_trig, OUTPUT);
    pinMode(ultrasonic2_echo, INPUT);
    pinMode(ultrasonic2_trig, OUTPUT);
    pinMode(motor_move_robot1, OUTPUT);
    pinMode(motor_move_robot2, OUTPUT);
    pinMode(pulley_pin1, OUTPUT);
    pinMode(pulley_pin2, OUTPUT);
    servo1.attach(servo_pin);
    Serial.begin(9600);
    while (!Serial)
    {
    }
    servo1.write(servo_low);
    digitalWrite(motor_pin1, LOW);
    digitalWrite(motor_pin2, LOW);
    digitalWrite(motor_move_robot1, LOW);
    digitalWrite(motor_move_robot2, LOW);
    digitalWrite(pulley_pin1, LOW);
    digitalWrite(pulley_pin2, LOW);


}
void loop()
{
  int distance = get_distance(ultrasonic2_echo,ultrasonic2_trig);

  Serial.println(distance);
    move_grip_motor(1);
    grip(1);
    move_grip_motor(2);
//    grip(2);
    move_pulley(1);
    move_robot(1);
    move_pulley(2);
    move_grip_motor(1);
    grip(2);
    move_grip_motor(2);
    move_pulley(2);
    move_robot(2);
    Serial.println("Demo ended.");
    while (1);

    
}

//**********All Functions******

int get_distance(int echo_pin, int trig_pin) // pass ultrasonic pins to get the distance
{
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echo_pin, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2;
    return distance;
}

void move_robot(int i)   // pass 1 to move forward, pass 2 to move backward
{
    Serial.println("Moving robot");
    bool move = true;

    if (i == 1)
    {
        while (move)
        {

            int distance = get_distance(ultrasonic2_echo, ultrasonic2_trig);
            if (distance >= safe_distance)
            {
                analogWrite(motor_move_robot1, 170);
            }
            else{
                digitalWrite(motor_move_robot1, LOW);
                move = false;
                delay(10);
            }
        }
    }

    else if (i == 2)
    {
        while (move)
        {
            int distance = get_distance(ultrasonic2_echo, ultrasonic2_trig);
            if (distance >= safe_distance)
            {
                analogWrite(motor_move_robot2, 170);
            }
            else{
                digitalWrite(motor_move_robot2, LOW);
                move = false;
                delay(10);
            }
        }
    }
}

void move_grip_motor(int i)   // pass 1 for forward, 2 for backward
{ 
    Serial.print("Running Motor ");
    Serial.println(i);
    if (i == 1)
    { // move forward
        analogWrite(motor_pin1, 70);
        delay(forward_delay - 500);
        analogWrite(motor_pin1, 0);
    }
    else if (i == 2)
    { // move backward
        analogWrite(motor_pin2, 70);
        delay(forward_delay);
        analogWrite(motor_pin2, 0);
    }
}

void grip(int i)    // pass 1 to close grip, 2 to open grip
{ 
    Serial.println("Running Servo");
    if (i == 1)
    { // grip close
        for (int i = servo_low; i <= servo_high; i += 3)
        {
            servo1.write(i);
            delay(claw_speed);
        }
    }
    else if (i == 2)
    { // grip open
        for (int i = servo_high; i >= servo_low; i -= 3)
        {
            servo1.write(i);
            delay(claw_speed);
        }
    }
}

void move_pulley(int i) // pass 1 to down the pulley, pass 2 to up the pulley
{ 
    Serial.print("Moving pulley");
    Serial.println(i);
    if (i == 1)
    { // pull down
        analogWrite(pulley_pin1, 160);
        analogWrite(pulley_pin4, 120);
        delay(pulley_delay + 700);
        analogWrite(pulley_pin1, 100);
        analogWrite(pulley_pin4, 80);

    }
    else if (i == 2)
    { // pull up
        analogWrite(pulley_pin1, 0);
        analogWrite(pulley_pin4, 0);
        analogWrite(pulley_pin2, 40);
        analogWrite(pulley_pin3, 40);
        delay(pulley_delay);
        analogWrite(pulley_pin2, 0);
        analogWrite(pulley_pin3, 0);
    }
}