/*
 * teensy_uart.h
 *
 *  Created on: May 31, 2020
 *      Author: Bryan
 */

#ifndef ODRIVE_CONTROLLER_H_
#define ODRIVE_CONTROLLER_H_

#include "Arduino.h"

template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }

// General Functions
void reboot(void);
void saveConfiguration(void);
void eraseConfiguration(void);
int readCurrentState(void);
int writeRequestedState(void);
void stopMotor(void);
void writeControlMode(int control_mode_);
void writeInputMode(int input_mode_);

/* ---------------- Control Parameters to Adjust ------------------------ */
float readPosGain(void);
void writePosGain(float pos_gain_);
float readVelGain(void);
void writeVelGain(float vel_gain_);
float readVelIntegralGain(void);
void writeVelIntegralGain(float vel_integral_gain_);
float readInertia(void);
void writeInertia(float inertia_);
float readTrajVelLimit(void);
void writeTrajVelLimit(float vel_limit_);
float readTrajAccelLimit(void);
void writeTrajAccelLimit(float accel_limit_);
float readTrajDecelLimit(void);
void writeTrajDecelLimit(float decel_limit_);

/* ---------------- Transmit Functions - Binary ------------------------ */
// Position Control
float readPosition(void);
void writePosition(float position_);

// Speed Control
float readVelocity(void);
void writeVelocity(float velocity_);

// Torque/Current Control
float readTorque(void);
void writeTorque(float velocity_);

/* ---------------- Receive Functions - Binary ------------------------ */
// Receive Individual Values
float uartReceiveFloat(void);
int uartReceiveInt(void);
int32_t uartReceiveInt32(void);
int16_t uartReceiveInt16(void);
int8_t uartReceiveInt8(void);
uint32_t uartReceiveUint32_t(void);
uint16_t uartReceiveUint16_t(void);

// Receive An Array/Vector of Values
void uartReceive(float* rx, int n_rx);
void uartReceive(int* rx, int n_rx);
void uartReceive(int32_t* rx, int n_rx);
void uartReceive(int16_t* rx, int n_rx);
void uartReceive(int8_t* rx, int n_rx);
void uartReceive(uint32_t* rx, int n_rx);
void uartReceive(uint16_t* rx, int n_rx);
void uartReceive(uint8_t* rx, int n_rx);


#endif /* ODRIVE_CONTROLLER_H_ */
