#include "seven_segment_display.hpp"


// Common ANODE 7-segment patterns 
static const u8 s_digit_segment_patterns[10] = {
    (u8)(~0x3FU), /* 0 -> 0xC0 */
    (u8)(~0x06U), /* 1 -> 0xF9 */
    (u8)(~0x5BU), /* 2 -> 0xA4 */
    (u8)(~0x4FU), /* 3 -> 0xB0 */
    (u8)(~0x66U), /* 4 -> 0x99 */
    (u8)(~0x6DU), /* 5 -> 0x92 */
    (u8)(~0x7DU), /* 6 -> 0x82 */
    (u8)(~0x07U), /* 7 -> 0xF8 */
    (u8)(~0x7FU), /* 8 -> 0x80 */
    (u8)(~0x6FU)  /* 9 -> 0x90 */
};

// Digit selection patterns for common ANODE display (which digit's anode to power)
static const u8 s_digit_select_patterns[DISPLAY_NUM_DIGITS] = {
    0x01U, /* Digit 0 (Left) */
    0x02U, /* Digit 1 */
    0x04U, /* Digit 2 */
    0x08U  /* Digit 3 (Right) */
};

// Decimal point segment for common anode (0 = ON, 1 = OFF)
#define DECIMAL_POINT_SEGMENT_BIT (0x80U) // (10000000b)

// Module-static variables for current display state (for multiplexing)
static u16  s_current_display_number = 0;
static bool    s_is_decimal_point_shown = false;
static u8 s_decimal_point_position = 0U; // 0-3
static u8 s_active_digit_index = 0U;     // Current digit being refreshed (0-3)


void SevenSegment_Init(void) {
    ShiftRegister_Init(); // Initialize the underlying shift register driver
    s_current_display_number = 0;
    s_is_decimal_point_shown = false;
    s_decimal_point_position = 0U;
    s_active_digit_index = 0U;
}


void SevenSegment_SetDisplayValue(u16 number, bool show_decimal_point, u8 decimal_pos) {
    // Clamp number to displayable range (0-9999)
    if (number < 0) {
        s_current_display_number = 0; 
    } else if (number > 9999) {
        s_current_display_number = 9999; // Max displayable
    } else {
        s_current_display_number = number;
    }

    s_is_decimal_point_shown = show_decimal_point;

    if (decimal_pos < DISPLAY_NUM_DIGITS) {
        s_decimal_point_position = decimal_pos;
    } else {
        s_decimal_point_position = 0U;
    }
}


void SevenSegment_RefreshDisplay(void) {
    u8 extracted_digits[DISPLAY_NUM_DIGITS];
    u8 segment_data_for_current_digit;
    u8 digit_selector_data;
    u16 temp_number = s_current_display_number;

    // Extract individual digits from the number
    // Rightmost digit (index 3) is number % 10
    extracted_digits[3] = (u8)(temp_number % 10);
    temp_number /= 10;
    extracted_digits[2] = (u8)(temp_number % 10);
    temp_number /= 10;
    extracted_digits[1] = (u8)(temp_number % 10);
    temp_number /= 10;
    extracted_digits[0] = (u8)(temp_number % 10); // Leftmost digit

    // Get the segment pattern for the digit to be displayed at s_active_digit_index
    if (extracted_digits[s_active_digit_index] < 10U) {
        segment_data_for_current_digit = s_digit_segment_patterns[extracted_digits[s_active_digit_index]];
    } else {
        segment_data_for_current_digit = (u8)(~0x00U); // All segments OFF 
    }

    // Activate decimal point if required for the current active digit
    if (s_is_decimal_point_shown && (s_active_digit_index == s_decimal_point_position)) {
        segment_data_for_current_digit &= (u8)(~DECIMAL_POINT_SEGMENT_BIT); // Clear bit to turn ON
    }

    // Get the digit selector pattern for the current active digit
    digit_selector_data = s_digit_select_patterns[s_active_digit_index];

    // Send data to shift registers
    // Latch LOW before shifting
    ShiftRegister_SetLatch(0);

    // Shift out segment data first, then digit selector data
    ShiftRegister_OutputByte(segment_data_for_current_digit);
    ShiftRegister_OutputByte(digit_selector_data);

    // Latch HIGH to transfer shifted data to storage registers
    ShiftRegister_SetLatch(1);

    // Move to the next digit for the next refresh cycle
    s_active_digit_index++;
    if (s_active_digit_index >= DISPLAY_NUM_DIGITS) {
        s_active_digit_index = 0U;
    }
}