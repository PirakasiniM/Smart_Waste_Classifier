#include <Servo.h>
#include <Stepper.h>
int SensorPin = 3;
Servo flap;
const int Pin=4;
const int stepsPerRevolution = 2048;
int homing_pin=13;//IR
int homing;//IR
int i;

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
const int sensor_pin = A1;
float duration_us, distance_cm;

int previous = 0;
int pos=0;

void setup() 
{
	pinMode(Pin, INPUT);
	pinMode(SensorPin, INPUT);
    // begin serial port
	Serial.begin (9600);
	flap.attach(5);
	myStepper.setSpeed(5);
	flap.write(0);
	delay(100);            
  
}

void loop() 
{
	int sensorValue = digitalRead(Pin);
	int IRValue = digitalRead(SensorPin);
	
	float moisture_percentage;
	int sensor_analog;
	sensor_analog = analogRead(sensor_pin);
	moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
	Serial.print("Moisture Percentage = ");
	Serial.print(moisture_percentage);
	Serial.print("\n");
	delay(500);
	  
	Serial.print("Inductive Value: ");
	Serial.println(sensorValue);
	delay(500);
	
	Serial.print("SensorIRPin Value: ");
	Serial.println(IRValue);
	delay(4000);  

	Serial.print("\n");
		 
	if(moisture_percentage>2)
	{

		myStepper.step(650);
		delay(1000);

		delay(2000);
	 
		flap.write(0);              // tell servo to go to position in variable 'pos'
		delay(500);
		
		flap.write(60);
		delay(500);
		
		flap.write(60);
		delay(15);

		flap.write(0);
		delay(15);
	   
		myStepper.step(-650);
		delay(1000);
	}   

	else if(sensorValue==LOW)
	{    
	  
		myStepper.step(1000);
		delay(1000);
	 
		flap.write(0);              // tell servo to go to position in variable 'pos'
		delay(500);
		
		flap.write(60);
		delay(500);
		
		flap.write(60);
		delay(15);

		flap.write(0);
		delay(15);
	   
		myStepper.step(-1000);
		delay(1000);
	}
	
	else if(IRValue==LOW)
	{
		myStepper.step(1750);
		delay(1000);
	  
		flap.write(0);              // tell servo to go to position in variable 'pos'
		delay(500);
		flap.write(60);

		delay(500);
		flap.write(60);
		delay(15);

		flap.write(0);
		delay(15);
	   
		myStepper.step(-1750);
		delay(1000);  
	} 
}
