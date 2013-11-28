#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>

#define WEBDUINO_FAVICON_DATA ""

#include <WebServer.h>

#include "globals.h"

#include "views.h"
#include "controllers.h"

#ifdef DEV
uint8_t const ip[] = { 10, 0, 0, 82 };
#else
uint8_t const ip[] = { 10, 0, 0, 82 };
#endif

uint32_t uptime, seconds_already_up;

Sensor sensors[MAX_TEMPERATURE_SENSORS] = { 0 };

uint8_t mac[] = { 0xDE, 0xBD, 0xBE, 0xDF, 0xFE, 0xCD };

OneWire onewire(8);

WebServer webserver;

bool resetTimer()
{
  if (millis() > 2147483647) {
    seconds_already_up += (millis() / 1000);
    extern volatile unsigned long timer0_millis;
    cli();
    timer0_millis = 0;
    sei();
    return true;
  }
  return false;
}

void setOneWireTemperature(void)
{
  for (uint8_t idx = 0; idx < MAX_TEMPERATURE_SENSORS; idx++)
  {
    if (!onewire.search(sensors[idx].address))
    {
      do {
#ifndef DEV
        sensors[idx].integer = INVALID_TEMPERATURE;
        sensors[idx].fraction = 0;
#else
        sensors[idx].integer = DEV_TEMPERATURE;
        sensors[idx].fraction = DEV_TEMPERATURE_FRAC;
#endif
      } while (++idx < MAX_TEMPERATURE_SENSORS);

      break;
    }

    onewire.reset();
    onewire.select(sensors[idx].address);
    onewire.write(0x44); // start conversion, with parasite power on at the end

    onewire.reset();
    onewire.select(sensors[idx].address);
    onewire.write(0xBE);

    int16_t data = onewire.read();
    data |= (onewire.read() << 8);
    if (data & 0x8000) // if negative
    {
      data = (data ^ 0xffff) + 1; // 2's comp
    }
    // multiply by (100 * 0.0625) or 6.25
    uint16_t mul_data = (data * 6) + data / 4;

    sensors[idx].integer = mul_data / 100;
    sensors[idx].fraction = mul_data % 100;
  }

  onewire.reset_search();
}

int main(void)
{
  uint32_t set_temperature_timer = 0;

  // arduino library init
  init();

  Ethernet.begin(mac, ip);
  webserver.begin();

  webserver.setDefaultCommand(&indexPageCmd);

  setOneWireTemperature();

  // main loop
  for (;;)
  {
    if (set_temperature_timer < millis())
    {
      resetTimer();

      setOneWireTemperature();

      set_temperature_timer = millis() + 750;
    }

    webserver.processConnection();
  }
}
