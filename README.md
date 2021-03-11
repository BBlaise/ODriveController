# ODriveController
This library allows you to control an ODrive motor controller using a microcontroller.

## Overview
This library allows you to control the ODrive motor controller using a microcontroller. As of now, it only works with either the Arduino or the Teensy microcontrollers, but will be extended to any microcontroller in the future. There are two implementations of this library, a standalone set of functions and a class implementation. Refer to "startup_guide.md" for tips on getting a new motor configured to run with the ODrive

### Required Libraries
- "ODriveArduino" - Performs low level ASCII communication between the microcontroller and the ODrive: https://github.com/odriverobotics/ODrive/tree/master/Arduino/ODriveArduino.
- "Arduino.h"
- "HardwareSerial.h" - Allows you to use UART on GPIO pins for the Teensy or Arduino microcontrollers

# Serial Communication
In this section I'll outline what needs to be transmitted or received on the serial port to perform the various functions of the ODrive.
## Baud Rate Configuration
First, you'll want to make sure the microcontroller and the ODrive are communicating with the same baud rate. The default ODrive baud rate is 115200 but you can set it using
```
odrv0.config.uart_baudrate = 115200
```
On the microcontroller side, you'll want to initialize the odrive object with the HardwareSerial object you're using to communicate with via UART. Make sure it's declared as a global object.
```
ODriveArduino odrive(Serial1);
```
Set the baud rate to match the ODrive's 
```
Serial1.begin(115200);
while(!Serial1);
```

## Startup and Calibration
As an initial test, you might want to read the bus voltage to ensure it is the same voltage provided by the power supply. To this, you need to send the following sequence of ASCII characters to the ODrive
```
r vbus_voltage\n
```
The ODrive will then send an ASCII string with the bus voltage that you'll then need to convert to a float.

You might also want to read the serial number of the ODrive if using multiple ODrives to make sure you've associated each serial bus with the correct controller.

To set the motor to an idle state, transmit:
```
w axis0.requested_state 1\n
```

Next, you can perform the startup/calibration sequence of your choosing. To perform the full calibration sequence, transmit
```
w axis0.requested_state 3\n
```
To only find the encoder offset, transmit
```
w axis0.requested_state 7\n
```


If you need to reboot the motor, transmit
```
sr\n
```
If you want to save the configuration, transmit
```
sr\n
```
If you want to erase the configuration, transmit
```
se\n
```

## Position Control
Zero the encoder/position estimate (may not be implemented until next release of odrivetool)
```
esl <axis> <value>\n
```

Change the input mode
- Passthrough:
```
w axis0.controller.input_mode 1\n
```
- Trapezoidal trajectory:
```
w axis0.controller.input_mode 5\n
```
Change the the control mode to closed loop position control:
```
w axis0.controller.control_mode 3\n
```

Read Position/Angle
```
r aixs0.encoder.pos_estimate\n
```
Write Position/Angle
- Command motor to an angle (in turns)
```
p <axis> <turns> <velocity_feedforward> <torque_feedforward>\n
```

- To command motor 0 to follow a position of 0.5 turns, transmit
```
p 0 0.5 0 0\n
```

## Velocity Control
TBD

## Torque/Current Control

# Standalone Library - odrive_controller
This document assumes you've already gone through *STARTUP_GUIDE.md* and know how to calibrate and tune your motor. It's easiest to do that procedure using odrivetool so I recommend you do that first. Afterwards, I would use this library and its functions to control the motor in real time with an Arduino.

## Startup and Calibration
Initialize the odrive object with the HardwareSerial object you're using to communicate with via UART. Make sure it's declared as a global object.
```
ODriveArduino odrive(Serial1);
```

First you'll want to make sure the microcontroller and the ODrive are communciating with the same baud rate. The ODrive's default baud rate is 115200. 
```
Serial1.begin(115200);
while(!Serial1);
```
Next, you'll want to run the calibration sequence, adjust any parameters or gains, and read/clear any errors, if necessary (To be continued). In my case, I also had to configure the encoder to output the correct amount of pulses

## Position Control

```
odrv0.axis0.controller.config.pos_gain
```

# Examples - odrive_controller
The following example scripts are included in the folder **examples > arduino_uart_examples** to demonstrate the functionality of the library. In all of these examples, the microcontroller is a [Teensy 3.6](https://www.pjrc.com/store/teensy36.html), the motor is a [brushless DC motor](https://www.omc-stepperonline.com/brushless-dc-motor/24v-3000rpm-0064nm-20w-109a-round-%D1%8436x65mm-brushless-dc-motor-36blr65-24-01.html?limit=100), and the encoder is an [AS5601](https://ams.com/AS5601) paired with a radial magnet

**startup_routine.cpp** - (TBD) Transmit an array of either floats or ints periodically via UART
**position_control.cpp** - Commands a repeating position step input or sinusoidal signal to the motor for the ODrive to follow
**position_tracking.cpp** - reads an input rotary knob's position (via AS5601) and controls an odrive with an AS5601 encoder to track the position
**speed_control.cpp** - (TBD)
**torque_contorl.cpp** - (TBD)
**dual_motor_control.cpp** - (TBD) Implements position control of two motors simultaneously\

# Class Implementation - ODriveController

TBD

# Examples - Class Implementation

TBD

## Authors

* **Bryan Blaise** - *Initial work* -

## License

## Acknowledgments