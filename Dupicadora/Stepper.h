class Stepper
{
    // Constructor
    Stepper(int Pin_enable, int Pin_dir, int Pin_steps, int Pin_sensor);

private:
    int position;
    int Pin_dir;
    int Pin_enable;
    int Pin_steps;
    int Pin_sensor;
    int step_delay;
    bool direction;
    bool status;
    uint16_t steps_number;

public:
    void enable();
    void disable();
    void setSpeed(long speed);
    void MoveSteps(bool dir, uint16_t steps);
    void reset();
    bool getStatus();
    int getPosition();
};