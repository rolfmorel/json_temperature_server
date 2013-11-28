#include "globals.h"

#include "views.h"

void serveIndexPage(WebServer &server, User &user)
{
  server.httpSuccess("application/json");

  server << "{ ";

  server << "\"sensors\" : [ ";
  for (uint8_t idx = 0; idx < MAX_TEMPERATURE_SENSORS; idx++)
  {
    if (sensors[idx].integer > INVALID_TEMPERATURE)
    {
      if (idx > 0)
        server << ", ";

      server << "{ \"0x";

      for (uint8_t addr_idx = 0;
           addr_idx < sizeof((struct Sensor *)0)->address; addr_idx++)
        server.print((unsigned char) sensors[idx].address[addr_idx], HEX);

      server << "\" : ";

      server << sensors[idx].integer << ".";

      if (sensors[idx].fraction < 10)
        server << "0";
      server << sensors[idx].fraction << " ";

      server << "} ";
    }
  }
  server << "], ";

  server << "\"seconds_up\" : " << seconds_already_up + (uptime / 1000);

  server << " }";
}
