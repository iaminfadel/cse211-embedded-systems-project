#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "mbed.h" 

// Shift register pins
#define SR_LATCH_PIN_ST_CP          D4          // Storage Register Clock Pin
#define SR_CLOCK_PIN_SH_CP          D7          // Shift Register Clock Pin
#define SR_DATA_PIN_DS              D8          // Serial Data In

// Buttons
#define BUTTON_S1_PIN               A1
#define BUTTON_S3_PIN               A3

// Potentiometer
#define POTENTIOMETER_PIN           A0

// Display properties
#define DISPLAY_NUM_DIGITS          4U          // Number of digits on the display
#define DISPLAY_REFRESH_INTERVAL_MS 2U          // Interval for refreshing a single digit (ms)

// Debounce time
#define BUTTON_ACTION_DEBOUNCE_MS   200U

// RTC time limits
#define RTC_MAX_SECONDS             59U 
#define RTC_MAX_MINUTES             99U

// ADC and Voltage calculation constants
#define ADC_MAX_RAW_VALUE           65535U      // Max value from read_u16()
#define ADC_REFERENCE_VOLTAGE       3.3f        // MCU ADC reference voltage
#define VOLTAGE_DISPLAY_MULTIPLIER  1000.0f     

#endif /* APP_CONFIG_H */