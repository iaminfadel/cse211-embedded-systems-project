#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "../../app_config.hpp"
#include "mbed.h"
#include "../../LIB/STD_TYPE.hpp"

/*
 * @brief Initializes the input handler module (buttons and potentiometer).
 * Configures button pins with internal pull-ups.
 */
void InputHandler_Init(void);

/*
 * @brief Checks if button S1 is newly pressed (detects a press event).
 * @return True if a new press of S1 is detected (since last call where it was not pressed),
 * false otherwise.
 */
bool InputHandler_IsButtonS1NewlyPressed(void);

/*
 * @brief Checks the current state of button S3 (active LOW).
 * @return True if S3 is currently being pressed, false otherwise.
 */
bool InputHandler_IsButtonS3Active(void);

/*
 * @brief Reads the analog voltage from the potentiometer.
 * @return The voltage as a f32
 */
f32 InputHandler_ReadPotentiometerVoltage(void);

#endif /* INPUT_HANDLER_H */