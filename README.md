# ODriveController
This library allows you to control an ODrive motor controller using a microcontroller.

## Overview
This library allows you to control the ODrive motor controller using a microcontroller. As of now, it only works with either the Arduino or the Teensy microcontrollers, but will be extended to any microcontroller in the future. There are two implementations of this library, a standalone set of functions and a class implementation.

### Required Libraries
- "ODriveArduino" - Performs low level ASCII communication between the microcontroller and the ODrive: https://github.com/odriverobotics/ODrive/tree/master/Arduino/ODriveArduino.
- "Arduino.h"
- "HardwareSerial.h" - Allows you to use UART on GPIO pins for the Teensy or Arduino microcontrollers

# Standalone Library - odrive_controller

## Startup and Calibration

### Using odrivetool
```
odrv0.axis0.requested_state = AXIS_STATE_IDLE
odrv0.axis0.motor.config.resistance_calib_max_voltage
odrv0.axis0.motor.config.calibration_current
odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
```
int tx = -12345;					// individual value (int32_t) to be transmitted
uartTransmit(tx);					// convert to bytes (four) and transmit them in a sequence


## Using Arduino

## Position Control

### Parameters to Adjust

```
odrv0.axis0.controller.config.pos_gain
odrv0.axis0.controller.config.vel_gain
odrv0.axis0.controller.config.vel_integrator_gain
odrv0.axis0.controller.config.inertia
odrv0.axis0.motor.config.current_control_bandwidth
odrv0.axis0.trap_traj.config.vel_limit
odrv0.axis0.trap_traj.config.accel_limit
odrv0.axis0.trap_traj.config.decel_limit
```

# Examples - odrive_controller
The following example scripts are included in the folder **examples > arduino_uart_examples** to demonstrate the functionality of the library.

**startup_routine.cpp** - Transmit an array of either floats or ints periodically via UART\
**position_control.cpp** - reads an input rotary knob's position (via AS5601) and controls an odrive with an AS5601 encoder to track the position
**speed_control.cpp** - TBD
**torque_contorl.cpp** - TBD
**dual_motor_control.cpp** - Implements position control of two motors simultaneously\

# Class Implementation - ODriveController

TBD

# Examples - Class Implementation

TBD

## Authors

* **Bryan Blaise** - *Initial work* -

## License

## Acknowledgments