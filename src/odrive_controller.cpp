/*
 * odrive_controller.cpp
 *
 *  Created on: May 31, 2020
 *      Author: Bryan
 */
#include "odrive_controller.h"

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"
#include "teensy_uart.h"

/* ---------------- General Functions ------------------------ */
void odriveReboot(void){
	uartTransmitString(Serial1, "sr\n");
}

void odriveSaveConfiguration(void){
	uartTransmitString(Serial1, "ss\n");
}

void odriveEraseConfiguration(void){
	uartTransmitString(Serial1, "se\n");
}

unsigned int odriveReadState(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".current_state\n");
	return uartReceiveString(Serial1).toInt();
}

void odriveWriteState(int axis_num, unsigned int state){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".requested_state " + String(state) + "\n");
}

void odriveIdleMotor(int axis_num){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".requested_state " + String(AXIS_STATE_IDLE) + "\n");
}

// Implement with error array
void odriveClearErrors(int axis_num){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".error 0\n");
}

// Implement with error array
unsigned int odriveReadAxisErrors(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".error\n");
	String axis_error = uartReceiveString(Serial1);
	//if(axis_error == 0x40) odriveReadMotorErrors(axis_num);
	return axis_error.toInt();
}

float odriveReadBusVoltage(void){
	uartTransmitString(Serial1, "r vbus_voltage\n");
	return uartReceiveString(Serial1).toFloat();
}

/* ---------------- Control Parameters Functions ------------------------ */
float odriveReadPosGain(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".controller.config.pos_gain\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWritePosGain(int axis_num, float gain){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".controller.config.pos_gain " + String(gain) + "\n");
}

float odriveReadVelGain(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".controller.config.vel_gain\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteVelGain(int axis_num, float gain){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".controller.config.vel_gain " + String(gain) + "\n");
}

float odriveReadVelIntegratorGain(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".controller.config.vel_integrator_gain\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteVelIntegratorGain(int axis_num, float gain){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".controller.config.vel_integrator_gain " + String(gain) + "\n");
}

float odriveReadCurrentControlBandwidth(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".motor.config.current_control_bandwidth\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteCurrentControlBandwidth(int axis_num, float bandwidth){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".motor.config.current_control_bandwidth " + String(bandwidth) + "\n");
}

float odriveReadInputFilterBandwidth(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".controller.config.input_filter_bandwidth\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteInputFilterBandwidth(int axis_num, float bandwidth){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".motor.config.input_filter_bandwidth " + String(bandwidth) + "\n");
}

float odriveReadTrapTrajVelLimit(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".trap_traj.config.vel_limit\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteTrapTrajVelLimit(int axis_num, float limit){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".trap_traj.config.vel_limit " + String(limit) + "\n");
}

float odriveReadTrapTrajAccelLimit(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".trap_traj.config.accel_limit\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteTrapTrajAccelLimit(int axis_num, float limit){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".trap_traj.config.accel_limit " + String(limit) + "\n");
}

float odriveReadTrapTrajDecelLimit(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".trap_traj.config.decel_limit\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteTrapTrajDecelLimit(int axis_num, float limit){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".trap_traj.config.decel_limit " + String(limit) + "\n");
}


/* ---------------- Control Functions ------------------------ */
void odriveZeroEncoder(int axis_num){
	// not working (likely not possible until next release or devel branch)
	uartTransmitString(Serial1, "esl axis" + String(axis_num) + " 0\n");
}

float odriveReadPosEstimate(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".encoder.pos_estimate\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWriteInputPos(int axis_num, float position){
	//uartTransmitString(Serial1, "w axis" + String(axis_num) + ".controller.input_pos " + String(position) + "\n");
    uartTransmitString(Serial1, "p " + String(axis_num)  + " " + String(position) + " 0 0\n");
}

/*
float odriveReadVelocity(void){
	Serial1 << "r axis" << 0 << ".encoder.vel_estimate\n";
	return odrive.readFloat();
}

void odriveWriteVelocity(float velocity_){
	Serial1 << "w axis" << 0 << ".controller.input_vek = " << velocity_ << "\n";
}
*/

float odriveReadIq(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".motor.current_control.Iq_measured\n");
	return uartReceiveString(Serial1).toFloat();
}

float odriveReadId(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".motor.current_control.Id_measured\n");
	return uartReceiveString(Serial1).toFloat();
}

/* ---------------- Motor Parameters ------------------------ */
float odriveReadPhaseResistance(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".motor.config.phase_resistance\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWritePhaseResistance(int axis_num, float resistance){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".motor.config.phase_resistance " + String(resistance) + "\n");
}

float odriveReadPhaseInductance(int axis_num){
	uartTransmitString(Serial1, "r axis" + String(axis_num) + ".motor.config.phase_inductance\n");
	return uartReceiveString(Serial1).toFloat();
}

void odriveWritePhaseInductance(int axis_num, float inductance){
	uartTransmitString(Serial1, "w axis" + String(axis_num) + ".motor.config.phase_inductance " + String(inductance) + "\n");
}
