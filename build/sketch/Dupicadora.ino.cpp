#include <Arduino.h>
#line 1 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Dupicadora.ino"
#include "Stepper.h"

#define Pin_Rele 32
#define Pin_Enable_Motor_X 13 
#define Pin_Dir_Motor_X 12
#define Pin_Pulse_Motor_X 14
#define Pin_Enable_Motor_A 27 
#define Pin_Dir_Motor_A 26
#define Pin_Pulse_Motor_A 25
#define Pin_Sensor_X 34
#define Pin_Sensor_A 35
#define Pin_MOSI 23
#define Pin_MISO 19
#define Pin_CLK 18
#define Pin_CS_G 5
#define Pin_CD 17
#define Pin_RST 16
#define Pin_CS_T 4
#define Pin_IRQ 2
#define Pin_CS_SD 15

bool dir_x = 0;
bool dir_a = 0;
bool sensor_x = 0;
bool sensor_a = 0;
uint16_t steps_x = 0;
uint16_t steps_a = 0;

#line 29 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Dupicadora.ino"
void MotorAC_enable();
#line 33 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Dupicadora.ino"
void MotorAC_disable();
#line 39 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Dupicadora.ino"
void setup();
#line 52 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Dupicadora.ino"
void loop();
#line 29 "d:\\Documentos\\ProyectoGrado\\Dupicadora\\Dupicadora.ino"
void MotorAC_enable(){
    digitalWrite(Pin_Rele,LOW);
}

void MotorAC_disable(){
    digitalWrite(Pin_Rele,HIGH);
}



void setup()
{
    pinMode(Pin_Enable_Motor_X,OUTPUT);
	pinMode(Pin_Dir_Motor_X,OUTPUT);
    pinMode(Pin_Pulse_Motor_X,OUTPUT);
    pinMode(Pin_Enable_Motor_A,OUTPUT);
	pinMode(Pin_Dir_Motor_A,OUTPUT);
    pinMode(Pin_Pulse_Motor_A,OUTPUT);
    pinMode(Pin_Rele,OUTPUT);
    pinMode(Pin_Sensor_X,INPUT_PULLDOWN);
    pinMode(Pin_Sensor_A,INPUT_PULLDOWN);    
}

void loop()
{
	
}

