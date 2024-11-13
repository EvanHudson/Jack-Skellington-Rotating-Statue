# Servo and LED Control with Light Detection

This project controls an MG90 servo motor and an array of LEDs based on button input and Light Dependent Resistor (LDR) readings. The program toggles through various modes, each affecting the servo's movement and LED patterns.

## Features

- **Button-Controlled Modes**: Toggle between 12 different modes by pressing a button.
- **LED Patterns**: Each mode displays a unique LED pattern across six LEDs.
- **Servo Motion**: Servo angle adjusts in specific modes, providing varying speeds and directions.
- **Light Detection**: Adjusts LEDs based on LDR values to simulate light sensitivity.

## Components

- **MG90 Servo Motor**: Controls the servo's angle.
- **LDR (Light Dependent Resistor)**: Reads ambient light levels.
- **Button**: Used to change modes.
- **6 LEDs**: Connected to pins 2 through 6 and pin 12, configured to display different patterns.

## Circuit Diagram

- **LDR**: Connected to analog pin A1.
- **Servo Motor**: Signal wire connected to pin 9.
- **LEDs**: Connected to digital pins 2, 3, 4, 5, 6, and 12.
- **Button**: Connected to pin 7 with internal pull-up resistor enabled.

## Code Overview

### Variables

- **LDRValue**: Stores the current reading from the LDR.
- **buttonPressCount**: Tracks the button presses to switch modes.
- **currentMode**: Determines the current operation mode.
- **Servo Control**: `slow()`, `fast()`, `spinLeft()` functions control the servo's movement.
- **LED Control**: `blinkSlow()` and `blinkFast()` functions control LED blinking speed.

### Modes

The button toggles through multiple modes. Each mode provides a different LED pattern and servo behavior:
1. **All LEDs On**: Servo rotates slowly clockwise.
2. **Green LEDs On**: Servo rotates slowly.
3. **Orange LEDs On**: Servo rotates slowly.
4. **Alternating Orange and Green LEDs**: Servo rotates slowly.
5. **Sequential LED Activation**: LEDs light up in sequence.
6. **Servo Scanning with LEDs**: Servo moves in a scanning pattern with LEDs.
7. **LDR Triggered LEDs**: Lights LEDs based on LDR values.
8. **LDR and Green LEDs**: Lights green LEDs based on LDR values.
9. **LDR and Orange LEDs**: Lights orange LEDs based on LDR values.
10. **Line Pattern with LDR**: LEDs turn on sequentially based on LDR.
11. **Fast Servo Rotation with LEDs**: Servo rotates fast with all LEDs on.
12. **Custom LED Flashing**: All LEDs flash rapidly.

## Installation

1. **Clone this repository**:
   ```bash
   git clone https://github.com/username/repository.git
