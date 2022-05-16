#include "Funciones.h"

#ifndef Pin_Rele
#define Pin_Rele 32
#endif

void MotorAC_enable()
{
    digitalWrite(Pin_Rele, LOW);
}

void MotorAC_disable()
{
    digitalWrite(Pin_Rele, HIGH);
}

uint16_t *generarLlave()
{
    uint16_t y_offset[5];
    uint16_t key[1501];
    uint16_t y_limit = 300;
    uint16_t y_min = 30;
    uint16_t y_temp;
    uint16_t y_calculated;
    uint16_t y_final;
    for (uint8_t i = 0; i <= 5; i++)
    {
        y_offset[i] = random(0, 30) * 10 - y_min;
    }
    for (uint16_t i = 0; i <= 1501; i++)
    {
        y_final = y_limit;
        for (uint8_t j = 0; j <= 5; j++)
        {
            y_temp = abs(i - 250);
            y_calculated = max(y_temp, y_min) + y_offset[i];
            y_final = min(y_calculated, y_final);
        }
        key[i] = y_final;
    }
    return key;
}