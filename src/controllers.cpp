#include "globals.h"
#include "views.h"

#include "controllers.h"

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
    server.httpSeeOther(URL_INDEX_PAGE "/");
    return;
  }

  serveIndexPage(server, user);
}
