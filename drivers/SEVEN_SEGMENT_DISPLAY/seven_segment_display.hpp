#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include "../../LIB/STD_TYPE.hpp"
#include "mbed.h"
#include "../SHIFT_REGISTER/shift_register.hpp"
#include "../../app_config.hpp" 

/*
 * @brief Initializes the 7-segment display module and its underlying shift register.
 */
void SevenSegment_Init(void);

/*
 * @brief Sets the 4-digit numerical value and decimal point to be displayed.
 * This function updates the internal buffer that SevenSegment_RefreshDisplay uses.
 * @param number The number to display (0-9999). Values outside this range may be clamped.
 * @param show_decimal_point True to enable the decimal point, false to disable.
 * @param decimal_pos Digit position for the decimal point (0=leftmost, 1, 2, 3=rightmost).
 * Ignored if show_decimal_point is false.
 */
void SevenSegment_SetDisplayValue(u16 number, bool show_decimal_point, u8 decimal_pos);

/*
 * @brief Refreshes one digit of the 7-segment display.
 * This function implements multiplexing and should be called periodically
 */
void SevenSegment_RefreshDisplay(void);

#endif /* SEVEN_SEGMENT_DISPLAY_H */