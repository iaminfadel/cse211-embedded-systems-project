#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include "../../LIB/STD_TYPE.hpp"
#include "mbed.h"
#include "../../app_config.hpp" 

/*
 * @brief Initializes the GPIO pins used for the shift register.
 */
void ShiftRegister_Init(void);

/*
 * @brief Sets the state of the latch pin.
 * @param state If 0, sets latch pin LOW; otherwise, sets HIGH.
 */
void ShiftRegister_SetLatch(u8 state);

/*
 * @brief Shifts out a single byte of data to the shift register.
 * Data is shifted MSB first.
 * @param data_byte The 8-bit value to shift out.
 */
void ShiftRegister_OutputByte(u8 data_byte);

#endif /* SHIFT_REGISTER_H */