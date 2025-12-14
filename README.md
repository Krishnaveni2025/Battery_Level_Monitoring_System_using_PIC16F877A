# Battery_Level_Monitoring_System_using_PIC16F877A

This project implements a Battery Level Monitoring System using a PIC16F877A microcontroller (simulated in Proteus). It monitors voltage levels and categorizes them into Low, Medium, or High states, displaying the status on a 16x2 LCD.

## Project Overview

-   **Platform:** MPLAB X IDE
-   **Simulation:** Proteus Design Suite
-   **Language:**  C
-   **Microcontroller:** PIC16F877A (Configured for 6MHz XTAL)
-   **Type:** Embedded Application (Non-Bare-metal / Simulation Focus)

## Features

-   **Real-time Voltage Monitoring:** Simulates voltage changes via button inputs.
-   **LCD Display:** Shows current voltage (e.g., "17.6V") and status (LOW/MEDIUM/HIGH).
-   **Interactive Controls:**
    -   **RB4:** Reset to Low State (Default 17.5V)
    -   **RB5:** Increase Voltage (+0.1V)
    -   **RB6:** Decrease Voltage (-0.1V)
    -   **RB7:** Reset to Medium State (17.6V)
-   **Status Indication:**
    -   **LOW:** Below 17.6V
    -   **MEDIUM:** 17.6V - 20.5V
    -   **HIGH:** 20.6V - 27.5V

## Hardware Requirements (Simulated)

-   PIC16F877A Microcontroller
-   16x2 Character LCD
-   Push Buttons (connected to PORTB)
-   Power Supply (simulated via code logic)

## Getting Started

1.  **Open Project:** Open the `.X` project folder in MPLAB X IDE.
2.  **Build:** Compile the code to generate the `.hex` file.
3.  **Simulate:** Load the `.hex` file into your PIC microcontroller component in Proteus.
4.  **Run:** Start the simulation and use the buttons on PORTB to interact with the system.

## Code Structure

-   `disp_batt_levels.c`: Main source code containing initialization, LCD driver, and main control loop.
-   `init()`: Initializes ports and LCD.
-   `switchscanning()`: Handles button inputs and logic updates.
-   `lcd_command()` / `lcd_data()`: LCD communication functions.

  https://github.com/user-attachments/assets/0b02f1b5-d1ca-4870-8811-4ac77bb90bf5
