#include "FS.h"

#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#define LABEL1_FONT &FreeSerif12pt7b
#define LABEL2_FONT &FreeSansOblique12pt7b
#define LABEL3_FONT &FreeSansBold9pt7b

#define CALIBRATION_FILE "/TouchCalData3"
#define REPEAT_CAL false

TFT_eSPI_Button copia;
TFT_eSPI_Button generar;
TFT_eSPI_Button copiaListo;
TFT_eSPI_Button generarListo;
TFT_eSPI_Button generarCorta;
TFT_eSPI_Button Home;
TFT_eSPI_Button grata;
TFT_eSPI_Button gratasON;
TFT_eSPI_Button gratasOFF;

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
  if (pressed && Home.contains(t_x, t_y) && (pag == 2 || pag == 3 || pag == 4 || pag == 5 || pag == 7 || pag == 8)) {
    Home.press(true); // tell the button it is pressed
    Serial.println("Menu");
    Serial.println("grataOFF");
    menu();
    delay(100);
  } else {
    Home.press(false); // tell the button it is NOT pressed
  }
  if (pressed && generarListo.contains(t_x, t_y) && (pag == 4 || pag == 5)) {
    generarListo.press(true); // tell the button it is pressed
    Serial.println("generarListo");
    generarAjustes();
  } else {
    generarListo.press(false); // tell the button it is NOT pressed
  }
  if (pressed && generarCorta.contains(t_x, t_y) && pag == 5) {
    generarCorta.press(true); // tell the button it is pressed
    Serial.println("generarCorta");
    generarCarga();
  } else {
    generarCorta.press(false); // tell the button it is NOT pressed
  }
  if (pressed && grata.contains(t_x, t_y) && pag == 1) {
    grata.press(true); // tell the button it is pressed
    Serial.println("grata");
    grataOFF();
  } else {
    grata.press(false); // tell the button it is NOT pressed
  }
  if (pressed && gratasON.contains(t_x, t_y) && pag == 7) {
    gratasON.press(true); // tell the button it is pressed
    Serial.println("grataON");
    delay(100);
    grataON();
  } else {
    gratasON.press(false); // tell the button it is NOT pressed
  }
  if (pressed && gratasOFF.contains(t_x, t_y) && pag == 8) {
    gratasOFF.press(true); // tell the button it is pressed
    Serial.println("grataOFF");
    delay(100);
    grataOFF();
  } else {
    gratasOFF.press(false); // tell the button it is NOT pressed
  }
}

void menu() {
  pag = 1;
  // / Check if any key coordinate boxes contain the touch coordinates

  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(110, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Menu V0.6");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
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
                     130, // Y CORD: SEE ABOVE Line 20
                     250, // WIDTH: SEE ABOVE Line 21
                     50, // HEIGHT: SEE ABOVE Line 22
                     TFT_WHITE, // OUTLINE
                     TFT_BLUE, // TEXT COLOR
                     TFT_WHITE, // FILL
                     "Generar", // TEXT TO PRINT
                     1); // TEXT SIZE: SEE ABOVE Line 23
  generar.drawButton();
 
  grata.initButton(&tft, // REF - LEAVE AS IS
                     160, // X Cord: SEE ABOVE Line 19
                     190, // Y CORD: SEE ABOVE Line 20
                     250, // WIDTH: SEE ABOVE Line 21
                     50, // HEIGHT: SEE ABOVE Line 22
                     TFT_WHITE, // OUTLINE
                     TFT_BLUE, // TEXT COLOR
                     TFT_WHITE, // FILL
                     "Grata", // TEXT TO PRINT
                     1); // TEXT SIZE: SEE ABOVE Line 23
  grata.drawButton();
}

void menuCopia() {
  pag = 2;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Copiar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
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
                        15, // X Cord: SEE ABOVE Line 19
                        15, // Y CORD: SEE ABOVE Line 20
                        30, // WIDTH: SEE ABOVE Line 21
                        30, // HEIGHT: SEE ABOVE Line 22
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
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Copiar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
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
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Copiar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
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


void grataOFF() {
  pag = 7;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Grata");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
  gratasON.initButton(&tft, // REF - LEAVE AS IS
                        160, // X Cord: SEE ABOVE Line 19
                        120, // Y CORD: SEE ABOVE Line 20
                        200, // WIDTH: SEE ABOVE Line 21
                        100, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_GREEN, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "ON", // TEXT TO PRINT
                        2); // TEXT SIZE: SEE ABOVE Line 23
  gratasON.drawButton();
  Home.initButton(&tft, // REF - LEAVE AS IS
                        15, // X Cord: SEE ABOVE Line 19
                        15, // Y CORD: SEE ABOVE Line 20
                        30, // WIDTH: SEE ABOVE Line 21
                        30, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_RED, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "x", // TEXT TO PRINT
                        1); // TEXT SIZE: SEE ABOVE Line 23
  Home.drawButton();
}

void grataON() {
  pag = 8;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Grata");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
  gratasOFF.initButton(&tft, // REF - LEAVE AS IS
                        160, // X Cord: SEE ABOVE Line 19
                        120, // Y CORD: SEE ABOVE Line 20
                        200, // WIDTH: SEE ABOVE Line 21
                        100, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_RED, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "OFF", // TEXT TO PRINT
                        2); // TEXT SIZE: SEE ABOVE Line 23
  gratasOFF.drawButton();
  Home.initButton(&tft, // REF - LEAVE AS IS
                        15, // X Cord: SEE ABOVE Line 19
                        15, // Y CORD: SEE ABOVE Line 20
                        30, // WIDTH: SEE ABOVE Line 21
                        30, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_RED, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "x", // TEXT TO PRINT
                        1); // TEXT SIZE: SEE ABOVE Line 23
  Home.drawButton();
}

void generarMenu() {
  pag = 4;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Generar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
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
                        15, // X Cord: SEE ABOVE Line 19
                        15, // Y CORD: SEE ABOVE Line 20
                        30, // WIDTH: SEE ABOVE Line 21
                        30, // HEIGHT: SEE ABOVE Line 22
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
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Generar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
  tft.setFreeFont(LABEL1_FONT);
  Home.initButton(&tft, // REF - LEAVE AS IS
                        15, // X Cord: SEE ABOVE Line 19
                        15, // Y CORD: SEE ABOVE Line 20
                        30, // WIDTH: SEE ABOVE Line 21
                        30, // HEIGHT: SEE ABOVE Line 22
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
  int guarda[] ={random(1,7),random(1,7),random(1,7),random(1,7),random(1,7)};
  tft.fillTriangle(161,83,183,83,172,round(3.83*guarda[0]+83.16),TFT_BLACK);
  tft.fillTriangle(183,83,205,83,194,round(3.83*guarda[1]+83.16),TFT_BLACK);
  tft.fillTriangle(205,83,227,83,216,round(3.83*guarda[2]+83.16),TFT_BLACK);
  tft.fillTriangle(227,83,249,83,238,round(3.83*guarda[3]+83.16),TFT_BLACK);
  tft.fillTriangle(249,83,271,83,260,round(3.83*guarda[4]+83.16),TFT_BLACK);
  //NUMEROS DE LAS GUARDAS//
  tft.drawRoundRect(155,40,120,40,5,TFT_WHITE);
  tft.drawLine(155, 60, 275, 60, TFT_WHITE);
  tft.setFreeFont(LABEL3_FONT);
  tft.setCursor(160, 55);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.println("GUARDAS #");
  tft.setCursor(161, 75);
  tft.println(guarda[0]);
  tft.drawLine(179, 60, 179, 80, TFT_WHITE);
  tft.setCursor(185, 75);
  tft.println(guarda[1]);
  tft.drawLine(203, 60, 203, 80, TFT_WHITE);
  tft.setCursor(209, 75);
  tft.println(guarda[2]);
  tft.drawLine(227, 60, 227, 80, TFT_WHITE);
  tft.setCursor(233, 75);
  tft.println(guarda[3]);
  tft.drawLine(251, 60, 251, 80, TFT_WHITE);
  tft.setCursor(257, 75);
  tft.println(guarda[4]);
  /////BOTONES//////
  tft.setFreeFont(LABEL2_FONT);
  generarListo.initButton(&tft, // REF - LEAVE AS IS
                        80, // X Cord: SEE ABOVE Line 19
                        200, // Y CORD: SEE ABOVE Line 20
                        120, // WIDTH: SEE ABOVE Line 21
                        50, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_BLUE, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "Nuevo P.", // TEXT TO PRINT
                        1); // TEXT SIZE: SEE ABOVE Line 23
  generarListo.drawButton();
  generarCorta.initButton(&tft, // REF - LEAVE AS IS
                        230, // X Cord: SEE ABOVE Line 19
                        200, // Y CORD: SEE ABOVE Line 20
                        120, // WIDTH: SEE ABOVE Line 21
                        50, // HEIGHT: SEE ABOVE Line 22
                        TFT_WHITE, // OUTLINE
                        TFT_BLUE, // TEXT COLOR
                        TFT_WHITE, // FILL
                        "Cortar", // TEXT TO PRINT
                        1); // TEXT SIZE: SEE ABOVE Line 23
  generarCorta.drawButton();
  
}

void generarCarga() {
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Generar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
  tft.setCursor(110, 85);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.println("Generando...");
  for (int carga = 0; carga < 260; carga++) {
    tft.fillRoundRect(30, 120, carga, 60, 20, TFT_GREEN);
    tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
    delay(50);
  }
  delay(100);
  pag = 3;
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(130, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Generar");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
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
