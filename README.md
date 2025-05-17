# CSE211S Final Project - Real-Time Clock and Voltage Display

## Overview
This project is the final assignment for CSE211S: Introduction to Embedded Systems - Spring 2025. The implementation uses a NUCLEO-F401RE board with an Arduino Multifunction Shield to create a system that can:
1. Function as a Real-Time Clock (RTC) displaying minutes and seconds
2. Display the voltage reading from the on-board potentiometer

## Hardware Components
- **NUCLEO-F401RE** microcontroller board
- **Arduino Multifunction Shield** containing:
  - 4-digit 7-segment display
  - Pushbuttons (S1, S2, S3)
  - Potentiometer
  - Other components (LEDs, buzzer, etc.)

## Project Requirements
As specified in the course project document:

### Real-Time Clock (RTC) Mode
- After board reset, the 7-segment display shows elapsed time in minutes and seconds starting from zero
- Format: The higher two digits show minutes, the lower two digits show seconds
- Pressing switch S1 at any time restarts the clock from zero

### Analog Signal Value Display Mode
- The on-board potentiometer's variable voltage is used as input to the on-chip ADC
- When switch S3 is pressed, the 7-segment display shows the ADC's input voltage value in volts
- When S3 is released, the display returns to showing elapsed time
- The RTC continues running even while S3 is pressed

## Implementation Details

### Input Handling (Interrupt-Driven)
- **Button S1 (Reset)**: Configured to trigger an interrupt on the falling edge (when pressed)
- **Button S3 (Mode)**: Configured to trigger interrupts on both falling edge (when pressed) and rising edge (when released)
- Interrupts set volatile flag variables that the main loop checks to determine system behavior
- This approach is more efficient than polling as it eliminates the need to constantly check button states

### Real-Time Clock Implementation
- Maintains an internal timer that increments seconds and minutes
- Time values are formatted for the 7-segment display (MMSS format)
- Can be reset to 00:00 via button S1 press

### ADC and Voltage Display
- Reads analog value from the on-board potentiometer
- Converts ADC reading to voltage value
- Formats voltage for proper display with decimal point

### Display Management
- Uses a ticker-based refresh mechanism for the 7-segment display
- Displays either time or voltage based on the state of button S3
- Handles decimal point placement for appropriate value formatting

## Software Architecture

### Modular Design
The code follows a modular structure with clear separation of concerns:

1. **Input Handler Module** (`input_handler.hpp/cpp`)
   - Manages button inputs via interrupt-driven approach
   - Handles potentiometer analog reading
   - Provides clean API for other modules to check input states

2. **Real-Time Clock Module** (`rtc.hpp/cpp`)
   - Keeps track of elapsed time
   - Manages time reset functionality
   - Provides functions to read current time values

3. **Seven Segment Display Module** (`seven_segment_display.hpp/cpp`)
   - Controls the 7-segment display output
   - Manages display refreshing via ticker interrupt
   - Handles digit multiplexing and decimal point control

4. **Main Application** (`main.cpp`)
   - Coordinates the overall system logic
   - Determines the display mode based on button inputs
   - Updates the display with appropriate values

### Key Functions

- `InputHandler_Init()`: Configures buttons and attaches interrupt handlers
- `InputHandler_IsButtonS1NewlyPressed()`: Checks if S1 was pressed since last check
- `InputHandler_IsButtonS3Active()`: Checks current state of S3 button
- `InputHandler_ReadPotentiometerVoltage()`: Reads and converts potentiometer value
- `RTC_Init()`: Initializes the real-time clock functionality
- `RTC_GetTime()`: Retrieves current minutes and seconds
- `RTC_Reset()`: Resets the clock to zero
- `SevenSegment_Init()`: Configures the 7-segment display
- `SevenSegment_SetDisplayValue()`: Updates the display with a new value

## Project Files
- `main.cpp` - Main application logic and system coordination
- `app_config.hpp` - Configuration constants and pin definitions
- `input_handler.hpp/cpp` - Button interrupt handling and potentiometer reading
- `rtc.hpp/cpp` - Real-time clock functionality and time tracking
- `seven_segment_display.hpp/cpp` - Control of 7-segment display
- `LIB/STD_TYPE.hpp` - Standard data type definitions

## Code Implementation and Key Features

### Polling vs. Interrupt-Based Approach
This implementation uses interrupts for button handling but polling for the main scheduling and system handling. The buttons' ISRs change the value of global flags which are polled in the main loop.

## Development Notes
- Interrupts are configured in the InputHandler_Init() function
- Time continues to increment even when in voltage display mode
- The display shows MM.SS format for time and V.VVV format for voltage
