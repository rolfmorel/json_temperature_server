//#include "../globals.h"
#include "globals.h"
#include "views.h"
#include "models.h"

#include "controllers.h"

void readPOSTparam(WebServer &server)
{
  bool repeat;
  char name[16], value[16];
  do
  {
    repeat = server.readPOSTparam(name, 16, value, 16);
    int16_t nam = strtoul(name + 1, NULL, 10);
    int16_t val = strtoul(value, NULL, 10);
    switch (name[0])
    {
      case 'S':
        // valid name and value for centralHeatingControl()
        if (nam >= 0 && nam <= 2 && val >= 0 && val <= 2)
        {
          centralHeatingControl(nam, val);
          mainTemperatureRegulation();
        }
        break;
      case 'T':
        // valid name and value for desiredTemperatureControl()
        if ((nam == 0 && val >= DEGREE_INPUT_WHOLE_MIN &&
             val <= DEGREE_INPUT_WHOLE_MAX) ||
            (nam == 1 && val >= 0 && val <= 99))
        {
          desiredTemperatureControl(nam, val);
          mainTemperatureRegulation();
        }
        break;
      case 'A':
        // valid name and value for timerControl()
        if (nam == 0 && val >= 0 && val <= 360)
        {
          timerControl(nam, val);
          mainTemperatureRegulation();
        }
        break;
      case 'M':
        // valid name and value for valveControl()
        if (nam >= 0 && nam <= 2 && val >= 0 && val <= 3 &&
            !motor_reset_timeout[nam])
        {
          valveRegulation(nam, val);
          motorReset();
        }
        break;
    }
  } while (repeat);
}

User authCheck(WebServer &server)
{
  User user;
  user.auth = false;

  // guest:
  if (server.checkCredentials("Z3Vlc3Q6"))
  {
    user.auth = true;
    user.admin = false;
    user.id = 0;
  }
  // admin:password
  else if (server.checkCredentials("YWRtaW46cGFzc3dvcmQ="))
  {
    user.auth = true;
    user.admin = true;
    user.id = 1;
  }
  // api:secret
  else if (server.checkCredentials("YXBpOnNlY3JldA=="))
  {
    user.auth = true;
    user.admin = true;
    user.id = 2;
  }
  // user:user
  else if (server.checkCredentials("dXNlcjp1c2Vy"))
  {
    user.auth = true;
    user.admin = false;
    user.id = 3;
  }
  return user;
}

void indexPageCmd(WebServer &server, WebServer::ConnectionType type,
                  char *url_tail, bool tail_complete)
{
  User user = authCheck(server);

  if (!user.auth)
  {
    server.httpUnauthorized();
    return;
  }

  if (user.admin && type == WebServer::POST)
  {
    readPOSTparam(server);
    server.httpSeeOther(URL_INDEX_PAGE "/");
    return;
  }

  serveIndexPage(server, user);
}

void apiPageCmd(WebServer &server, WebServer::ConnectionType type,
                char *url_tail, bool tail_complete)
{
  User user = authCheck(server);

  if (!user.auth || user.id != 2)
  {
    server.httpUnauthorized();
    return;
  }

  if (user.admin && type == WebServer::POST)
  {
    readPOSTparam(server);
    server.httpNoContent();
    return;
  }

  //TODO: implement urlparams api

  serveApiPage(server, user);
}

void valveControlPageCmd(WebServer &server, WebServer::ConnectionType type,
                         char *url_tail, bool tail_complete)
{
  User user = authCheck(server);

  if (!user.auth)
  {
    server.httpUnauthorized();
    return;
  }

  if (user.admin && type == WebServer::POST)
  {
    readPOSTparam(server);
    server.httpSeeOther(URL_VALVE_CONTROL_PAGE);
    return;
  }

  serveValveControlPage(server, user);
}

// void urlPageCmd(WebServer &server, WebServer::ConnectionType type,
//                 char **url_path, char *url_tail, bool tail_complete)
// {
//   User user = authCheck(server);

//   if (!user.auth)
//   {
//     server.httpUnauthorized();
//     return;
//   }

//   uint8_t len_url_path = 0, n = 0;
//   while (*(url_path + n++)) ++len_url_path;

//   if (len_url_path)
//   {
//     if (strcmp(url_path[0], "400") == 0)
//     {
//       server.httpFail();
//       if (!tail_complete) {
//         server << "buffer to small for url\n";
//       }
//       return;
//     }
//   }

//   server.httpSuccess();

//   server << "url_parts=" << len_url_path << "\n";

//   for (n = 0; n < len_url_path; n++)
//   {
//     server << "url_part" << n << "=";
//     char *p = url_path[n];

//     while (*p != 0) server << *p++;

//     server << "\n";
//   }

//   server << "url_tail=";
//   while (*url_tail) server << *(url_tail++);
//   server << '\n';
//   server << tail_complete;
// }
