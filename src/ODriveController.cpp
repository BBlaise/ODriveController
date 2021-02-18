/*
 * ODriveController.cpp
 *
 *  Created on: Feb 11, 2021
 *      Author: Bryan
 */

#include "ODriveController.h"

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"

odrv_options odrv{};

// Constructors and Deconstructor
ODriveController::ODriveController(){}

ODriveController::ODriveController(HardwareSerial* p_uart_){p_uart = p_uart_;}

//ODriveController::ODriveController(Stream& serial_) : serial(serial_){}

ODriveController::~ODriveController(){}

// ODrive Methods

// Axis Methods
ODriveController::Axis::Axis(){}

ODriveController::Axis::Axis(uint8_t axis_num_){
	axis_num = axis_num_;
}

// Controller Methods

// Motor Methods

// Encoder Methods
