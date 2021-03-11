/*
 * odrive_controller.h
 *
 *  Created on: January 31, 2021
 *      Author: Bryan
 */

#ifndef ODRIVE_CONTROLLER_H_
#define ODRIVE_CONTROLLER_H_

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"
#include "teensy_uart.h"

/* ---------------- General Functions ------------------------ */
void odriveReboot(void);
void odriveSaveConfiguration(void);
void odriveEraseConfiguration(void);
unsigned int odriveReadState(int axis_num);
void odriveWriteState(int axis_num, unsigned int state);
void odriveIdleMotor(int axis_num);
void odriveClearErrors(int axis_num);
void odriveReadOdrvErrors(void);		// figure out
unsigned int odriveReadAxisErrors(int axis_num);		// figure out
void writeControlMode(int control_mode_);
void writeInputMode(int input_mode_);
float odriveReadBusVoltage(void);

/* ---------------- Control Parameters ------------------------ */
float odriveReadPosGain(int axis_num);
void odriveWritePosGain(int axis_num, float gain);
float odriveReadVelGain(int axis_num);
void odriveWriteVelGain(int axis_num, float gain);
float odriveReadVelIntegratorGain(int axis_num);
void odriveWriteVelIntegratorGain(int axis_num, float gain);
float odriveReadCurrentControlBandwidth(int axis_num);
void odriveWriteCurrentControlBandwidth(int axis_num, float bandwidth);
float odriveReadInputFilterBandwidth(int axis_num);
void odriveWriteInputFilterBandwidth(int axis_num, float bandwidth);
float odriveReadTrapTrajVelLimit(int axis_num);
void odriveWriteTrapTrajVelLimit(int axis_num, float limit);
float odriveReadTrapTrajAccelLimit(int axis_num);
void odriveWriteTrapTrajAccelLimit(int axis_num, float limit);
float odriveReadTrapTrajDecelLimit(int axis_num);
void odriveWriteTrapTrajDecelLimit(int axis_num, float limit);

/* ---------------- Control Functions ------------------------ */
void odriveZeroEncoder(int axis_num);
void odriveSetEncodercount(int axis_num, int count);
float odriveReadPosEstimate(int axis_num);
void odriveWriteInputPos(int axis_num, float position);
float odriveReadVelocityEstimate(int axis_num);
void odriveWriteVelocity(int axis_num, float velocity);
float odriveReadTorque(int axis_num);
void odriveWriteTorque(int axis_num, float torque);
float odriveReadIq(int axis_num);
float odriveReadId(int axis_num);

/* ---------------- Motor Parameters ------------------------ */
float odriveReadPhaseResistance(int axis_num);
void odriveWritePhaseResistance(int axis_num, float resistance);
float odriveReadPhaseInductance(int axis_num);
void odriveWritePhaseInductance(int axis_num, float inductance);

enum error : unsigned int {
//enum axis_error {
	ERROR_NONE = 0x00,
	ERROR_INVALID_STATE = 0x01,
	ERROR_DC_BUS_UNDER_VOLTAGE = 0x02,
	ERROR_DC_BUS_OVER_VOLTAGE = 0x04,
	ERROR_MOTOR_DISARMED = 0x20,
	ERROR_MOTOR_FAILED = 0x40,
	ERROR_ENCODR_FAILED = 0x100,
	ERROR_CONTROLLER_FAILED = 0x200,
};

enum axis_state {
	AXIS_STATE_UNDEFINED = 0,
	AXIS_STATE_IDLE = 1,
	AXIS_STATE_STARTUP_SEQUENCE = 2,
	AXIS_STATE_FULL_CALIBRATION_SEQUENCE = 3,
	AXIS_STATE_MOTOR_CALIBRATION = 4,
	AXIS_STATE_SENSORLESS_CONTROL = 5,
	AXIS_STATE_ENCODER_INDEX_SEARCH = 6,
	AXIS_STATE_ENCODER_OFFSET_CALIBRATION = 7,
	AXIS_STATE_CLOSED_LOOP_CONTROL = 8,
	AXIS_STATE_LOCKIN_SPIN = 9,
	AXIS_STATE_ENCODER_DIR_FIND = 10,
	AXIS_STATE_HOMING = 11
};

#endif /* ODRIVE_CONTROLLER_H_ */
