//#include "../globals.h"
#include "globals.h"

#include "views.h"

P(br) = "<br />\n";

P(hr) = "<hr />\n";

P(startHTMLhead) = "<html>\n"
                   "<head>\n"
                   "<title>Central Heating</title>\n";

P(endHead) = "</head>\n"
             "<body>\n"
             "<div id='main'>\n";

P(endHtml) = "</div>\n"
             "</body>\n"
             "</html>";

P(floorHeatingMenu) = "Floor Heating Menu\n";
P(centralAirHeatingMenu) = "Central Air Heating Menu\n";
P(floorHeatingOff) = "Floor Heating is OFF\n";
P(centralAirHeatingOff) = "Central Air Heating is OFF\n";

// CSS source:
// .button, .dropdown {
// background-color: blue;
// color: yellow;
// display: inline-block;
// outline: none;
// cursor: pointer;
// text-align: center;
// text-decoration: none;
// font: bold 16px/100% Arial, Helvetica, sans-serif;
// padding: .5em 0.5em .5em;
// text-shadow: 0 1px 1px rgba(0,0,0,.3);
// border-radius: .5em;
// box-shadow: 0 1px 2px rgba(0,0,0,.2);
// }

// select.dropdown option {
// background-color: blue;
// }

// .button:hover {
// text-decoration: none;
// }

// .button:active {
// position: relative;
// top: 1px;
// }

// body {
// font-family: 'Arial'; font-size: large; color: black;
// }

// .red {
// color: red;
// }

// .xl {
// font-size: x-large;
// }

// .xxl {
// font-size: xx-large;
// }

// hr {
// width: 100%
// }

// #main {
// text-align: center;
// margin: 0 0 auto;
// }
// </style>

// CSS minified:
P(CSSstyle) = "<style>\n"
              ".button,.dropdown{background-color:blue;color:#FF0;display:inli"
              "ne-block;outline:0;cursor:pointer;text-align:center;text-decora"
              "tion:none;font:bold 16px/100% Arial,Helvetica,sans-serif;text-s"
              "hadow:0 1px 1px rgba(0,0,0,.3);border-radius:.5em;box-shadow:0 "
              "1px 2px rgba(0,0,0,.2);padding:.5em}select.dropdown option{back"
              "ground-color:blue;}.button:hover{text-decoration:none}.button:a"
              "ctive{position:relative;top:1px}body{font-family:Arial;font-siz"
              "e:large;color:#000}.red{color:red}.xl{font-size:x-large}.xxl{fo"
              "nt-size:xx-large}hr{width:100%}#main {text-align:center; marg"
              "in: 0 0 auto;}\n"
              "</style>\n";

// JavaScript source:
// <script type='text/javascript'>
// // var w = window.innerWidth >= 600 ? window.innerWidth: 600;
// // document.getElementById('main').style.width = w;
// // var viewPortTag = document.createElement('meta');
// // viewPortTag.name = 'viewport';
// // viewPortTag.content = 'width=' + w + ', initial-scale=1.0';
// // document.getElementsByTagName('head')[0].appendChild(viewPortTag);
// function UpdateTime() {
// var currentTime = document.getElementById('time').innerHTML.split(' ');
// var days = currentTime[0], hours = currentTime[2],
// minutes = currentTime[4], seconds = currentTime[6];
// seconds++;
// if (seconds == 60) {
// minutes++; seconds = 0;
// }
// if (minutes == 60) {
// hours++; minutes = 0;
// }
// if (hours == 24) {
// days++; hours = 0;
// }
// document.getElementById('time').innerHTML = days + " days " + hours +
// " hours " + minutes + " minutes " + seconds + " seconds";
// setTimeout('UpdateTime()', 1000);
// }
// UpdateTime()
// </script>

// JavaScript source:
// <script type='text/javascript'>
// function CountBack() {
// var count = document.getElementsByClassName('count');
// for (var i=0; i < count.length; i++) {
// document.getElementsByClassName('count')[i].innerHTML = count[i].innerHTML - 1;
// if (count[i].innerHTML == 0) {
// location.reload(true);
// }
// }
// setTimeout('CountBack()',

// 000);
// }
// if (document.getElementById('ms-count') != null) {
// setTimeout('CountBack()', document.getElementById('ms-count').innerHTML);
// } else {
// CountBack();
// }
// </script>

// JavaScript minified:
P(JavaScript1) = "<script type='text/javascript'>\n"
                 "function UpdateTime(){var e=document.getElementById('time')."
                 "innerHTML.split(' ');var t=e[0],n=e[2],r=e[4],i=e[6];i++;if("
                 "i==60){r++;i=0}if(r==60){n++;r=0}if(n==24){t++;n=0}document."
                 "getElementById('time').innerHTML=t+' days '+n+' hours '+r+' "
                 "minutes '+i+' seconds';setTimeout('UpdateTime()',1e3)}Update"
                 "Time()\n"
                 "</script>\n";

// JavaScript minified:
P(countJavaScript1) = "<script type='text/javascript'>\n"
                      "function CountBack(){var e=document.getElementsByClassN"
                      "ame('count');for(var t=0;t<e.length;t++){document.getEl"
                      "ementsByClassName('count')[t].innerHTML=e[t].innerHTML-"
                      "1;if(e[t].innerHTML==0){location.reload(true)}}setTimeo"
                      "ut('CountBack()',";

// JavaScript minified:
P(countJavaScript2) = "000)}if(document.getElementById('ms-count')!=null){setT"
                      "imeout('CountBack()',document.getElementById('ms-count'"
                      ").innerHTML)}else{CountBack()}\n"
                      "</script>\n";

//TODO: optimize or rewrite to request state of motors instead of actions of motors
void htmlButtonsPrint(WebServer &server, uint8_t action)
{
  switch (action)
  {
    case 0:
      P(htmlButtonsPrint0) = "<form action='' method='post'>\n"
      "<button type='submit' name='S0' value='1' class=button>\n"
      "Turn Floor Heating ON</button><br />\n"
      "</form>\n";
      server.printP(htmlButtonsPrint0);
      break;
    case 1:
      P(htmlButtonsPrint1) = "<form action='' method='post'>\n"
      "<button type='submit' name='S0' value='0' class=button>\n"
      "Turn Floor Heating OFF</button><br />\n"
      "</form>\n";
      server.printP(htmlButtonsPrint1);
      break;
    case 2:
      P(htmlButtonsPrint2) = "<form action='' method='post'>\n"
      "<button type='submit' name='S1' value='1' class=button>\n"
      "Turn Central Air Heating ON</button><br />\n"
      "</form>\n";
      server.printP(htmlButtonsPrint2);
      break;
    case 3:
      P(htmlButtonsPrint3) = "<form action='' method='post'>\n"
      "<button type='submit' name='S1' value='0' class=button>\n"
      "Turn Central Air Heating OFF</button><br />\n"
      "</form>\n";
      server.printP(htmlButtonsPrint3);
      break;
  }
}

void htmlSelectOptionsPrint(WebServer &server, uint8_t value,
                            bool selected = false)
{
  P(htmldropdownprint0) = "<option value='";
  P(htmldropdownprint1) = "' selected='selected";
  P(htmldropdownprint2) = "'>";
  P(htmldropdownprint3) = "</option>\n";
  server.printP(htmldropdownprint0);
  server << value;
  if (selected) server.printP(htmldropdownprint1);
  server.printP(htmldropdownprint2);
  if (value < 10) server << 0;
  server << value;
  server.printP(htmldropdownprint3);
}

void valveButtonsPrint(WebServer &server, uint8_t valve, int8_t action)
{
  P(valveButtonsPrint0) = "<button type='submit' name='M";
  server.printP(valveButtonsPrint0);
  server << valve;
  P(valveButtonsPrint1) = "' value='";
  server.printP(valveButtonsPrint1);
  server << action;
  P(valveButtonsPrint2) = "' class=button>";
  server.printP(valveButtonsPrint2);
  switch (action)
  {
    case 0:
      P(valveButtonsPrint3) = "Open Valve";
      server.printP(valveButtonsPrint3);
      break;
    case 1:
      P(valveButtonsPrint4) = "Half Open Valve";
      server.printP(valveButtonsPrint4);
      break;
    case 2:
      P(valveButtonsPrint5) = "Half Close Valve";
      server.printP(valveButtonsPrint5);
      break;
    case 3:
      P(valveButtonsPrint6) = "Close Valve";
      server.printP(valveButtonsPrint6);
      break;
  }
  P(valveButtonsPrint7) = "</button>\n";
  server.printP(valveButtonsPrint7);
}

void htmlTimePrint(WebServer &server, uint32_t const &time_in_seconds)
{
  P(htmlTimePrint0) = "<object id='time'>";
  P(htmlTimePrint1) = "</object>";
  server.printP(htmlTimePrint0);
  server << ((time_in_seconds / 86400)) << " days ";
  server << ((time_in_seconds / 3600) % 24) << " hours ";
  server << ((time_in_seconds / 60) % 60) << " minutes ";
  server << ((time_in_seconds) % 60) << " seconds\n";
  server.printP(htmlTimePrint1);
}

void htmlTemperatureSensorsPrint(WebServer &server,
                                 Temperature const * const temp)
{
  P(htmlTemperatureSensorsPrint0) = " on Floor Heating return is";
  P(htmlTemperatureSensorsPrint1) = " in Living Room is";
  P(htmlTemperatureSensorsPrint2) = "\n<font class='xl red'>";
  for (uint8_t n = 0; n < MAX_TEMPERATURE_SENSORS; n++)
  {
    if (temp[n].integer > INVALID_TEMPERATURE)
    {
      server << "Sensor" << n;
      switch (n)
      {
        case 0:
          server.printP(htmlTemperatureSensorsPrint0);
          break;
        case 1:
          server.printP(htmlTemperatureSensorsPrint1);
          break;
      }
      server.printP(htmlTemperatureSensorsPrint2);
      server << " " << temp[n].integer << ".";
      if (temp[n].fraction < 10) server << '0';
      server << temp[n].fraction << "&#176C</font><br />\n";
    }
  }
}

void htmlRefreshButtonPrint(WebServer &server)
{
  P(htmlRefreshButtonPrint0) = "<input type='button' class=button value="
  "'Refresh Page' onclick='window.location.reload()'>\n";
  server.printP(htmlRefreshButtonPrint0);
}

void htmlButtonToIndexPage(WebServer &server)
{
  P(htmlButtonToIndexPage0) = "<form action='/" URL_INDEX_PAGE
  "' method='link'>\n"
  "<button type='submit' class=button>Index Page</button>\n"
  "</form>\n";
  server.printP(htmlButtonToIndexPage0);
}

void htmlButtonToValveControlPage(WebServer &server)
{
  P(htmlButtonToValveControlPage0) = "<form action='/" URL_VALVE_CONTROL_PAGE
  "' method='link'>\n"
  "<button type='submit' class=button>Valve Control Page</button>\n"
  "</form>\n";
  server.printP(htmlButtonToValveControlPage0);
}

void serveIndexPage(WebServer &server, User &user)
{
  server.httpSuccess();

  server.printP(startHTMLhead);

  server.printP(CSSstyle);

  server.printP(endHead);

  P(indexPagePrint0) = "<center>\n";
  server.printP(indexPagePrint0);

  htmlTimePrint(server, (seconds_already_up + (uptime / 1000)));

  server.printP(hr);

  htmlTemperatureSensorsPrint(server, temperature);

  server.printP(hr);

  if ((Setting[0] || Setting[1]) || user.admin)
  {
    P(indexPagePrint5) = "<font class=xxl>\n"
                         "Central Heating control</font><br />\n";
    server.printP(indexPagePrint5);
  }

  if (Setting[0] && !Setting[1])
  {
    server.printP(floorHeatingMenu);
    P(indexPagePrint6) = "<br />\n"
                         "Floor Heating is on when\n"
                         "<font class='xl red'>";
    server.printP(indexPagePrint6);
    server << " " << temperature[0].integer << ".";
    if (temperature[0].fraction <= 9) server << '0';
    server << temperature[0].fraction << "&#176C</font>\n";
    P(indexPagePrint7) = "(sensor0) is lower than \n"
                         "<font class='xl red'>";
    server.printP(indexPagePrint7);
    server << temp_setting[0] << ".";
    if (temp_setting[1] <= 9) server << 0;
    server << temp_setting[1];
    P(indexPagePrint8) = "&#176C</font><br />\n";
    server.printP(indexPagePrint8);

    if (user.admin)
    {
      P(indexPagePrint9) = "Input target temperature:"
                           "<br />\n<font class='xl red'>\n"
                           "<form action='' method='post'>\n"
                           "<select name='T0' class=dropdown>\n";
      server.printP(indexPagePrint9);
      for (short n = DEGREE_INPUT_WHOLE_MIN; n <= DEGREE_INPUT_WHOLE_MAX; n++)
      {
        if (n == temp_setting[0])
        {
          htmlSelectOptionsPrint(server, n, true);
        }
        else
        {
          htmlSelectOptionsPrint(server, n);
        }
      }
      P(indexPagePrint14) = "</select>.<select name='T1' class=dropdown>\n";
      server.printP(indexPagePrint14);
      for (short n = 0; n <= DEGREE_INPUT_FRACT_MAX;
           n = n + DEGREE_INPUT_FRACT_STEP)
      {
        if (n == temp_setting[1])
        {
          htmlSelectOptionsPrint(server, n, true);
        }
        else
        {
          htmlSelectOptionsPrint(server, n);
        }
      }
      P(indexPagePrint15) = "</select>&#176C<br />\n<button type='submit'"
                            " class='button'>submit</button></font></form>\n";
      server.printP(indexPagePrint15);
      htmlButtonsPrint(server, 1);
      server.printP(centralAirHeatingOff);
      htmlButtonsPrint(server, 2);
    }

  }
  else if (Setting[1])
  {
    server.printP(centralAirHeatingMenu);
    server.printP(br);
    if (air_timeout == 0)
    {
      if (user.admin)
      {
        P(indexPagePrint16) = "Input for how many minutes Central Air "
                              "Heating should stay on:\n";
        server.printP(indexPagePrint16);
        P(indexPagePrint17) = "<form action='' method='post'>\n"
                              "<select name='A0' class=dropdown>\n";
        server.printP(indexPagePrint17);
        for (uint8_t n = 0; n < TIMER_OPTIONS_LEN; n++)
        {
          htmlSelectOptionsPrint(server, timer_options[n]);
        }
        P(indexPagePrint18) = "</select><br />\n<button type='submit' "
                              "class='button'>submit</button>"
                              "</form>\n";
        server.printP(indexPagePrint18);
      }
    }
    else
    {
      P(indexPagePrint19) = "Central Air Heating "
                            "is on for <font class='xl red'>"
                            "<object class=count>";
      server.printP(indexPagePrint19);
      server << ((air_timeout - uptime) / 60000) + 1;
      P(indexPagePrint20) = "</object><object id='ms-count' "
                            "hidden=true>";
      server.printP(indexPagePrint20);
      server << (air_timeout - uptime) % 60000;
      P(indexPagePrint21) = "</object></font> more minutes<br />\n";
      server.printP(indexPagePrint21);
    }
    server.printP(countJavaScript1);
    server << "60";
    server.printP(countJavaScript2);

    if (user.admin) htmlButtonsPrint(server, 3);
  }
  else
  {
    server.printP(floorHeatingOff);
    if (user.admin)
    {
      htmlButtonsPrint(server, 0);
    }
    else
    {
      server.printP(br);
    }
    server.printP(centralAirHeatingOff);
    if (user.admin) htmlButtonsPrint(server, 2);
  }
  server.printP(hr);

  htmlButtonToValveControlPage(server);
  server.printP(hr);

  htmlRefreshButtonPrint(server);
  server.printP(hr);

  for (uint8_t n = 0; n <= 7; n++)
  {
    server << relay[n];
  }
  server << "\n";

  server.printP(JavaScript1);

  server.printP(endHtml);
}

void serveApiPage(WebServer &server, User &user)
{
  server.httpSuccess();

  unsigned long time_in_seconds = seconds_already_up + (uptime / 1000);
  server << "time_in_seconds=" << time_in_seconds << "\n";

  server << "FloorHeating=" << Setting[0] << "\n";

  server << "AirHeating=" << Setting[1] << "\n";

  for (uint8_t n = 0; n < MAX_TEMPERATURE_SENSORS; n++)
  {
    if (temperature[n].integer > INVALID_TEMPERATURE)
    {
      server << "Sensor[" << n << "]=";
      server << temperature[n].integer << ".";
      server << temperature[n].fraction <<"\n";
    }
  }

  server << "temp_setting=" << temp_setting[0] << ".";
  server << temp_setting[1] << "\n";

  for (uint8_t n = 0; n <= 2; n++)
  {
    server << "motor_pos[" << n << "]=" << motor_pos[n] << "\n";
  }

  for (uint8_t n = 0; n <= 2; n++)
  {
    server << "motor_reset_timeout[" << n << "]=";
    server << (motor_reset_timeout[n] ?
               ((motor_reset_timeout[n] - uptime) / 1000): 0) << "\n";
  }

  server << "air_timeout=";
  server << (air_timeout ? ((air_timeout - uptime) / 1000): 0) << "\n";

  server << "relay=";
  for (uint8_t n = 0; n <= 7; n++) server << relay[n];
  server << "\n";
}

void serveValveControlPage(WebServer &server, User &user)
{
  server.httpSuccess();

  server.printP(startHTMLhead);

  server.printP(CSSstyle);

  server.printP(endHead);

  P(ValveControlPage0) = "<center>\n";
  server.printP(ValveControlPage0);

  htmlTimePrint(server, (seconds_already_up + (uptime / 1000)));
  server.printP(hr);

  htmlTemperatureSensorsPrint(server, temperature);
  server.printP(hr);

  P(ValveControlPage1) = "<font class=xxl>\nValve Control"
                         "</font><br />\n";
  server.printP(ValveControlPage1);

  for (uint8_t n = 0; n <= 2; n++)
  {
    P(ValveControlPage2) = "Valve ";
    server.printP(ValveControlPage2);
    server << n + 1; // server << n + 1; for one based html
    if (!relay[n * 2 + 2])
    {
      P(ValveControlPage3) = "<form action='' method="
                            "'post'>\n";
      P(ValveControlPage4) = "</form>\n";
      //TODO: Optimize Memory footprint
      if (motor_pos[n] == -1)
      {
        P(ValveControlPage5) = " is closed";
        server.printP(ValveControlPage5);
        if (user.admin)
        {
          server.printP(ValveControlPage3);
          valveButtonsPrint(server, n, 1);
          valveButtonsPrint(server, n, 0);
          server.printP(ValveControlPage4);
        }
        else
        {
          server.printP(br);
        }
      }
      else if (motor_pos[n] == 0)
      {
        P(ValveControlPage6) = " is half open ";
        server.printP(ValveControlPage6);
        if (user.admin)
        {
          server.printP(ValveControlPage3);
          valveButtonsPrint(server, n, 0);
          if ((motor_pos[0] + motor_pos[1] + motor_pos[2]) > -1)
          {
            valveButtonsPrint(server, n, 3);
          }
          server.printP(ValveControlPage4);
        }
        else
        {
          server.printP(br);
        }
      }
      else if (motor_pos[n] == 1)
      {
        P(ValveControlPage7) = " is open";
        server.printP(ValveControlPage7);
        if (user.admin)
        {
          server.printP(ValveControlPage3);
          valveButtonsPrint(server, n, 2);
          if ((motor_pos[0] + motor_pos[1] + motor_pos[2]) > -1)
          {
            valveButtonsPrint(server, n, 3);
          }
          server.printP(ValveControlPage4);
        }
        else
        {
          server.printP(br);
        }
      }
    }
    else
    {
      server.printP(br);
      P(ValveControlPage8) = "operation will be done in:\n"
      "<font class='xl red'><object class=count>";
      server.printP(ValveControlPage8);
      server << ((motor_reset_timeout[n] - uptime) / 1000) + 1;
      P(ValveControlPage9) = "</object></font> seconds<br />";
      server.printP(ValveControlPage9);
      server << "\n";
    }
  }
  server.printP(countJavaScript1);
  server << "1";
  server.printP(countJavaScript2);

  server.printP(hr);

  htmlButtonToIndexPage(server);
  server.printP(hr);

  htmlRefreshButtonPrint(server);
  server.printP(hr);

  for (uint8_t n = 0; n <= 7; n++) server << relay[n];
  server << "\n";

  server.printP(JavaScript1);

  server.printP(endHtml);
}
