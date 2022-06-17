// Declaracion librerias
#include "FS.h"

#include "Stepper.h"
#include "Funciones.h"
#include "stdint.h"
#include <SPI.h>
#include <TFT_eSPI.h>


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
TFT_eSPI_Button Home;

// Declaracion variables
bool key_ready = false;
uint16_t steps_x = 0;
uint16_t steps_a = 0;
uint16_t llave[1500];
uint8_t progreso = 5;
uint16_t t_x = 0, t_y = 0;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  actualizarCarga(tft, progreso);
  if (progreso < 255) {
    progreso++;
  } else {
    progreso = 255;
  }
  portEXIT_CRITICAL_ISR(&timerMux);

}

// Declaracion de los motores
Stepper Motor_x(Pin_Enable_Motor_X, Pin_Dir_Motor_X, Pin_Pulse_Motor_X, Pin_Sensor_X, false, 25);
Stepper Motor_a(Pin_Enable_Motor_A, Pin_Dir_Motor_A, Pin_Pulse_Motor_A, Pin_Sensor_A, false, 50);

void setup()
{
  Serial.begin(9600);
  // Inicializacion pantalla
  tft.begin();
  tft.setRotation(1);
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

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 212000, true);

  touch_calibrate();

  // Reset de los motores
  Motor_a.setSpeed(50);
  Motor_a.reset();
  Motor_x.setSpeed(25);
  Motor_x.reset();

  //    Motor_a.setSpeed(200);
  //    Motor_a.MoveSteps(5200);
  //    Motor_x.setSpeed(50);
  //    Motor_x.MoveSteps(30000);
  Motor_x.sound(4);
  delay(300);
  Motor_x.sound(4);

  //Motor_a.disable();
  //Motor_x.disable();

  // Motor_a.disable();
  // Motor_x.disable();

  // generarLlave(llave);
  //     Serial.println("empezando ...");
  //     Motor_x.setSpeed(25);
  //     Motor_x.reset();
}

void loop()
{
  progreso = 0;
  Serial.println("Seleccione modo a utilizar:");
  Serial.println("C: Copiar");
  Serial.println("G: Generar");
  menu(tft, copia, generar);

  while (true)
  {
    t_x = 0;
    t_y = 0;
    boolean pressed = tft.getTouch(&t_x, &t_y);
    if (Serial.available() || pressed )
    {
      String str = Serial.readStringUntil('\n');
      str.toLowerCase();
      str.trim();
      Serial.print(t_x);
      Serial.print(", ");
      Serial.println(t_y);
      if (str == "c" || copia.contains(t_x, t_y))
      {
        menuCopia(tft,copiaListo,Home);
        Motor_a.reset();
        Motor_x.reset();
        Motor_x.setSpeed(25);
        Motor_x.MovePosition(31500);
        // Pantallazo "introduzca las llaves y oprima listo"
        Serial.println("Oprima cualquier tecla para continuar");
        key_ready = false;

        while (true)
        {
          t_x = 0;
          t_y = 0;
          if (Serial.available()||pressed )
          {
            key_ready = true;
          }

          if (key_ready == true)
          {
            timerAlarmEnable(timer);
            copiaCarga(tft);
            break;
          }
        }
        // Pantallazo "espere a que termine...""
        Serial.println("Realizando llave ...");

        Motor_a.setSpeed(100);
        Motor_a.MovePosition(5300);
        digitalWrite(Pin_Rele, HIGH);
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
        Motor_x.sound(4);
        delay(300);
        Motor_x.sound(4);
        timerAlarmDisable(timer);
        finalizado(tft,Home);
        //  Pantallazo "finalizado"
        Serial.println("Finalizado");
        //  Pantallazo "activar grata
        Serial.println("Desea activar grata:");
        Serial.println("S: Si");
        Serial.println("N: No");

        while (true)
        {
          if (Serial.available())
          {
            String str = Serial.readStringUntil('\n');
            str.toLowerCase();
            str.trim();
            if (str == "s")
            {
              digitalWrite(Pin_Rele, HIGH);
              while (true)
              {
                if (Serial.available())
                {
                  digitalWrite(Pin_Rele, LOW);
                  break;
                }
              }
              break;
            }
            else if (str == "n")
            {
              break;
            }
          }
        }
        break;
      }

      else if (str == "m")
      {
        digitalWrite(Pin_Rele, LOW);
      }
      else if (str == "n")
      {
        digitalWrite(Pin_Rele, HIGH);
      }
    }
  }

  //  if (Serial.available()) {
  //    String str = Serial.readStringUntil('\n');
  //
  //    Serial.println("recibido");
  //    if (str[0] == 'x') {
  //      int posd = str.substring(2).toInt();
  //      Motor_x.setSpeed(50);
  //      Motor_x.MovePosition(posd);
  //      Serial.print("x=");
  //      Serial.println(posd);
  //    }
  //    if (str[0] == 'a') {
  //      int posd = str.substring(2).toInt();
  //      if (posd < 0) {
  //        Motor_a.disable();
  //      } else {
  //        Motor_a.setSpeed(200);
  //        Motor_a.MovePosition(posd);
  //        Serial.print("a=");
  //        Serial.println(posd);
  //      }
  //    }
  //  }
  // Pantallazo "Menu principal:Copia, generar llave"
}


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
