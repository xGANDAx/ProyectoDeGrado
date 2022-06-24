// Declaracion librerias
#include "FS.h"

#include "Stepper.h"
#include "Funciones.h"
#include "stdint.h"
#include <SPI.h>
#include <TFT_eSPI.h>

#define LABEL1_FONT &FreeSerif12pt7b
#define LABEL2_FONT &FreeSansOblique12pt7b
#define LABEL3_FONT &FreeSansBold9pt7b

#define CALIBRATION_FILE "/TouchCalData3"
#define REPEAT_CAL false

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
// Pines Pantalla TFT
#define Pin_MOSI 23
#define Pin_MISO 19
#define Pin_CLK 18
#define Pin_CS_G 15
#define Pin_CD 2
#define Pin_RST 4
#define Pin_CS_T 22
#define Pin_IRQ 21
#define Pin_CS_SD 5

TFT_eSPI tft = TFT_eSPI();

TFT_eSPI_Button copia;
TFT_eSPI_Button generar;
TFT_eSPI_Button copiaListo;
TFT_eSPI_Button generarListo;
TFT_eSPI_Button generarListo2;
TFT_eSPI_Button generarCorta;
TFT_eSPI_Button Home;
TFT_eSPI_Button grata;
TFT_eSPI_Button grataON;
TFT_eSPI_Button grataOFF;


// Declaracion variables
bool key_ready = false;
bool grataStatus = false;
uint16_t steps_x = 0;
uint16_t steps_a = 0;
uint16_t llave[1500];
uint16_t progreso = 0;
uint16_t t_x = 0, t_y = 0;
boolean pressed;
bool gListo = false;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  tft.fillRoundRect(30, 120, progreso, 60, 20, TFT_GREEN);
  tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
  if (progreso < 260) {
    progreso++;
  }
  portEXIT_CRITICAL_ISR(&timerMux);

}

// Declaracion de los motores
Stepper Motor_x(Pin_Enable_Motor_X, Pin_Dir_Motor_X, Pin_Pulse_Motor_X, Pin_Sensor_X, false, 25);
Stepper Motor_a(Pin_Enable_Motor_A, Pin_Dir_Motor_A, Pin_Pulse_Motor_A, Pin_Sensor_A, false, 50);

void setup()
{
  // Inicialixacion serial (Solo pruebas)
  Serial.begin(9600);
  // Inicializacion pantalla
  tft.begin();
  tft.setRotation(1);

  // Inicializacion de todos los botones
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
  generarListo2.initButton(&tft, // REF - LEAVE AS IS
                           80, // X Cord: SEE ABOVE Line 19
                           200, // Y CORD: SEE ABOVE Line 20
                           120, // WIDTH: SEE ABOVE Line 21
                           50, // HEIGHT: SEE ABOVE Line 22
                           TFT_WHITE, // OUTLINE
                           TFT_BLUE, // TEXT COLOR
                           TFT_WHITE, // FILL
                           "Nuevo P.", // TEXT TO PRINT
                           1); // TEXT SIZE: SEE ABOVE Line 23
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

  grataON.initButton(&tft, // REF - LEAVE AS IS
                     160, // X Cord: SEE ABOVE Line 19
                     120, // Y CORD: SEE ABOVE Line 20
                     200, // WIDTH: SEE ABOVE Line 21
                     100, // HEIGHT: SEE ABOVE Line 22
                     TFT_WHITE, // OUTLINE
                     TFT_GREEN, // TEXT COLOR
                     TFT_WHITE, // FILL
                     "ON", // TEXT TO PRINT
                     2); // TEXT SIZE: SEE ABOVE Line 23
  grataOFF.initButton(&tft, // REF - LEAVE AS IS
                      160, // X Cord: SEE ABOVE Line 19
                      120, // Y CORD: SEE ABOVE Line 20
                      200, // WIDTH: SEE ABOVE Line 21
                      100, // HEIGHT: SEE ABOVE Line 22
                      TFT_WHITE, // OUTLINE
                      TFT_RED, // TEXT COLOR
                      TFT_WHITE, // FILL
                      "OFF", // TEXT TO PRINT
                      2); // TEXT SIZE: SEE ABOVE Line 23

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
  digitalWrite(Pin_Rele, LOW);

  // Definicion del timer para la pantalla de progreso
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 212000, true);

  // Calibracion del tactil
  touch_calibrate();

  // Reset de los motores
  Motor_a.reset();
  Motor_x.reset();
  Motor_x.sound(4);
  delay(300);
  Motor_x.sound(4);
  Serial.println("Empezando ...");
}

void loop()
{
MenuPrincipal:
  Serial.println("Seleccione modo a utilizar:");
  Serial.println("C: Copiar");
  Serial.println("G: Generar");

  // Generacion del menu principal
  tft.setFreeFont(LABEL1_FONT);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(110, 20);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.println("Menu V0.6");
  tft.drawLine(0, 30, 320, 30, TFT_BLUE);
  tft.setTextSize(1);
  tft.setFreeFont(LABEL2_FONT);
  copia.drawButton();
  generar.drawButton();
  grata.drawButton();

  while (true)
  {
    t_x = 0;
    t_y = 0;
    pressed = tft.getTouch(&t_x, &t_y);
    if (Serial.available() || pressed )
    {
      String str = Serial.readStringUntil('\n');
      str.toLowerCase();
      str.trim();
      if (str == "c" || copia.contains(t_x, t_y))
      {
        //Inicializacion del modo copia
        Motor_a.reset();
        Motor_x.reset();
        Motor_x.setSpeed(25);
        Motor_x.MovePosition(31500);

        // Generacion pantalla de copia
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
        copiaListo.drawButton();
        tft.setFreeFont(LABEL1_FONT);
        Home.drawButton();
        Serial.println("Oprima cualquier tecla para continuar");

        while (true)
        {
          t_x = 0;
          t_y = 0;
          pressed = tft.getTouch(&t_x, &t_y);
          if (Serial.available() || (pressed && copiaListo.contains(t_x, t_y)))
          {
            // Activacion barra de progreso
            timerAlarmEnable(timer);
            // Generacion barra de carga
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
            tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
            Serial.println("Realizando llave ...");
            break;
          } else if (pressed && Home.contains(t_x, t_y)) {
            goto MenuPrincipal;
          }
        }
        Motor_a.setSpeed(100);
        Motor_a.MovePosition(5300);
        digitalWrite(Pin_Rele, HIGH);
        grataStatus = true;
        Motor_a.disable();
        Motor_x.setSpeed(400);
        Motor_x.MovePosition(0);
        Motor_a.setSpeed(200);
        Motor_a.MoveSteps(-800);
        Motor_x.setSpeed(25);
        Motor_x.MovePosition(31500);
        Motor_a.setSpeed(100);
        Motor_a.disable();
        Motor_x.setSpeed(400);
        Motor_x.MovePosition(0);
        Motor_a.reset();
        digitalWrite(Pin_Rele, LOW);
        grataStatus = false;
        Motor_x.sound(4);
        delay(300);
        Motor_x.sound(4);

        //Deshabilita la pantalla de carga
        timerAlarmDisable(timer);
        progreso = 0;

        //  Pantallazo "finalizado"
        tft.setFreeFont(LABEL1_FONT);
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(130, 20);
        tft.setTextColor(TFT_BLUE);
        tft.setTextSize(1);
        tft.println("Copiar");
        tft.drawLine(0, 30, 320, 30, TFT_BLUE);
        tft.setCursor(110, 120);
        tft.setTextColor(TFT_WHITE, TFT_BLUE);
        tft.println("¡Finalizado!");
        tft.setTextSize(2);
        tft.setFreeFont(LABEL2_FONT);
        Home.drawButton();
        Serial.println("Finalizado");
        delay(5000);
        break;
      }
      // Seccion de generacion de llave
      else if (str == "g" || generar.contains(t_x, t_y))
      {
        Motor_a.reset();
        Motor_x.reset();
        Motor_x.setSpeed(25);
        Motor_x.MovePosition(31500);
        // Pantalla de generar
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
        generarListo.drawButton();
        tft.setFreeFont(LABEL1_FONT);
        Home.drawButton();
        Serial.println("Oprima cualquier tecla para continuar");
        
        while (true)
        {
          t_x = 0;
          t_y = 0;
          pressed = tft.getTouch(&t_x, &t_y);
          if (Serial.available() || (pressed && generarListo.contains(t_x, t_y)))
          {
            break;
          }
          else if (pressed && Home.contains(t_x, t_y))
          {
            goto MenuPrincipal;
          }
        }
        
        while (true)
        {
          tft.setFreeFont(LABEL1_FONT);
          tft.fillScreen(TFT_BLACK);
          tft.setCursor(130, 20);
          tft.setTextColor(TFT_BLUE);
          tft.setTextSize(1);
          tft.println("Generar");
          tft.drawLine(0, 30, 320, 30, TFT_BLUE);
          tft.setFreeFont(LABEL1_FONT);
          Home.drawButton();
          ///////////////////////////////////////
          /////DIBUJO DE LA LLAVE A GENERAR//////
          ///////////////////////////////////////
          tft.fillCircle(80, 110, 55, TFT_WHITE);
          tft.fillCircle(50, 110, 15, TFT_BLACK);
          tft.fillRoundRect(90, 85, 200, 50, 30, TFT_WHITE);
          tft.fillTriangle(120, 90, 145, 70, 145, 90, TFT_WHITE);
          tft.fillRectVGradient(132, 91, 160, 12, TFT_DARKGREY, TFT_WHITE);
          tft.fillRectVGradient(125, 118, 165, 12, TFT_DARKGREY, TFT_WHITE);
          tft.fillTriangle(278, 90, 300, 90, 300, 120, TFT_BLACK);
          tft.fillTriangle(250, 150, 300, 105, 300, 150, TFT_BLACK);
          /////TRIANGULOS PATRON GUARDAS/////
          int guarda[] = {random(1, 7), random(1, 7), random(1, 7), random(1, 7), random(1, 7)};
          tft.fillTriangle(161, 83, 183, 83, 172, round(3.83 * guarda[0] + 83.16), TFT_BLACK);
          tft.fillTriangle(183, 83, 205, 83, 194, round(3.83 * guarda[1] + 83.16), TFT_BLACK);
          tft.fillTriangle(205, 83, 227, 83, 216, round(3.83 * guarda[2] + 83.16), TFT_BLACK);
          tft.fillTriangle(227, 83, 249, 83, 238, round(3.83 * guarda[3] + 83.16), TFT_BLACK);
          tft.fillTriangle(249, 83, 271, 83, 260, round(3.83 * guarda[4] + 83.16), TFT_BLACK);
          //NUMEROS DE LAS GUARDAS//
          tft.drawRoundRect(155, 40, 120, 40, 5, TFT_WHITE);
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
          generarListo2.drawButton();
          generarCorta.drawButton();
          delay(500);
          
          while (true)
          {
            t_x = 0;
            t_y = 0;
            pressed = tft.getTouch(&t_x, &t_y);
            if (Serial.available() || pressed)
            {
              String str = Serial.readStringUntil('\n');
              str.toLowerCase();
              str.trim();
              if (str == "a" || generarListo2.contains(t_x, t_y))
              {
                break;
              }
              else if (str == "d" || generarCorta.contains(t_x, t_y))
              { 
                gListo = true;
                break;
              }
              else if (str == "s" || Home.contains(t_x, t_y))
              {
                goto MenuPrincipal;
              }
            }
          }
          if(gListo){
            // Activacion barra de progreso
            timerAlarmEnable(timer);
            // Generacion barra de carga
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
            tft.drawRoundRect(26, 116, 268, 68, 20, TFT_WHITE);
            Serial.println("Generando llave ...");
            break;
          }
        }
        // Generando llave
        delay(55000);


        //Deshabilita la pantalla de carga
        timerAlarmDisable(timer);
        progreso = 0;

        //  Pantallazo "finalizado"
        tft.setFreeFont(LABEL1_FONT);
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(130, 20);
        tft.setTextColor(TFT_BLUE);
        tft.setTextSize(1);
        tft.println("Generar");
        tft.drawLine(0, 30, 320, 30, TFT_BLUE);
        tft.setCursor(110, 120);
        tft.setTextColor(TFT_WHITE, TFT_BLUE);
        tft.println("¡Finalizado!");
        tft.setTextSize(2);
        tft.setFreeFont(LABEL2_FONT);
        Home.drawButton();
        Serial.println("Finalizado");
        delay(5000);
        break;
        
      }
      // Seccion de la grata
      else if (str == "f" || grata.contains(t_x, t_y))
      {
        if(!digitalRead(Pin_Sensor_X) && !digitalRead(Pin_Sensor_A)){
          Motor_x.reset();
          Motor_a.reset();
        }
        // Generacion del menu de grata
        tft.setFreeFont(LABEL1_FONT);
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(130, 20);
        tft.setTextColor(TFT_BLUE);
        tft.setTextSize(1);
        tft.println("Grata");
        tft.drawLine(0, 30, 320, 30, TFT_BLUE);
        Home.drawButton();

        Serial.println("Activar grata:");
        Serial.println("a : Activar");
        Serial.println("d : Desactivar");
        Serial.println("s : Salir");
        while (true)
        {
          Serial.println(grataStatus);
          // Generacion boton cambiante de la grata
          if (grataStatus)
          {
            grataOFF.drawButton();
          }
          else
          {
            grataON.drawButton();
          }

          // Manipulacion de la grata
          while (true)
          {
            t_x = 0;
            t_y = 0;
            pressed = tft.getTouch(&t_x, &t_y);
            if (Serial.available() || pressed)
            {
              String str = Serial.readStringUntil('\n');
              str.toLowerCase();
              str.trim();
              if (str == "a" || (grataON.contains(t_x, t_y) && !grataStatus))
              {
                grataStatus = true;
                digitalWrite(Pin_Rele, HIGH);
                delay(500);
                break;
              }
              else if (str == "d" || (grataOFF.contains(t_x, t_y) && grataStatus))
              {
                grataStatus = false;
                digitalWrite(Pin_Rele, LOW);
                delay(500);
                break;
              }
              else if (str == "s" || Home.contains(t_x, t_y))
              {
                grataStatus = false;
                digitalWrite(Pin_Rele, LOW);
                goto MenuPrincipal;
              }
            }
          }
        }
      }
      /*
        Funciones solo para pruebas
        m=#.#   >> Mueve el motor x a una posicion en mm
        n   >> enciende la fresa
        r   >> hace un reset
        x=# >> mueve el motor x a el paso #
        a=# >> mueve el motor a a el paso #
      */
      else if (str == "r")
      {
        Motor_a.reset();
        Motor_x.reset();
      }
      else if (str[0] == 'x')
      {
        int posd = str.substring(2).toInt();
        Motor_x.setSpeed(50);
        Motor_x.MovePosition(posd);
        Serial.print("x=");
        Serial.println(posd);
      }
      else if (str[0] == 'a')
      {
        int posd = str.substring(2).toInt();
        if (posd < 0)
        {
          Motor_a.disable();
        }
        else
        {
          Motor_a.setSpeed(200);
          Motor_a.MovePosition(posd);
          Serial.print("a=");
          Serial.println(posd);
        }
      }
      else if (str[0] == 'm')
      {
        double posd = str.substring(2).toDouble();
        int pasos = round((posd - 0.25181) / 0.00126);
        Motor_x.setSpeed(50);
        Motor_x.MovePosition(pasos);
        Serial.print("x(mm)=");
        Serial.println(posd);
      }
    }
  }
}

//Funciones auxiliares

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
