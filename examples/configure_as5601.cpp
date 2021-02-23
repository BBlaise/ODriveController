// Teensy/Arduino Libraries
#include "Arduino.h"

#include "i2c_t3.h"

// C/C++ Libraries
#include "bitwise.h"		// low level bit operations

// Custom Teensy Libraries
#include "HardwareSerial.h"
#include "SoftwareSerial.h"
#include "ODriveArduino.h"
#include "TeensyI2C.h"
#include "teensy_uart.h"
#include "TeensyI2C.h"
#include "Encoder.h"		// counts pulses from AS5601 hall sensor

// Project Specific Libraries
#include "mcu_options.h"
//#include "ODriveController.h"
#include "AS5601.h"			// hall effect sensor library

// Function Prototypes
//template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
//template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }
void timer0ISR(void);
void blinkLED(int led_pin_, int on_time);

// Pin Assignments
const int encoder0A_pin = 5;		// A channel of AS5601 encoder0 (master)
const int encoder0B_pin = 6;		// B channel of AS5601 encoder0 (master)
const int encoder1A_pin = 7;		// A channel of AS5601 encoder1 (slave)
const int encoder1B_pin = 8;		// B channel of AS5601 encoder1 (slave)
const int led_pin = 13;
const int rx_pin = 0;			// connect to ODrive TX pin (pin 1)
const int tx_pin = 1;			// connect to ODrive RX pin (pin 2)

// Objects
IntervalTimer timer0;
uint32_t timer0_period = 250;		// timer period [ms]
ODriveArduino odrive(Serial1);
TeensyI2C i2c0(&Wire);
TeensyI2C i2c1(&Wire1);								// i2c bus for slave readings
AS5601 <TeensyI2C*> hall_sensor0(&i2c0);
AS5601 <TeensyI2C*> hall_sensor1(&i2c1);			// hall sensor for master
Encoder encoder0(encoder0A_pin, encoder0B_pin);		// master encoder
Encoder encoder1(encoder1A_pin, encoder1B_pin);	// slave encoder

// Global Variables
float master_cpr = 1024;
volatile int master_count = 0;
volatile float master_angle = 0;

float slave_cpr = 1024;
volatile int slave_count = 0;
volatile float slave_angle = 0;

// Runtime Edits
bool configure_hall_sensors = true;
//bool configure_hall_sensors = false;

void setup(){
	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 100000); // SCL = 19, SDA = 18, 100 kHz
	Wire1.begin(I2C_MASTER, 0x00, I2C_PINS_37_38, I2C_PULLUP_EXT, 100000); // SCL = 37, SDA = 38, 100kHz

	pinMode(led_pin, OUTPUT);
	digitalWrite(led_pin, LOW);

	// Connect to Serial Monitor
	Serial.begin(115200);
	while(!Serial);

	// Connect to ODrive via UART
	Serial1.begin(115200);
	while(!Serial1);
	Serial.println("ODrive connected");

	hall_sensor0.setABN(as5601.ABN1024);
	delay(10);
	Serial.println(hall_sensor0.readMagnitude());
	Serial.println("hall_sensor0 configured");
	master_cpr = hall_sensor0.n_pulses;
	//Serial.println(master_cpr);

	hall_sensor1.setABN(as5601.ABN1024);
	delay(10);
	Serial.println(hall_sensor1.readMagnitude());
	Serial.println("hall_sensor1 configured");
	slave_cpr = hall_sensor1.n_pulses;
	//Serial.println(slave_cpr);

	// Configure encoders
	encoder0.write(0);
	encoder1.write(0);

	// Configure and Activate Timers
	timer0.priority(180);
	//timer0.begin(timer0ISR, timer0_period*1000);  // start program/timer ISR
}

void loop(){}

void timer0ISR(void){
	//blinkLED(led_pin, 150);

	master_count = encoder0.read();
	master_angle = master_count * 360 / master_cpr;
	//Serial.println(master_count);

	slave_count = encoder1.read();
	slave_angle = slave_count * 360 / slave_cpr;
	Serial.println(slave_count);
}

void blinkLED(int led_pin_, int on_time){
	digitalWrite(led_pin_, HIGH);
	delay(on_time);
	digitalWrite(led_pin_, LOW);
}
