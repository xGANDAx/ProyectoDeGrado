#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#define LABEL1_FONT &FreeSerif12pt7b
#define LABEL2_FONT &FreeSansOblique12pt7b

#define CALIBRATION_FILE "/TouchCalData3"
#define REPEAT_CAL false

TFT_eSPI_Button copia;
TFT_eSPI_Button generar;
TFT_eSPI_Button copiaListo;
TFT_eSPI_Button generarListo;
TFT_eSPI_Button Home;

int pag = 0;

void setup() {
  Serial.begin(9600);

  tft.begin();
  tft.setRotation(1);
  touch_calibrate();
  menu();
}

void loop() {
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates


  // Pressed will be set true is there is a valid touch on the screen
  boolean pressed = tft.getTouch(&t_x, &t_y);
  if (pressed && copia.contains(t_x, t_y) && pag == 1) {
    copia.press(true); // tell the button it is pressed
    Serial.println("Copia");
    delay(50);
    menuCopia();
  } else {
    copia.press(false); // tell the button it is NOT pressed
  }
  if (pressed && generar.contains(t_x, t_y) && pag == 1) {
    generar.press(true); // tell the button it is pressed
    Serial.println("Generar");
    generarMenu();
  } else {
    generar.press(false); // tell the button it is NOT pressed
  }
  if (pressed && copiaListo.contains(t_x, t_y) && pag == 2) {
    copiaListo.press(true); // tell the button it is pressed
    Serial.println("copiaListo");
    copiaCarga();
  } else {
    copiaListo.press(false); // tell the button it is NOT pressed
  }
  if (pressed && Home.contains(t_x, t_y) && (pag == 2 || pag == 3 || pag == 4 || pag == 5)) {
    Home.press(true); // tell the button it is pressed
    Serial.println("Menu");
    menu();
  } else {
    Home.press(false); // tell the button it is NOT pressed
  }
  if (pressed && generarListo.contains(t_x, t_y) && pag == 4) {
    generarListo.press(true); // tell the button it is pressed
    Serial.println("generarListo");
    generarAjustes();
  } else {
    generarListo.press(false); // tell the button it is NOT pressed
  }
}

void menu() {
  pag = 1;
  // / Check if any key coordinate boxes contain the touch coordinates

  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(110, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Menu V0.5");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
  //      tft.fillRoundRect(30, 70, 250, 50, 20, TFT_BLUE);
  //      tft.drawRoundRect(26, 66, 258, 58, 20, TFT_BLUE);
  //      tft.setCursor(120, 85);
  //      tft.setTextColor(TFT_WHITE, TFT_BLUE);
  //      tft.println("Copia");
  //      tft.fillRoundRect(30, 150, 250, 50, 20, TFT_BLUE);
  //      tft.drawRoundRect(26, 146, 258, 58, 20, TFT_BLUE);
  //      tft.setCursor(95, 165);
  //      tft.println("Generacion");
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

void menuCopia() {
  pag = 2;
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

void copiaCarga() {
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
  for (int carga = 0; carga < 260; carga++) {
    tft.fillRoundRect(30, 120, carga, 60, 20, TFT_GREEN);
    tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
    delay(50);
  }
  delay(100);
  pag = 3;
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

void generarMenu() {
  pag = 4;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Generar");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
  tft.fillRoundRect(30, 50, 260, 110, 20, TFT_BLUE);
  tft.drawRoundRect(26, 46, 268, 118, 20, TFT_BLUE);
  tft.setCursor(40, 75);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("Coloque unicamente el");
  tft.setCursor(50, 110);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("modelo de llave en la");
  tft.setCursor(100, 145);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("maquina");
  tft.setTextSize(2);
  tft.setFreeFont(LABEL2_FONT);
  generarListo.initButton(&tft, // REF - LEAVE AS IS
                        160, // X Cord: SEE ABOVE Line 19
                        200, // Y CORD: SEE ABOVE Line 20
                        150, // WIDTH: SEE ABOVE Line 21
                        50, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_BLUE, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "Listo", // TEXT TO PRINT
                        1); // TEXT SIZE: SEE ABOVE Line 23
  generarListo.drawButton();
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

void generarAjustes(){
  pag = 5;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 15);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Generar");
  tft.drawLine(0, 20, 320, 20, TFT_BLUE);
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
  ///////////////////////////////////////
  /////DIBUJO DE LA LLAVE A GENERAR//////
  ///////////////////////////////////////
  tft.fillCircle(80,110,55,TFT_WHITE);
  tft.fillCircle(50,110,15,TFT_BLACK);
  tft.fillRoundRect(90,85,200,50,30,TFT_WHITE);
  tft.fillTriangle(120,90,145,70,145,90,TFT_WHITE);
  tft.fillRectVGradient(132,91,160,12,TFT_DARKGREY,TFT_WHITE);
  tft.fillRectVGradient(125,118,165,12,TFT_DARKGREY,TFT_WHITE);
  tft.fillTriangle(278,90,300,90,300,120,TFT_BLACK);
  tft.fillTriangle(250,150,300,105,300,150,TFT_BLACK);
  /////TRIANGULOS PATRON GUARDAS/////
  tft.fillTriangle(162,83,182,83,172,round(3.83*random(1,7)+83.16),TFT_BLACK);
  tft.fillTriangle(184,83,204,83,194,round(3.83*random(1,7)+83.16),TFT_BLACK);
  tft.fillTriangle(206,83,226,83,216,round(3.83*random(1,7)+83.16),TFT_BLACK);
  tft.fillTriangle(228,83,248,83,238,round(3.83*random(1,7)+83.16),TFT_BLACK);
  tft.fillTriangle(250,83,270,83,260,round(3.83*random(1,7)+83.16),TFT_BLACK);
 
}


//////////////////////////////////////////////////////////////////////////////////////////

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}
