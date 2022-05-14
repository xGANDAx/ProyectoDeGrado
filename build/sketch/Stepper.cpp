#line 1 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Stepper.cpp"
#include "Arduino.h"
#include "Stepper.h"

Stepper::Stepper(int Pin_enable,int Pin_dir,int Pin_steps){
    this->Pin_enable = Pin_enable;
    this->Pin_dir = Pin_dir;
    this->Pin_steps = Pin_steps;
}

void Stepper::setSpeed(long speed){
    this->step_delay = speed;
}