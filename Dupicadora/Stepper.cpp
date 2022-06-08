#include "Arduino.h"
#include "Stepper.h"
#include "stdint.h"

// Constructor
Stepper::Stepper(int Pin_enable, int Pin_dir, int Pin_steps, int Pin_sensor, bool reset_direction)
{
    this->Pin_enable = Pin_enable;
    this->Pin_dir = Pin_dir;
    this->Pin_steps = Pin_steps;
    this->Pin_sensor = Pin_sensor;
    this->reset_direction = reset_direction;
}

// Asigna la velocidad del motor (en revision)
void Stepper::setSpeed(long speed)
{
    step_delay = speed;
}

// Habilita el motor
void Stepper::enable()
{
    digitalWrite(Pin_enable, HIGH);
    status = true;
}

// Deshabilita el motor
void Stepper::disable()
{
    digitalWrite(Pin_enable, LOW);
    status = false;
}

// Se mueve el motor una cantidad de pasos
void Stepper::MoveSteps(int16_t steps)
{
    if (!status)
    {
        enable();
    }
    if (steps<0)
    {
        digitalWrite(Pin_dir, reset_direction);
    }
    else
    {
        digitalWrite(Pin_dir, !reset_direction);
    }

    for (int step = 0; step < steps; step++)
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(step_delay);
    }
}

// Mueve el motor a la posicion inicial
void Stepper::reset()
{
    if (!status)
    {
        enable();
    }

    digitalWrite(Pin_dir, reset_direction);

    while (!digitalRead(Pin_sensor))
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(step_delay);
    }

    position = 0;
}

// Mueve el motor a una posicion deseada
void Stepper::MovePosition(int position)
{
    if (!status)
    {
        enable();
    }

    if (this->position > position)
    {
        digitalWrite(Pin_dir, reset_direction);
    }
    else
    {
        digitalWrite(Pin_dir, !reset_direction);
    }

    for (int step = 0; step < abs(this->position - position); step++)
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(step_delay);
    }
    this->position = position;
}

// Comprueba si el motor esta habilitado
bool Stepper::getStatus()
{
    return status;
}

// Retorna la posicion del motor
int Stepper::getPosition()
{
    return position;
}

// Emite un pitido
void Stepper::sound()
{
    if (status)
    {
        enable();
    }

    for (int step = 0; step < 100; step++)
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(10);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(10);
    }
}