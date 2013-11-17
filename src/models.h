#ifndef __MODELS_H
#define __MODELS_H

void mainTemperatureRegulation();

void motorReset();

void centralHeatingControl(short name, short value);

void desiredTemperatureControl(short name, short value) ;

void valveRegulation(short name, short value);

void timerControl(short name, short value);

#endif
