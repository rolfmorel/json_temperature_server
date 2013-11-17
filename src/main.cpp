#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>

// #define WEBDUINO_FAVICON_DATA { \
//   0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, \
//   0x10, 0x00, 0x01, 0x00, 0x04, 0x00, 0x28, 0x01, \
//   0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, \
//   0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, \
//   0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, \
//   0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x13, 0x0b, \
//   0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x10, 0x00, \
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x0f, 0x0b, \
//   0x9e, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xf2, \
//   0xff, 0x00, 0x07, 0x97, 0xea, 0x00, 0x1d, 0x94, \
//   0xf7, 0x00, 0x07, 0x52, 0xea, 0x00, 0x00, 0x00, \
//   0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x88, 0x82, 0x28, 0x88, 0x00, 0x00, 0x00, 0x08, \
//   0x82, 0x27, 0x72, 0x28, 0x80, 0x00, 0x00, 0x88, \
//   0x77, 0x55, 0x55, 0x77, 0x88, 0x00, 0x08, 0x87, \
//   0x75, 0x53, 0x35, 0x57, 0x78, 0x80, 0x08, 0x77, \
//   0x55, 0x13, 0x31, 0x55, 0x77, 0x80, 0x08, 0x77, \
//   0x55, 0x33, 0x33, 0x55, 0x77, 0x80, 0x08, 0x87, \
//   0x75, 0x34, 0x43, 0x57, 0x78, 0x80, 0x00, 0x88, \
//   0x77, 0x53, 0x35, 0x77, 0x88, 0x00, 0x00, 0x08, \
//   0x87, 0x56, 0x65, 0x78, 0x80, 0x00, 0x00, 0x00, \
//   0x88, 0x75, 0x57, 0x88, 0x00, 0x00, 0x00, 0x00, \
//   0x08, 0x75, 0x57, 0x80, 0x00, 0x00, 0x00, 0x00, \
//   0x08, 0x87, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x87, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, \
//   0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0xfc, 0x3f, \
//   0x45, 0x52, 0xf0, 0x0f, 0x52, 0x4f, 0xe0, 0x07, \
//   0x4c, 0x45, 0xc0, 0x03, 0x3a, 0x5c, 0x80, 0x01, \
//   0x6f, 0x67, 0x80, 0x01, 0x6d, 0x44, 0x80, 0x01, \
//   0x61, 0x00, 0x80, 0x01, 0x44, 0x41, 0xc0, 0x03, \
//   0x53, 0x44, 0xe0, 0x07, 0x4f, 0x4f, 0xf0, 0x0f, \
//   0x43, 0x3a, 0xf8, 0x1f, 0x72, 0x6f, 0xf8, 0x1f, \
//   0x61, 0x6d, 0xfc, 0x3f, 0x69, 0x6c, 0xfe, 0x7f, \
//   0x20, 0x28, 0xfe, 0x7f, 0x36, 0x29 }

#include "globals.h"

//#include "server/models.h"
//#include "server/views.h"
//#include "server/controllers.h"
#include "models.h"
#include "views.h"
#include "controllers.h"

#ifdef DEV
uint8_t const ip[] = { 10, 0, 0, 81 };
#else
uint8_t const ip[] = { 10, 0, 0, 80 };
#endif


uint8_t mac[] = { 0xDE, 0xBD, 0xBE, 0xDF, 0xFE, 0xCD };

uint32_t main_timer, set_temperature_timer;

OneWire onewire(8);

WebServer webserver;

bool resetTimer()
{
  if (uptime > 2147483647 && motor_reset_timeout[0] == 0 &&
      motor_reset_timeout[1] == 0 && motor_reset_timeout[2] == 0 &&
      floor_timeout == 0 && air_timeout == 0)
  {
    seconds_already_up += (uptime / 1000);
    extern volatile unsigned long timer0_millis;
    cli();
    timer0_millis = 0;
    sei();
    return true;
  }
  return false;
}

void valveStartupSequence()
{
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n], LOW);
  }
#if ((defined(VALVE_CLOSE_CCW) && VALVE_START_POSITION == -1) || \
     (!defined(VALVE_CLOSE_CCW) && VALVE_START_POSITION == 1))
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n*2+2], HIGH);
  }
  delay(OPEN_TIME);
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n*2+2], LOW);
  }
#elif ((!defined(VALVE_CLOSE_CCW) && VALVE_START_POSITION == -1) || \
       (defined(VALVE_CLOSE_CCW) && VALVE_START_POSITION == 1))
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n * 2 + 2], HIGH);
    digitalWrite(relay_pin[n * 2 + 3], HIGH);
  }
  delay(OPEN_TIME);
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n * 2 + 2], LOW);
    digitalWrite(relay_pin[n * 2 + 3], LOW);
  }
#elif VALVE_START_POSITION == 0
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n*2+2], HIGH);
    //TODO: Check which way is closed, as not shut all the valve at ones, VALVE_CLOSE_CCW etc.
    digitalWrite(relay_pin[n*2+3], HIGH);
  }
  delay(OPEN_TIME);
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n*2+3], LOW);
  }
  delay(HALF_OPEN_TIME);
  for (uint8_t n = 0; n <= 2; n++)
  {
    digitalWrite(relay_pin[n*2+2], LOW);
  }
#else
#error please use VALVE_CLOSE_CCW and VALVE_START_POSITION macros correctly
#endif
}

void setOneWireTemperature(Temperature * temp)
{
  uint8_t address[8];
  for (uint8_t n = 0; n < MAX_TEMPERATURE_SENSORS; n++)
  {
    if (!onewire.search(address))
    {
      for (uint8_t i = n; i < MAX_TEMPERATURE_SENSORS; i++)
      {
#ifndef DEV
        temp[i].integer = INVALID_TEMPERATURE;
        temp[i].fraction = 0;
#else
        temp[i].integer = DEV_TEMPERATURE;
        temp[i].fraction = DEV_TEMPERATURE_FRAC;
#endif
      }
      onewire.reset_search();
      break;
    }

    onewire.reset();
    onewire.select(address);
    onewire.write(0x44); // start conversion, with parasite power on at the end

    onewire.reset();
    onewire.select(address);
    onewire.write(0xBE);

    int16_t data = onewire.read();
    data |= (onewire.read() << 8);
    if (data & 0x8000) // if negative
    {
      data = (data ^ 0xffff) + 1; // 2's comp
    }
    // multiply by (100 * 0.0625) or 6.25
    uint16_t mul_data = (data * 6) + data / 4;

    temp[n].integer = mul_data / 100;
    temp[n].fraction = mul_data % 100;
  }
}

int main(void)
{
  // arduino library init
  init();

  // port declaration
  for (uint8_t n = 0; n <= 7; n++) {
    pinMode(relay_pin[n], OUTPUT);
  }

#ifndef DEV
  valveStartupSequence();
#endif

  Ethernet.begin(mac, ip);
  webserver.begin();

  webserver.setDefaultCommand(&indexPageCmd);
  webserver.addCommand(URL_VALVE_CONTROL_PAGE, &valveControlPageCmd);
  webserver.addCommand(URL_API_PAGE, &apiPageCmd);

  // webserver.setUrlPathCommand(&urlPageCmd);

  for (uint8_t n = 0; n < MAX_TEMPERATURE_SENSORS; n++)
  {
#ifndef DEV
    temperature[n].integer = INVALID_TEMPERATURE;
    temperature[n].fraction = 0;
#else
    temperature[n].integer = DEV_TEMPERATURE;
    temperature[n].fraction = DEV_TEMPERATURE_FRAC;
#endif
  }

  main_timer = 0;
  set_temperature_timer = 0;

  // main loop
  for (;;)
  {
    uptime = millis();

    if (main_timer < uptime)
    {
      // check if internal timer needs to be reset
      if (resetTimer())
        set_temperature_timer = millis() + 750;

      mainTemperatureRegulation();

      motorReset();

      main_timer = millis() + 250;
    }

    if (set_temperature_timer < uptime)
    {
      setOneWireTemperature(temperature);

      set_temperature_timer = millis() + 750;
    }

    webserver.processConnection();
  }
}
