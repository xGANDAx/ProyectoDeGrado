#include "Funciones.h"
#include "stdint.h"
#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h>

#define LABEL1_FONT &FreeSerif12pt7b
#define LABEL2_FONT &FreeSansOblique12pt7b



void menu(TFT_eSPI tft, TFT_eSPI_Button copia, TFT_eSPI_Button generar) {
  // / Check if any key coordinate boxes contain the touch coordinates

  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(110, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Menu V0.5");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
  tft.setTextSize(1);
  tft.setFreeFont(LABEL2_FONT);



  copia.initButton(&tft, // REF - LEAVE AS IS
                   160, // X Cord: SEE ABOVE Line 19
                   70, // Y CORD: SEE ABOVE Line 20
                   250, // WIDTH: SEE ABOVE Line 21
                   50, // HEIGHT: SEE ABOVE Line 22
                   TFT_WHITE, // OUTLINE
                   TFT_BLUE, // TEXT COLOR
                   TFT_WHITE, // FILL
                   "Copiar", // TEXT TO PRINT
                   1); // TEXT SIZE: SEE ABOVE Line 23
  copia.drawButton();

  generar.initButton(&tft, // REF - LEAVE AS IS
                     160, // X Cord: SEE ABOVE Line 19
                     150, // Y CORD: SEE ABOVE Line 20
                     250, // WIDTH: SEE ABOVE Line 21
                     50, // HEIGHT: SEE ABOVE Line 22
                     TFT_WHITE, // OUTLINE
                     TFT_BLUE, // TEXT COLOR
                     TFT_WHITE, // FILL
                     "Generar", // TEXT TO PRINT
                     1); // TEXT SIZE: SEE ABOVE Line 23
  generar.drawButton();

}

void menuCopia(TFT_eSPI tft,TFT_eSPI_Button copiaListo,TFT_eSPI_Button Home) {
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Copiar");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
  tft.fillRoundRect(30, 50, 260, 110, 20, TFT_BLUE);
  tft.drawRoundRect(26, 46, 268, 118, 20, TFT_BLUE);
  tft.setCursor(40, 85);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("Coloque la llave a copiar");
  tft.setCursor(35, 120);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("y el modelo en la maquina");
  tft.setTextSize(2);
  tft.setFreeFont(LABEL2_FONT);
  copiaListo.initButton(&tft, // REF - LEAVE AS IS
                        160, // X Cord: SEE ABOVE Line 19
                        200, // Y CORD: SEE ABOVE Line 20
                        150, // WIDTH: SEE ABOVE Line 21
                        50, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_BLUE, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "Listo", // TEXT TO PRINT
                        1); // TEXT SIZE: SEE ABOVE Line 23
  copiaListo.drawButton();
  tft.setFreeFont(LABEL1_FONT);
  Home.initButton(&tft, // REF - LEAVE AS IS
                  10, // X Cord: SEE ABOVE Line 19
                  10, // Y CORD: SEE ABOVE Line 20
                  20, // WIDTH: SEE ABOVE Line 21
                  20, // HEIGHT: SEE ABOVE Line 22
                  TFT_WHITE, // OUTLINE
                  TFT_RED, // TEXT COLOR
                  TFT_WHITE, // FILL
                  "x", // TEXT TO PRINT
                  1); // TEXT SIZE: SEE ABOVE Line 23
  Home.drawButton();
}

void copiaCarga(TFT_eSPI tft) {
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Copiar");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
  tft.setCursor(110, 85);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("Copiando...");
  tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
}

void actualizarCarga(TFT_eSPI tft, int progreso){
  tft.fillRoundRect(30, 120, progreso, 60, 20, TFT_GREEN);
  tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
}

void finalizado(TFT_eSPI tft, TFT_eSPI_Button Home) {
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Copiar");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
  tft.setCursor(110, 90);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("¡Finalizado!");
  tft.setTextSize(2);
  tft.setFreeFont(LABEL2_FONT);
  Home.initButton(&tft, // REF - LEAVE AS IS
                  170, // X Cord: SEE ABOVE Line 19
                  160, // Y CORD: SEE ABOVE Line 20
                  150, // WIDTH: SEE ABOVE Line 21
                  50, // HEIGHT: SEE ABOVE Line 22
                  TFT_WHITE, // OUTLINE
                  TFT_BLUE, // TEXT COLOR
                  TFT_WHITE, // FILL
                  "Menu", // TEXT TO PRINT
                  1); // TEXT SIZE: SEE ABOVE Line 23
  Home.drawButton();

}

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
