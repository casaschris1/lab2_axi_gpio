\# ECE 520 Lab 2 - AXI GPIO

This project implements an AXI GPIO system on the Zybo Z7-10 using Vivado and Vitis



\## Hardware

* Zybo Z7-10
* Zynq-7000 Processing System
* 3 AXI GPIO peripherals
* 4 onboard switches
* 4 onboard LEDs
* RGB LED

\## Software

* Vivado 2023.1
* Vitis 2023.1
* C

\## AXI GPIO Configuration

Three AXI GPIO peripherals are used:

* AXI GPIO 0 - Controls the four LEDs
* AXI GPIO 1 - Controls the RGB LED
* AXI GPIO 2 - Reads the four switches

The LED and RGB GPIOs are configured as outputs, while the switch GPIO is configured as an input.

\## Hardware Verification

The design was successfully implemented and tested on the Zybo Z7-10.

Testing confirmed by instructor.

