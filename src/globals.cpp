#include <Arduino.h>

#include "globals.h"

#include "favicon.h"
#include <WebServer.h>

uint8_t const relay_pin[] = { A0, A1, 2, 3, 4, 5, 6, 7 };
uint16_t const timer_options[] = { TIMER_OPTIONS };

#if VALVE_START_POSITION == -1
int8_t motor_pos[] = { -1, -1, -1 };
#elif VALVE_START_POSITION == 0
int8_t motor_pos[] = { 0, 0, 0 };
#elif VALVE_START_POSITION == 1
int8_t motor_pos[] = { 1, 1, 1 };
#endif

uint8_t temp_setting[] = { 0, 0 };

uint16_t air_timer;

bool relay[] = { false, false, false, false, false, false, false, false },
     Setting[] = { false, false };

uint32_t uptime, air_timeout, seconds_already_up = 0, floor_timeout = 0,
         motor_reset_timeout[] = { 0, 0, 0 };

Temperature temperature[MAX_TEMPERATURE_SENSORS];
