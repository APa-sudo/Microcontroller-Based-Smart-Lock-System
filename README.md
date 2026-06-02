# Microcontroller-Based Smart Lock System

## Overview

This project implements a password-protected electronic locking system using an Arduino-compatible microcontroller. The system combines push-button input, servo motor actuation, visual status indication, and potentiometer-based manual control to simulate a secure access control mechanism.

The project was developed as part of a microcontroller laboratory course and demonstrates embedded programming concepts including digital I/O, analog input processing, actuator control, debouncing, state management, and user interface feedback.

---

## Features

* Password-based unlocking mechanism
* Servo motor controlled locking system
* Push-button user input
* Debounced button handling
* Visual feedback using LEDs and RGB LEDs
* Potentiometer-based manual servo control
* System reset functionality
* State-based control logic

---

## Hardware Components

* Arduino-compatible microcontroller
* Servo motor
* Push buttons
* Potentiometer
* Red LED
* Green LED
* RGB LED
* Breadboard and jumper wires

---

## System Operation

### Locked State

When powered on, the system starts in the locked state:

* Servo moves to the locked position
* Red LED indicates locked status
* User inputs are monitored

---

### Password Entry

The user enters a predefined button sequence using two input buttons.

The implemented access code is:

```text
Button 1 → Button 2
```

The sequence is stored and validated after the required number of inputs has been received.

---

### Successful Authentication

If the entered sequence matches the stored access code:

* Servo rotates to the unlocked position
* Green LED turns on
* RGB LED flashes green
* System enters unlocked state

---

### Failed Authentication

If the entered sequence is incorrect:

* RGB LED flashes red
* System remains locked
* Input buffer is cleared

---

### Manual Servo Control

While the system is locked, a potentiometer can be used to control the servo position within predefined limits.

This feature was included to demonstrate analog input acquisition and actuator control using ADC values.

---

### System Reset

Pressing the reset button:

* Clears all user input
* Returns the servo to the locked position
* Resets status indicators
* Restores the initial system state

---

## Embedded Concepts Demonstrated

* Digital input handling
* Button debouncing
* State machines
* Servo motor control
* Analog-to-digital conversion (ADC)
* Embedded security logic
* Real-time event processing
* User feedback systems

---

## Technologies Used

* Arduino C/C++
* Arduino IDE
* Servo Library

---

## Learning Outcomes

This project provided practical experience with:

* Embedded software development
* Hardware-software integration
* Sensor and actuator interfacing
* State-based system design
* Real-time control logic
* Debugging microcontroller applications

---

## Author

Akshat Pathak

Bachelor's in Robotics Engineering
Technische Hochschule Würzburg-Schweinfurt (THWS)
