#include "stdint.h"

class Stepper
{
private:
    // Pines
    int Pin_dir;
    int Pin_enable;
    int Pin_steps;
    int Pin_sensor;
    // Varibles
    int step_delay;
    int position;
    int reset_speed;
    bool direction;
    bool status;
    bool reset_direction;

public:
    // Constructor
    Stepper(int Pin_enable, int Pin_dir, int Pin_steps, int Pin_sensor, bool reset_direction, int reset_speed);
    // Funciones
    void enable();
    void disable();
    void setSpeed(long speed);
    void MoveSteps(int16_t steps);
    void MovePosition(int position);
    void reset();
    void sound(int frecuency);
    bool getStatus();
    int getPosition();
};
