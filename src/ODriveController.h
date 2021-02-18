/*
 * ODriveController.h
 *
 *  Created on: Feb 11, 2021
 *      Author: Bryan
 */

#ifndef ODRIVECONTROLLER_H_
#define ODRIVECONTROLLER_H_

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"

// ODrive Options
/*int enum_val0 = 0;
int enum_val1 = 2;*/

struct odrv_options{
	// Axis Options
	struct axis_ {
		enum error : unsigned int {
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

		// Controller Options
		struct controller_ {
			enum error {
				ERROR_NONE = 0x00,
				ERROR_OVERSPEED = 0x01,
				ERROR_INVALID_INPUT_MODE = 0x02,
				ERROR_UNSTABLE_GAIN = 0x04,
				ERROR_INVALID_MIRROR_AXIS = 0x08,
				ERROR_INVALID_LOAD_ENCODER = 0x10,
				ERORR_INVALID_ESTIMATE = 0x20
			};

			// Config Options
			enum control_mode {
				CONTROL_MODE_VOLTAGE_CONTROL = 0,
				CONTROL_MODE_TORQUE_CONTROL = 1,
				CONTROL_MODE_VELOCITY_CONTROL = 2,
				CONTROL_MODE_POSITION_CONTROL = 3
			};

			enum input_mode {
				INPUT_MODE_INACTIVE = 0,
				INPUT_MODE_PASSTHROUGH = 1,
				INPUT_MODE_VEL_RAMP = 2,
				INPUT_MODE_POS_FILTER = 3,
				INPUT_MODE_MIX_CHANNELS = 4,
				INPUT_MODE_TRAP_TRAJ = 5,
				INPUT_MODE_TORQUE_RAMP = 6,
				INPUT_MODE_MIRROR = 7,
			};
		};
		controller_ controller{};

		// Motor Options
		struct motor_ {
			enum error {
				ERROR_NONE = 0x00,
				ERROR_PHASE_RESISTANCE_OUT_OF_RANGE = 0x01,
				ERROR_PHASE_INDUCTANCE_OUT_OF_RANGE = 0x02,
				ERROR_ADC_FAILED = 0x04,
				ERROR_DRV_FAULT = 0x08,
				ERROR_CONTROL_DEADLINE_MISSED = 0x10,
				ERROR_NOT_IMPLEMENTED_MOTOR_TYPE = 0x20,
				ERORR_BRAKE_CURRENT_OUT_OF_RANGE = 0x40,
				ERROR_MODULATION_MAGNITUDE = 0x80,
				ERROR_CURRENT_LIMIT_VIOLATION = 0x1000
			};

			// Motor Type Options
			enum motor_type {
				MOTOR_TYPE_HIGH_CURRENT = 0,
				MOTOR_TYPE_GIMBAL = 2,
				MOTOR_TYPE_ACIM = 3
			};

			// Armed State Options
			enum armed_state {
				ARMED_STATE_DISARMED = 0,
				ARMED_STATE_WAITING_FOR_TIMINGS = 1,
				ARMED_STATE_WAITING_FOR_UPDATE = 2,
				ARMED_STATE_ARMED = 3
			};
		};
		motor_ motor{};
	};
	axis_ axis{};

	//
};
extern odrv_options odrv;

class ODriveController {
public:
	ODriveController();
	ODriveController(HardwareSerial* p_uart_);
	//ODriveController(p_uart* serial_);		// implement template version of class
	//ODriveController(Stream& serial_);
	virtual ~ODriveController();

	// ODrive
	void reboot(void);
	void saveConfiguration(void);
	void eraseConfiguration(void);
	float readBusVoltage(void);
	// readErrors() How do you do this?

	// Axes
	class Axis {
	public:
		Axis();
		Axis(uint8_t axis_num_);
		uint8_t axis_num = 0;
		uint8_t current_state = 0;
		uint8_t requested_state = 0;

		void requestState(void);
		unsigned int readCurrentState(void);
		void writePosition(void);
		float readPosition(void);
		void writeVelocity(void);
		float readVelocity(void);
		void writeTorque(void);
		float readTorque(void);
		void moveIncremental(void);
		void setLinearCount(int count_);

		// Axis Config
		struct config_ {
			bool startup_motor_calibration = false;
			bool startup_encoder_index_search = false;
			bool startup_encoder_offset_calibraiton = false;
			bool startup_closed_loop_control = false;
			bool startup_sensorles_control = false;
			bool startup_homing = false;
		};
		config_ config{};

		// --------- Controller -----------//
		struct controller_ {
			unsigned int error;
			float input_pos = 0;
			float input_vel = 0;
			float input_torque = 0;
			float pos_setpoint;
			float vel_setpoint;
			float torque_setpoint;
			float vel_integrator_torque;

			// Config
			struct config_ {
				int control_mode = 3;
				int input_mode = 1;
				float pos_gain = 0;
				float vel_gain = 0;
				float vel_integrator_gain = 0;
				float vel_limit;
				float vel_limit_tolerance = 1.0;
				float torque_ramp_rate;
				float homing_speed;
				float inertia;
				bool enable_vel_limit = true;
				bool enable_current_mode_vel_limit = true;
				bool enable_overspeed_error = true;
			};
			config_ config{};
		};
		controller_ controller{};

		// --------- Motor -----------//
		struct motor_ {
			unsigned int error;
			unsigned int armed_state;
			bool is_calibrated = false;
			float current_meas_phB;
			float current_meas_phC;

			// Config
			struct config_ {
				bool pre_calibrated = false;
				int pole_pairs = 2;
				float calibration_current;
				float resistance_calib_max_voltage;
				float phase_inductance;
				float torque_constant;
				float direction;
				unsigned int motor_type;
				float torque_lim;
				float current_control_bandwidth;
			};
			config_ config{};

			// current_control
		};
		motor_ motor{};

		// --------- Encoder -----------//
		struct encoder_ {
			bool index_found = false;
			float shadow_count;
			int32_t count_in_cpr = 0;
			float pos_estimate;
			float vel_esimate;
			//bool use_index = false;
			//int cpr = 1024;

			// Config
			struct config_ {
				bool use_index = false;
				int cpr = 1024;
			};
			config_ config{};

			// current_control
		};
		encoder_ encoder{};

		// --------- TrapTraj -----------//
	};

	Axis axis0;
	Axis axis1;

	// Encoder Options
	float cpr = 1024;

	// Accessors

private:
	//Stream& serial;
	HardwareSerial* p_uart;
};

#endif /* ODRIVECONTROLLER_H_ */
