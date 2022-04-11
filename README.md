# Muscle-Sensor

Sensor changed due to out of stock of MyoWare Muscle Sensor

# NEW Sensor: EMG Detector

Product: Grove EMG Detector

Datasheet included in the directory

--------------------------------------------------------------
This directory will include these things:
1. Datasheet
2. C codes to compile with arduino uno rev3 - atmega328p microcontroller
	+ EMG Detector
	+ Servo Motor
4. Python file: script to compile C code file
5. Circuit Design
6. Video demo
--------------------------------------------------------------
Guide to compile:
- Download the zip file
- Edit the python file:
	1. Edit the path_win_avr in python_script.py
	example: path_win_avr = '[your root avr]/avr-gcc-11.1.0-x64-windows/avr-gcc-11.1.0-x64-windows/bin/'
	3. Python installed
	4. Run in cmd: [root of file keypad.c]\python compile_script.py 4
--------------------------------------------------------------
Ideas: Bicep to control the Servo Motor
- EMG Detector will measure the digital signals of the biceps
- Servo Motor will operate based on the output of the EMG Detector
