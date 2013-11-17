#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <Arduino.h>

template <typename Type>
inline Print &operator << (Print &obj, Type arg)
{
  obj.print(arg);
  return obj;
}

#define MAX_TEMPERATURE_SENSORS 3

#define VALVE_CLOSE_CCW
// options: 1: open, 0: half open, -1: closed
#define VALVE_START_POSITION 1

#define HALF_OPEN_TIME 75000  // 75 seconds
#define OPEN_TIME 155000  // 155 seconds
#define TIMEOUT_IN_SECONDS 600L  // 10 minutes
#define TIMEOUT ((uint32_t) (TIMEOUT_IN_SECONDS * 1000))

#define DEGREE_INPUT_WHOLE_MIN 16
#define DEGREE_INPUT_WHOLE_MAX 36
#define DEGREE_INPUT_FRACT_STEP 25
#define DEGREE_INPUT_FRACT_MAX (DEGREE_INPUT_FRACT_STEP * ((100 / \
        DEGREE_INPUT_FRACT_STEP) - 1))
#define TIMER_OPTIONS 15, 30, 60, 90, 120, 180
#define TIMER_OPTIONS_LEN 6

#define INVALID_TEMPERATURE -274
#ifdef DEV
#define DEV_TEMPERATURE 31
#define DEV_TEMPERATURE_FRAC 33
#endif

#define PREFIX ""
#define URL_INDEX_PAGE ""
#define URL_API_PAGE "api"
#define URL_VALVE_CONTROL_PAGE "valve_control"

struct User {
  bool auth : 1;
  bool admin : 1;
  unsigned int id : 6;
};

struct Temperature {
  int16_t integer;
  uint8_t fraction;
};

extern uint8_t const relay_pin[];

extern uint16_t const timer_options[];

extern int8_t  motor_pos[];

extern uint8_t temp_setting[];

extern uint16_t air_timer;

extern bool relay[], Setting[];

extern uint32_t uptime, air_timeout, seconds_already_up, floor_timeout,
                motor_reset_timeout[];

extern Temperature temperature[];

#endif
