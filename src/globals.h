#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <Arduino.h>

template <typename Type>
inline Print &operator << (Print &obj, Type arg)
{
  obj.print(arg);
  return obj;
}

#define MAX_TEMPERATURE_SENSORS 16

#define INVALID_TEMPERATURE -274
#ifdef DEV
#define DEV_TEMPERATURE 31
#define DEV_TEMPERATURE_FRAC 33
#endif

#define PREFIX ""
#define URL_INDEX_PAGE ""
#define URL_API_PAGE "api"

struct User {
  bool auth : 1;
  bool admin : 1;
  unsigned int id : 6;
};

struct Sensor {
  uint8_t address[8];
  int16_t integer;
  uint8_t fraction;
};

extern uint32_t seconds_already_up;

extern Sensor sensors[MAX_TEMPERATURE_SENSORS];

#endif
