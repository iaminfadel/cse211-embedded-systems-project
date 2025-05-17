#include "rtc.hpp"

static volatile u16 s_current_seconds = 0;
static volatile u16 s_current_minutes = 0;

static Ticker s_rtc_internal_ticker;

void RTC_Init(void) {
    s_current_seconds = 0;
    s_current_minutes = 0;
    // Attach the tick update function to trigger every 1.0 second
    s_rtc_internal_ticker.attach(callback(&RTC_TickUpdate), 1.0f);
}

void RTC_Reset(void) {
    s_current_seconds = 0;
    s_current_minutes = 0;
}

void RTC_GetTime(u16* p_minutes, u16* p_seconds) {
    // Ensure pointers are valid before dereferencing
    if ((p_minutes != NULL) && (p_seconds != NULL)) {
        *p_minutes = s_current_minutes;
        *p_seconds = s_current_seconds;
    }
}

void RTC_TickUpdate(void) {
    s_current_seconds++;
    if (s_current_seconds > RTC_MAX_SECONDS) {
        s_current_seconds = 0;
        s_current_minutes++;
        if (s_current_minutes > RTC_MAX_MINUTES) {
            s_current_minutes = 0; // Rolls over
        }
    }
}