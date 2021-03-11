// Teensy/Arduino Libraries
#include "Arduino.h"

// C/C++ Libraries
#include "bitwise.h"		// low level bit operations

// Custom Teensy Libraries
#include "HardwareSerial.h"
#include "teensy_uart.h"

// Project Specific Libraries
#include "mcu_options.h"
#include "odrive_controller.h"

void timer0ISR(void);
void blinkLED(int led_pin_, int on_time);

// Pin Assignments
const int led_pin = 13;
const int rx_pin = 0;			// connect to ODrive TX pin
const int tx_pin = 1;			// connect to ODrive RX pin

// Objects
IntervalTimer timer0;
uint32_t timer0_period = 1000;		// timer period [ms]

// Global Variables

void setup(){
	pinMode(led_pin, OUTPUT);
	digitalWrite(led_pin, LOW);

	// Connect to Serial Monitor
	Serial.begin(115200);
	while(!Serial);

	// Connect to ODrive via UART
	Serial1.begin(115200);
	while(!Serial1);
	//TODO read serial number to detect connection
	Serial.println("ODrive connected");

	int axis_num = 0;
	Serial.println(odriveReadBusVoltage());
	Serial.println(odriveReadPosEstimate(axis_num));
	odriveZeroEncoder(axis_num);

	//odriveWritePosGain(axis_num, 10);
	//odriveWriteVelGain(axis_num, 0.02);
	//odriveWriteVelIntegratorGain(axis_num, 0.4);
	//Serial.println(odriveReadCurrentControlBandwidth(axis_num));
	//Serial.println(odriveReadTrapTrajVelLimit(axis_num));
	//odriveWriteTrapTrajVelLimit(axis_num, 50);
	//Serial.println(odriveReadTrapTrajVelLimit(axis_num));
	//Serial.println(odriveReadTrapTrajAccelLimit(axis_num));
	//Serial.println(odriveReadTrapTrajDecelLimit(axis_num));

	// Configure and Activate Timers
	timer0.priority(180);
	//timer0.begin(timer0ISR, timer0_period*1000);  // start program/timer ISR
}

void loop(){}

void timer0ISR(void){
	//Serial.println("timer0ISR");
	//blinkLED(led_pin, 250);
}

void blinkLED(int led_pin_, int on_time){
	digitalWrite(led_pin_, HIGH);
	delay(on_time);
	digitalWrite(led_pin_, LOW);
}
