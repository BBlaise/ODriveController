# ODrive Startup Guide
This tutorial steps you through the process of getting an brushless DC motup and running with the ODrive controller.

## Overview
This document guides you through what I did to get the ODrive controller working. I will show the process end to end, and provide a few more details than what the default ODrive documentation outlines. However, I won't repeat every single step shown in the ODrive documentation. I'll mainly focus on where my process deviated from the default one. I'll show you the proper connections, the sequence of functions and parameters to change, as well as common pitfalls. I'll then point you to how to configure the controller for various control modes. Lastly, I'll show you how to set up the controller for communication with a microcontroller (i.e. Teensy 3.6).

## Hardware
- 24V ODrive
- Teensy 3.6 microcontroller: https://www.pjrc.com/store/teensy36.html
- 36BLR65-24-01 (STEPPERONLINE) brushless DC motor: https://www.omc-stepperonline.com/brushless-dc-motor/24v-3000rpm-0064nm-20w-109a-round-%D1%8436x65mm-brushless-dc-motor-36blr65-24-01.html?limit=100
	- 4 poles
	- UVW hall efect sensors (not used)
	- Rated speed: 3000RPM
	- Stall torque: 0.220 N-m
	- Rated current: 1.09A
	- Stall current = 3.565A
- AS5601 (AMS) Contactless hall effect sensor/encoder: https://ams.com/AS5601
	- Outputs an absolute angle or an adjustable AB quadrature outputs up to 1024 CPR
	- Configured using I2C via a microcontroller (Teensy 3.6)
- 30V/10A power supply
- 50W resistor (comes with ODrive)

## Wiring
- ![](image/basic_wiring.png)
- If you are simultaneously using a microcontroller alongside the ODrive, make sure their ground pins are connected (either directly or via a breadboard).

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

* **Bryan Blaise** - *Author* -

## License

## Acknowledgments