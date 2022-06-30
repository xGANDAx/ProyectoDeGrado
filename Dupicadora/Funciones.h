#include <stdint.h>
#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h>

void menu(TFT_eSPI tft, TFT_eSPI_Button copia, TFT_eSPI_Button generar);
void menuCopia(TFT_eSPI tft,TFT_eSPI_Button copiaListo,TFT_eSPI_Button Home);
void copiaCarga(TFT_eSPI tft);
void actualizarCarga(TFT_eSPI tft, int progreso);
void finalizado(TFT_eSPI tft, TFT_eSPI_Button Home);
void Copiar();
void generarLlave2(double key[]);
void generarLlave(uint16_t key[]);
void generarLlave(uint16_t key[], uint16_t offsets[5]);
