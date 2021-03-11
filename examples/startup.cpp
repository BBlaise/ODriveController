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
	Serial.println("ODrive connected");

	int axis_num = 0;
	// Read voltage to confirm proper ODrive communication
	Serial.println(odriveReadBusVoltage());

	// Read and clear errors
	Serial.println(odriveReadAxisErrors(axis_num));
	odriveClearErrors(axis_num);
	Serial.println(odriveReadAxisErrors(axis_num));

	// Set motor idle
	odriveWriteState(axis_num, AXIS_STATE_IDLE);
	//odriveIdleMotor(axis_num);

	// Parameters to adjust before calibration
	Serial.println(odriveReadPhaseInductance(axis_num), 3);
	Serial.println(odriveReadPhaseResistance(axis_num), 3);
	//odriveWritePhaseInductance(axis_num, 0.003);
	//odriveWritePhaseResistance(axis_num, 1.95);
	//Serial.println(odriveReadPhaseInductance(axis_num), 3);
	//Serial.println(odriveReadPhaseResistance(axis_num), 3);

	// Calibration
	//odriveWriteState(axis_num, AXIS_STATE_FULL_CALIBRATION_SEQUENCE);
	//odriveWriteState(axis_num, AXIS_STATE_MOTOR_CALIBRATION);
	//odriveWriteState(axis_num, AXIS_STATE_ENCODER_OFFSET_CALIBRATION);
	//odriveWriteState(axis_num, AXIS_STATE_ENCODER_INDEX_SEARCH);

	//odriveIdleMotor(axis_num);

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
