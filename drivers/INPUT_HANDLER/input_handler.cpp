#include "input_handler.hpp"

// Pin definitions
static InterruptIn s_button_s1_pin(BUTTON_S1_PIN);
static InterruptIn s_button_s3_pin(BUTTON_S3_PIN);
static AnalogIn s_potentiometer_pin(POTENTIOMETER_PIN);

// Button state flags
static volatile bool s_s1_button_pressed_flag = false;
static volatile bool s_s3_button_active_flag = false;

// Interrupt handlers
static void S1_Button_Pressed_Handler(void)
{
    // Set the flag when the button is pressed (rising edge)
    s_s1_button_pressed_flag = true;
}

static void S3_Button_Pressed_Handler(void)
{
    // Button S3 is active (pressed)
    s_s3_button_active_flag = !s_s3_button_active_flag;
}


void InputHandler_Init(void)
{
    // Configure button pins with internal pull-ups
    s_button_s1_pin.mode(PullUp);
    s_button_s3_pin.mode(PullUp);

    s_button_s1_pin.fall(callback(&S1_Button_Pressed_Handler));
    s_button_s3_pin.fall(callback(&S3_Button_Pressed_Handler));
}

bool InputHandler_IsButtonS1NewlyPressed(void)
{
    // Check if the flag is set, then clear it
    if (s_s1_button_pressed_flag)
    {
        s_s1_button_pressed_flag = false;
        return true;
    }
    
    return false;
}

bool InputHandler_IsButtonS3Active(void)
{
    // Return the current state flag for S3
    return s_s3_button_active_flag;
}

f32 InputHandler_ReadPotentiometerVoltage(void)
{
    u16 adc_raw_value;
    f32 voltage;

    adc_raw_value = s_potentiometer_pin.read_u16();

    // Convert raw ADC value to voltage: (raw / max_raw) * ref_voltage
    voltage = ((f32)adc_raw_value / ADC_MAX_RAW_VALUE) * ADC_REFERENCE_VOLTAGE;

    return voltage;
}