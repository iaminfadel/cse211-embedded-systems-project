#include "mbed.h"
#include "app_config.hpp"
#include "rtc.hpp"
#include "input_handler.hpp"
#include "seven_segment_display.hpp"
#include "./LIB/STD_TYPE.hpp"

// Ticker for refreshing the 7-segment display
static Ticker s_display_refresh_driver_ticker;

// Enum for display modes
typedef enum {
    DISPLAY_MODE_TIME,
    DISPLAY_MODE_VOLTAGE
} display_mode_t;

static display_mode_t s_current_display_mode = DISPLAY_MODE_TIME;

int main(void) {
    // Initialize all modules
    InputHandler_Init();
    RTC_Init();
    SevenSegment_Init();

    // Start the display refresh ticker.
    // It calls SevenSegment_RefreshDisplay to update one digit at a time.
    s_display_refresh_driver_ticker.attach_us(callback(&SevenSegment_RefreshDisplay),
                                             (DISPLAY_REFRESH_INTERVAL_MS * 1000U));

    while (1) {
        // Input Processing
        // We used external interrupts to update the flags, and polled the flag status in main loop
        if (InputHandler_IsButtonS1NewlyPressed()) { // Check if reset button was pressed
            RTC_Reset(); // Reset RTC
        }

        if (InputHandler_IsButtonS3Active()) { // Check mode
            s_current_display_mode = DISPLAY_MODE_VOLTAGE; 
        } else {
            s_current_display_mode = DISPLAY_MODE_TIME;
        }

        // Logic and Display Update
        if (s_current_display_mode == DISPLAY_MODE_VOLTAGE) { // Display Voltage
            f32 voltage_reading;
            u16 voltage_to_display;

            // Display: V.VVV (Decimal point after the first digit (index 0))
            voltage_reading = InputHandler_ReadPotentiometerVoltage(); 
            voltage_to_display = (u16)(voltage_reading * VOLTAGE_DISPLAY_MULTIPLIER);
            SevenSegment_SetDisplayValue(voltage_to_display, true, 0U);

        } else { // Display Time
            u16 current_minutes, current_seconds;
            u16 time_to_display; // Format MMSS

            // Display: MM.SS (Decimal point after the second digit (index 1))
            RTC_GetTime(&current_minutes, &current_seconds);
            time_to_display = (current_minutes * 100) + current_seconds;
            SevenSegment_SetDisplayValue(time_to_display, true, 1U);
        }

        ThisThread::sleep_for(50ms); // Adjust polling frequency
    }
}