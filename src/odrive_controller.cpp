/*
 * teensy_uart.cpp
 *
 *  Created on: May 31, 2020
 *      Author: Bryan
 */

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"

float readBusVoltage(void){
		Serial1 << "r vbus_voltage\n";
		Serial << "Vbus voltage: " << odrive.readFloat() << '\n';
}

float readPosition(void){
	Serial1 << "r axis" << 0 << ".encoder.pos_estimate\n";
	return odrive.readFloat();
}

void writePosition(float position_){
	Serial1 << "w axis" << 0 << ".controller.input_pos = " << position_ << "\n";
}

float readVelocity(void){
	Serial1 << "r axis" << 0 << ".encoder.vel_estimate\n";
	return odrive.readFloat();
}

void writePosition(float velocity_){
	Serial1 << "w axis" << 0 << ".controller.input_vek = " << velocity_ << "\n";
}

float readPosGain(void){
	Serial1 << "r axis" << 0 << ".controller.config.pos_gain\n";
	return odrive.readFloat();
}
float readVelGain(void){
	Serial1 << "r axis" << 0 << ".controller.config.vel_gain\n";
	return odrive.readFloat();
}

float readVelIntegralGain(void){
	Serial1 << "r axis" << 0 << ".controller.config.vel_integral_gain\n";
	return odrive.readFloat();
}

