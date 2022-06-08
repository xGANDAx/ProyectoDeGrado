// Declaracion librerias
#include "Stepper.h"
#include "Funciones.h"
#include "stdint.h"

// Declaracion pines
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

// Declaracion variables
bool key_ready = false;
uint16_t steps_x = 0;
uint16_t steps_a = 0;
uint16_t llave[1500];

// Declaracion de los motores
Stepper Motor_x(Pin_Enable_Motor_X,Pin_Dir_Motor_X,Pin_Pulse_Motor_X,Pin_Sensor_X,true);
Stepper Motor_a(Pin_Enable_Motor_A,Pin_Dir_Motor_A,Pin_Pulse_Motor_A,Pin_Sensor_A,false);

void setup()
{
    //Inicializacion pantalla

    // Inicializacion de los pines de los motores
    pinMode(Pin_Enable_Motor_X, OUTPUT);
    pinMode(Pin_Dir_Motor_X, OUTPUT);
    pinMode(Pin_Pulse_Motor_X, OUTPUT);
    pinMode(Pin_Enable_Motor_A, OUTPUT);
    pinMode(Pin_Dir_Motor_A, OUTPUT);
    pinMode(Pin_Pulse_Motor_A, OUTPUT);
    pinMode(Pin_Rele, OUTPUT);
    pinMode(Pin_Sensor_X, INPUT_PULLDOWN);
    pinMode(Pin_Sensor_A, INPUT_PULLDOWN);

    // Reset de los motores
    Motor_a.reset();
    Motor_a.sound();
    Motor_x.reset();
    Motor_x.sound();

    Motor_a.disable();
    Motor_x.disable();
    
    generarLlave(llave);
}

void loop()
{
    // Pantallazo "Menu principal:Copia, generar llave"

}

void copiar(){
    Motor_a.reset();
    Motor_x.MovePosition(1500);
    // Pantallazo "introduzca las llaves y oprima listo"

    while(true)
    {
        if(key_ready == true) break;
    }
    // Pantallazo "espere a que termine...""
    Motor_a.MovePosition(1500);
    digitalWrite(Pin_Rele, LOW);
    Motor_a.disable();
    Motor_x.reset();
    Motor_a.MoveSteps(500);
    Motor_x.MovePosition(1500);
    Motor_a.disable();
    Motor_x.reset();
    digitalWrite(Pin_Rele, HIGH);
    // Pantallazo "finalizado"
    // Pantallazo "activar grata"
    digitalWrite(Pin_Rele, LOW);
    delay(60000);
    digitalWrite(Pin_Rele, HIGH);
}