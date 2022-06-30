#include <cmath>
#include <stdlib.h>
#include <iostream>

#include <iomanip>

using namespace std;

double llave[271];

void generarLlave2(double key[])
{
  double y_offset[6]={0.0,0.0,0.0,0.0,0.0,0.0};
  double y_limit = 4.0;
  double y_min = 0.5;
  double y_temp;
  double y_calculated;
  double y_final;
  double y_6;
  double xg[6] = {6.0, 9.8, 13.6, 17.4, 21.2, 27.0};
/*
  for (int i = 0; i <= 4; i++)
  {
    y_offset[i] = (rand()%10 + 1)* 0.4;
  }

  y_offset[5] = 0.0;
  */
  for (int i = 0; i <= 270; i++)
  {
    y_final = y_limit;
    for (int j = 0; j <= 5; j++)
    {
      y_temp = abs((i+0.0)/10.0 - xg[j]);
      if(j == 5){
      	y_calculated = y_temp;
	  }else{
		y_calculated = fmax(y_temp, y_min) + y_offset[j]-y_min;
	  }
      y_final = fmin(y_calculated, y_final);
    }
    key[i] = y_final;
  }
}

double f = 0.0;

int main(int argc, char const *argv[])
{
    generarLlave2(llave);
    
    for(int k=0;k<271;k++){
    	cout <<fixed<<setprecision(2)<< llave[k]<<",";
	}
	
    return 0;
}


