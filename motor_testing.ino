const int motor_pin1 = 0;
const int motor_pin2 = 0;
const int motor_pin3 = 0;
const int motor_pin4 = 0;
const int motor_pin5 = 0;

void setup()
{
    init_pins(motor_pin1);
    init_pins(motor_pin2);
    init_pins(motor_pin3);
    init_pins(motor_pin4);
    init_pins(motor_pin5);
    Serial.begin(9600);
    while(!Serial);
    Serial.print("Beginnig test!");
}
void loop()
{
    run_motor(motor_pin1);
    run_motor(motor_pin2);
    run_motor(motor_pin3);
    run_motor(motor_pin4);
    run_motor(motor_pin5);
}

void run_motor(int i)
{
    if (i != 0)
    {
        digitalWrite(i, HIGH);
        delay(1000);
        digitalWrite(i, LOW);
    }
}

void init_pins(int i)
{
    if (i != 0)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
}