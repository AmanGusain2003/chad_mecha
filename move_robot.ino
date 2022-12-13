// This code has movement of the robot in it with ultrasonic

#include <Servo.h>

// All pins
const int motor_pin1 = 4; // move grip forward
const int motor_pin2 = 3; // move grip reverse
const int servo_pin = 7;
const int pulley_pin1 = 9;        // move pulley down
const int pulley_pin2 = 6;        // move pulley up
const int motor_move_robot1 = 23; // move the robot forward
const int motor_move_robot2 = 22; // move the robot backward
const int ultrasonic1_trig = 3; //forward ultrasonic trig 
const int ultrasonic1_echo = 3; //forward ultrasonic echo
const int ultrasonic2_trig = 3; //backward ultrasonic trig
const int ultrasonic2_echo = 3; //backward ultrasonic echo

//***********
// some values
const int forward_delay = 3500; // delay required for moving the grip motors forward.
const int pulley_delay = 3000;  // delay required to completely pull pulley down or up.
const int servo_low = 80;       // servo low limit for the claw
const int servo_high = 150;     // servo high limit for the claw
const int claw_speed = 20;      // **decrease the value to increase the claw speed**
const int safe_distance = 20;   // safe distance for the ultrasonic (in cm)
//*********

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
    servo1.attach(servo_pin);
    Serial.begin(9600);
    while (!Serial)
    {
    }
    servo1.write(servo_low);
    digitalWrite(motor_pin1, LOW);
    digitalWrite(motor_pin2, LOW);
}
void loop()
{
    move_grip_motor(1);
    grip(1);
    move_grip_motor(2);
    move_pulley(2);
    move_robot(1);

    move_pulley(1);
    move_grip_motor(1);
    grip(2);
    move_grip_motor(2);
    move_pulley(2);
    move_robot(2);
    Serial.println("Demo ended.");
    while (1);
}

//****************************All Functions****************

int get_distance(int echo_pin, int trig_pin) // pass ultrasonic pins to get the distance
{
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(echo_pin, HIGH);
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

            int distance = get_distance(ultrasonic1_echo, ultrasonic1_trig);
            if (distance >= 10)
            {
                digitalWrite(motor_move_robot1, HIGH);
            }
            else
                digitalWrite(motor_move_robot1, LOW);
            delay(10);
        }
    }

    else if (i == 2)
    {
        while (move)
        {
            int distance = get_distance(ultrasonic2_echo, ultrasonic1_trig);
            if (distance >= 10)
            {
                digitalWrite(motor_move_robot2, HIGH);
            }
            else
                digitalWrite(motor_move_robot2, LOW);
            delay(10);
        }
    }
}

void move_grip_motor(int i)   // pass 1 for forward, 2 for backward
{ 
    Serial.println("Running Motor ");
    if (i == 1)
    { // move forward
        digitalWrite(motor_pin1, HIGH);
        delay(forward_delay);
        digitalWrite(motor_pin1, LOW);
    }
    else if (i == 2)
    { // move backward
        digitalWrite(motor_pin2, HIGH);
        delay(forward_delay);
        digitalWrite(motor_pin2, LOW);
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
    Serial.println("Moving pulley");
    if (i == 1)
    { // pull down
        digitalWrite(pulley_pin1, HIGH);
        delay(pulley_delay);
        digitalWrite(pulley_pin1, LOW);
    }
    else if (i == 2)
    { // pull up
        digitalWrite(pulley_pin2, HIGH);
        delay(pulley_delay);
        digitalWrite(pulley_pin2, LOW);
    }
}
