#include "Funciones.h"
#include "stdint.h"
#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h>

void generarLlave2(double key[])
{
  double y_offset[5];
  double y_limit = 40;
  double y_min = 10;
  double y_temp;
  double y_calculated;
  double y_final;
  for (uint8_t i = 0; i <= 5; i++)
  {
    y_offset[i] = random(0, 20) * 2 - y_min;
  }
  for (uint16_t i = 0; i <= 1500; i++)
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
}

void generarLlave(uint16_t key[])
{
  uint16_t y_offset[5];
  uint16_t y_limit = 300;
  uint16_t y_min = 30;
  uint16_t y_temp;
  uint16_t y_calculated;
  uint16_t y_final;
  for (uint8_t i = 0; i <= 5; i++)
  {
    y_offset[i] = random(0, 30) * 10 - y_min;
  }
  for (uint16_t i = 0; i <= 1500; i++)
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
}

void generarLlave(uint16_t key[], uint16_t offsets[5])
{
  uint16_t y_limit = 300;
  uint16_t y_min = 30;
  uint16_t y_temp;
  uint16_t y_calculated;
  uint16_t y_final;
  for (uint8_t i = 0; i <= 5; i++)
  {
    offsets[i] = random(0, 30) * 10 - y_min;
  }
  for (uint16_t i = 0; i <= 1500; i++)
  {
    y_final = y_limit;
    for (uint8_t j = 0; j <= 5; j++)
    {
      y_temp = abs(i - 250);
      y_calculated = max(y_temp, y_min) + offsets[i];
      y_final = min(y_calculated, y_final);
    }
    key[i] = y_final;
  }
}
