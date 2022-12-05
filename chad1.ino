#include <Servo.h> 

const int motor_pin1 = 2;       //forward
const int motor_pin2 = 2;       //reverse
const int servo_pin = 2;
const int forward_delay = 1000;  //delay required for moving the motors forward.
const int servo_low = 20;    //servo low limit for the claw
const int servo_high = 120;  //servo high limit for the claw
const int claw_speed = 20;   //decrease the value to increase the claw speed
Servo servo1;

void setup(){
    pinMode(motor_pin1, OUTPUT);
    pinMode(motor_pin2, OUTPUT);
    servo1.attach(servo_pin);
    Serial.begin(9600);
    while(!Serial){}
    servo1.write(0); 

}
void loop(){
    run_motor(1);
    grip(1);
    run_motor(2);
    grip(2);
}

void run_motor(int i){      //pass 1 for forward, 2 for backward
    if(i == 1){     //move forward
        digitalWrite(motor_pin1, HIGH);
        delay(forward_delay);
        digitalWrite(motor_pin1, LOW);
    }
    else if(i == 2){            //move backward
        digitalWrite(motor_pin2, HIGH);
        delay(forward_delay);
        digitalWrite(motor_pin2, LOW);
    }
}

void grip(int i){               //pass 1 to close grip, 2 to open grip
    if(i == 1){     //grip close
        for(int i = servo_low; i <= servo_high; i+=3){
            servo1.write(i);
            delay(claw_speed);
        }
    } else if (i == 2){     //grip open
        for(int i = servo_high; i >= servo_low; i+=3){
            servo1.write(i);
            delay(claw_speed);
        }
    }
}