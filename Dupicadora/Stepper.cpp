#include "Arduino.h"
#include "Stepper.h"
#include "stdint.h"

// Constructor
Stepper::Stepper(int Pin_enable, int Pin_dir, int Pin_steps, int Pin_sensor, bool reset_direction, int reset_speed)
{
    this->Pin_enable = Pin_enable;
    this->Pin_dir = Pin_dir;
    this->Pin_steps = Pin_steps;
    this->Pin_sensor = Pin_sensor;
    this->reset_direction = reset_direction;
    this->reset_speed = reset_speed;
}

// Asigna la velocidad del motor (en revision)
void Stepper::setSpeed(long speed)
{
    step_delay = speed;
}

// Habilita el motor
void Stepper::enable()
{
    digitalWrite(Pin_enable, LOW);
    status = true;
}

// Deshabilita el motor
void Stepper::disable()
{
    digitalWrite(Pin_enable, HIGH);
    status = false;
}

// Se mueve el motor una cantidad de pasos
void Stepper::MoveSteps(int16_t steps)
{
    if (!status)
    {
        enable();
    }
    if (steps < 0)
    {
        digitalWrite(Pin_dir, reset_direction);
    }
    else
    {
        digitalWrite(Pin_dir, !reset_direction);
    }

    for (int step = 0; step < abs(steps); step++)
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

    step_delay = reset_speed;
    digitalWrite(Pin_dir, reset_direction);
    while (digitalRead(Pin_sensor))
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(step_delay);
    }

    step_delay = 10 * reset_speed;
    digitalWrite(Pin_dir, !reset_direction);
    while (!digitalRead(Pin_sensor))
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(step_delay);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(step_delay);
    }

    digitalWrite(Pin_dir, reset_direction);
    while (digitalRead(Pin_sensor))
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
void Stepper::sound(int frecuency)
{
    if (!status)
    {
        enable();
    }

    digitalWrite(Pin_dir, reset_direction);
    for (int step = 0; step < 20000; step++)
    {
        digitalWrite(Pin_steps, HIGH);
        delayMicroseconds(frecuency);
        digitalWrite(Pin_steps, LOW);
        delayMicroseconds(frecuency);
    }
}
