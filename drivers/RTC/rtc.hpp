#ifndef RTC_H
#define RTC_H

#include "../../LIB/STD_TYPE.hpp"
#include "../../app_config.hpp"
#include "mbed.h"

/*
 * @brief Initializes the rtc.
 * Sets time to 00:00 and starts the internal 1-second ticker.
 */
void RTC_Init(void);

/*
 * @brief Resets the rtc time to 00 minutes and 00 seconds.
 */
void RTC_Reset(void);

/*
 * @brief Retrieves the current time from the rtc.
 * @param p_minutes Pointer to a variable where the current minutes will be stored.
 * @param p_seconds Pointer to a variable where the current seconds will be stored.
 */
void RTC_GetTime(u16* p_minutes, u16* p_seconds);

/*
 * @brief Internal tick function
 */
void RTC_TickUpdate(void);

#endif /* RTC_H */