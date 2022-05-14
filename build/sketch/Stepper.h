#line 1 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Stepper.h"
class Stepper{
    //Constructor
    Stepper(int Pin_enable,int Pin_dir,int Pin_steps);

    private:
        int Pin_dir;
        int Pin_enable;
        int Pin_steps;
        int direction;
        int steps_number;
        int step_delay;

    public:
        void setSpeed(long speed);
};