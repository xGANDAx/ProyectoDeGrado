#include "Funciones.h"
#include "stdint.h"
#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h>

void generarLlave2(float key[])
{
  float y_offset[6]={0.0,0.0,0.0,0.0,0.0,0.0};
  float y_limit = 4;
  float y_min = 0.4;
  float y_temp;
  float y_calculated;
  float y_final;
  float xg[6] = {6.0, 9.8, 13.6, 17.4, 21.2, 27.0};
  for (uint8_t i = 0; i <= 4; i++)
  {
    y_offset[i] = random(1, 10) * 0.4;
  }
  
  for (uint16_t i = 0; i <= 270; i++)
  {
    y_final = y_limit;
    for (uint8_t j = 0; j <= 5; j++)
    {
      y_temp = abs((i+0.0)/10.0 - xg[j]);
      if(j==5){
        y_calculated = y_temp; 
      }else{
        y_calculated = max(y_temp, y_min) + y_offset[j]-y_min;
      }
      y_final = min(y_calculated, y_final);
    }
    key[i] = y_final;
  }
}
