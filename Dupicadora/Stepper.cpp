#include "Arduino.h"
#include "Stepper.h"

Stepper::Stepper(int Pin_enable,int Pin_dir,int Pin_steps, int Pin_sensor){
    this->Pin_enable = Pin_enable;
    this->Pin_dir = Pin_dir;
    this->Pin_steps = Pin_steps;
    this->Pin_sensor = Pin_sensor;
}

void Stepper::setSpeed(long speed){
    this->step_delay = speed;
}

void Stepper::enable(){
    digitalWrite(Pin_enable,HIGH);
    this->status = true;
}
void Stepper::disable(){
    digitalWrite(Pin_enable,LOW);
    this->status = false;
}

void Stepper::MoveSteps(bool dir, uint16_t steps){
    if (!this->status){
        enable();
    }
    this->direction = dir;
    this->steps_number = steps;
    digitalWrite(Pin_dir, direction);
    for (int step = 0; step < this->steps_number; step++){
        digitalWrite(Pin_steps,HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps,LOW);
        delayMicroseconds(step_delay);
    }
}

void Stepper::reset(){
    if (!this->status){
        enable();
    }
    direction = false;
    digitalWrite(Pin_dir, direction);
    while(!digitalRead(Pin_sensor)){
        digitalWrite(Pin_steps,HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps,LOW);
        delayMicroseconds(step_delay);
    }
}

bool Stepper::getStatus(){
    return this->status;
}