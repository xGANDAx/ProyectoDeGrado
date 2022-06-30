#include "Funciones.h"
#include "stdint.h"
#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h>

void generarLlave2(double key[])
{
  double y_offset[6]={0.0,0.0,0.0,0.0,0.0,0.0};
  double y_limit = 4;
  double y_min = 0.5;
  double y_temp;
  double y_calculated;
  double y_final;
  double xg[6] = {6.0, 9.8, 13.6, 17.4, 21.2, 27.0};
  for (uint8_t i = 0; i <= 4; i++)
  {
    y_offset[i] = random(1, 10) * 0.4 - y_min;
  }
  
  for (uint16_t i = 0; i <= 270; i++)
  {
    y_final = y_limit;
    for (uint8_t j = 0; j <= 5; j++)
    {
      y_temp = abs(i/10.0 - xg[j]);
      if(j==5){
        y_calculated = y_temp; 
      }else{
        y_calculated = max(y_temp, y_min) + y_offset[i]-y_min;
      }
      y_final = min(y_calculated, y_final);
    }
    key[i] = y_final;
  }
}
