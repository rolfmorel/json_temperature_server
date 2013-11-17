#ifndef __CONTROLLERS_H
#define __CONTROLLERS_H

#define WEBDUINO_NO_IMPLEMENTATION
#include <WebServer.h>

void indexPageCmd(WebServer &server, WebServer::ConnectionType type,
                  char *url_tail, bool tail_complete);

void valveControlPageCmd(WebServer &server, WebServer::ConnectionType type,
                         char *url_tail, bool tail_complete);

void apiPageCmd(WebServer &server, WebServer::ConnectionType type,
                char *url_tail, bool tail_complete);

#endif
