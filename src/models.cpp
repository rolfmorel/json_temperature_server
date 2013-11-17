//#include "../globals.h"
#include "globals.h"

#include "models.h"

void mainTemperatureRegulation()
{
  if (air_timer > 0)
  {
    air_timeout = (air_timer * 60000) + uptime;
    air_timer = 0;
  }

  if (Setting[0] || Setting[1])
  {
    if (Setting[1])
    {
      if (air_timeout != 0)
      {
        if (air_timeout > uptime)
        {
          digitalWrite(relay_pin[0], HIGH);
          digitalWrite(relay_pin[1], HIGH);
          relay[0] = true;
          relay[1] = true;
        }
        else
        {
          digitalWrite(relay_pin[0], LOW);
          digitalWrite(relay_pin[1], LOW);
          relay[0] = false;
          relay[1] = false;
          air_timeout = 0;
          Setting[1] = false;
        }
      }
      else
      {
        digitalWrite(relay_pin[0], LOW);
        digitalWrite(relay_pin[1], LOW);
        relay[0] = false;
        relay[1] = false;
      }
    }
    else
    {
      air_timeout = 0;
      if (Setting[0])
      {
        if (floor_timeout < uptime)
        {
          if (temperature[0].integer > INVALID_TEMPERATURE)
          {
            if ((temp_setting[1] == 0 &&
                 (temperature[0].integer < temp_setting[0])) ||
                (temperature[0].integer + 1 <= temp_setting[0] ||
                 (temperature[0].integer == temp_setting[0] &&
                  temperature[0].fraction < temp_setting[1])))
            {
              digitalWrite(relay_pin[0], HIGH);
              digitalWrite(relay_pin[1], LOW);
              relay[0] = true;
              relay[1] = false;
              floor_timeout = uptime + TIMEOUT;
            }
            else
            {
              digitalWrite(relay_pin[0], LOW);
              digitalWrite(relay_pin[1], LOW);
              relay[0] = false;
              relay[1] = false;
            }
          }
        }
      }
      else
      {
        floor_timeout = 0;
      }
    }
  }
  else
  {
    digitalWrite(relay_pin[0], LOW);
    digitalWrite(relay_pin[1], LOW);
    relay[0] = false;
    relay[1] = false;
  }
}

void motorReset()
{
  for (uint8_t n = 0; n <= 2; n++)
  {
    if (motor_reset_timeout[n] > 0 && motor_reset_timeout[n] < uptime)
    {
      digitalWrite(relay_pin[n * 2 + 2], LOW);
      digitalWrite(relay_pin[n * 2 + 3], LOW);
      relay[n * 2 + 2] = false;
      relay[n * 2 + 3] = false;
      motor_reset_timeout[n] = 0;
    }
  }
}

void centralHeatingControl(short name, short value) {
  Setting[name] = !!(value);
  if (!!value)
  {
    air_timeout = 0;
    floor_timeout = 0;
  }
}

void desiredTemperatureControl(short name, short value) {
  temp_setting[name] = value;
  floor_timeout = 0;
}

void valveRegulation(short name, short value) { //TODO: clean up further
  if (!motor_reset_timeout[name])
  {
    switch (value)
    {
      case 0: // Open Valve
        if (motor_pos[name] <= 0) // checks if valve isn't open
        {
          digitalWrite(relay_pin[name * 2 + 2], HIGH);
          relay[name * 2 + 2] = true;
#ifdef VALVE_CLOSE_CCW
          digitalWrite(relay_pin[name * 2 + 3], HIGH);
          relay[name * 2 + 3] = true;
#endif
          if (motor_pos[name] == 0)
            motor_reset_timeout[name] = (uptime + HALF_OPEN_TIME);
          else if (motor_pos[name] == -1)
            motor_reset_timeout[name] = (uptime + OPEN_TIME);
          motor_pos[name] = 1;
        }
        break;
      case 1: // Half Open Valve
        if (motor_pos[name] == -1) // checks if valve is closed
        {
          digitalWrite(relay_pin[name * 2 + 2], HIGH);
          relay[name * 2 + 2] = true;
#ifdef VALVE_CLOSE_CCW
          digitalWrite(relay_pin[name * 2 + 3], HIGH);
          relay[name * 2 + 3] = true;
#endif
          motor_reset_timeout[name] = (uptime + HALF_OPEN_TIME);
          motor_pos[name] = 0;
        }
      break;
    case 2: // Half Close Valve
      if (motor_pos[name] == 1) // checks if valve is open
      {
        digitalWrite(relay_pin[name * 2 + 2], HIGH);
        relay[name * 2 + 2] = true;
#ifndef VALVE_CLOSE_CCW
        digitalWrite(relay_pin[name * 2 + 3], HIGH);
        relay[name * 2 + 3] = true;
#endif
        motor_reset_timeout[name] = (uptime + HALF_OPEN_TIME);
        motor_pos[name] = 0;
      }
      break;
    case 3: // Close Valve
      // don't let all valves be closed at the same time AND checks if valve
      // isn't closed
      if ((motor_pos[0] + motor_pos[1] + motor_pos[2]) > -1 &&
          motor_pos[name] >= 0)
      {
        digitalWrite(relay_pin[name * 2 + 2], HIGH);
        relay[name * 2 + 2] = true;
#ifndef VALVE_CLOSE_CCW
        digitalWrite(relay_pin[name * 2 + 3], HIGH);
        relay[name * 2 + 3] = true;
#endif
        if (motor_pos[name] == 0)
          motor_reset_timeout[name] = (uptime + HALF_OPEN_TIME);
        else if (motor_pos[name] == 1)
          motor_reset_timeout[name] = (uptime + OPEN_TIME);
        motor_pos[name] = -1;
      }
      break;
    }
  }
}

void timerControl(short name, short value)
{
  air_timer = value;
}
