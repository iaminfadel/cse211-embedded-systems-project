#include "shift_register.hpp"

static DigitalOut s_latch_pin(SR_LATCH_PIN_ST_CP);
static DigitalOut s_clock_pin(SR_CLOCK_PIN_SH_CP);
static DigitalOut s_data_pin(SR_DATA_PIN_DS);


void ShiftRegister_Init(void) {
    s_latch_pin = 0; // Initialize latch pin to LOW
    s_clock_pin = 0; // Initialize clock pin to LOW
    s_data_pin  = 0; // Initialize data pin to LOW
}


void ShiftRegister_SetLatch(u8 state) {
    s_latch_pin = (state != 0U) ? 1 : 0;
}

static void ShiftOutMSBFirst(u8 value_to_shift) {
     
    for (int i = 7; i >= 0; --i) {
        // Set data pin based on the current bit
        s_data_pin = ((value_to_shift & (1U << i)) != 0U) ? 1 : 0;

        // Pulse the shift clock (SH_CP)
        s_clock_pin = 1;
        s_clock_pin = 0; // Data shifted on rising or falling edge
    }
}

void ShiftRegister_OutputByte(u8 data_byte) {
    ShiftOutMSBFirst(data_byte);
}