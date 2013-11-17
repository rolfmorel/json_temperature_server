#ifndef __VIEWS_H
#define __VIEWS_H

#define WEBDUINO_NO_IMPLEMENTATION
#include <WebServer.h>

void serveIndexPage(WebServer &server, User &user);

void serveValveControlPage(WebServer &server, User &user);

void serveApiPage(WebServer &server, User &user);

#endif
