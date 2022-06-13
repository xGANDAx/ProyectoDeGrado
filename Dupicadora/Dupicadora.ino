// Declaracion librerias
#include "Stepper.h"
#include "Funciones.h"
#include "stdint.h"

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

// Declaracion variables
bool key_ready = false;
uint16_t steps_x = 0;
uint16_t steps_a = 0;
uint16_t llave[1500];

// Declaracion de los motores
Stepper Motor_x(Pin_Enable_Motor_X, Pin_Dir_Motor_X, Pin_Pulse_Motor_X, Pin_Sensor_X, false);
Stepper Motor_a(Pin_Enable_Motor_A, Pin_Dir_Motor_A, Pin_Pulse_Motor_A, Pin_Sensor_A, false);

void setup()
{
  Serial.begin(9600);
  // Inicializacion pantalla

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

  // Motor_a.disable();
  // Motor_x.disable();

  // generarLlave(llave);
  //     Serial.println("empezando ...");
  //     Motor_x.setSpeed(25);
  //     Motor_x.reset();
}

void loop()
{

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
  if (Serial.available())
  {
    String str = Serial.readStringUntil('\n');
    str.trim();
    if (str == "c")
    {
      Motor_a.setSpeed(50);
      Motor_a.reset();
      Motor_x.setSpeed(25);
      Motor_x.MovePosition(31500);
      // Pantallazo "introduzca las llaves y oprima listo"
      Serial.println("oprima culaquier tecla para continuar");
      key_ready = false;
      while (true)
      {
        if (Serial.available())
        {
          key_ready = true;
        }

        if (key_ready == true) break;
      }
      // Pantallazo "espere a que termine...""
      Serial.println("Realizando llave");
      Motor_a.setSpeed(100);
      Motor_a.MovePosition(5300);
      digitalWrite(Pin_Rele, HIGH);
      Motor_a.disable();
      Motor_x.setSpeed(300);
      Motor_x.reset();
      Motor_a.setSpeed(200);
      Motor_a.MoveSteps(-800);
      Motor_x.setSpeed(25);
      Motor_x.MovePosition(31500);
      Motor_a.setSpeed(100);
      Motor_a.disable();
      Motor_x.setSpeed(300);
      Motor_x.reset();

      Motor_a.reset();
      digitalWrite(Pin_Rele, LOW);
      //  Pantallazo "finalizado"
      //  Pantallazo "activar grata"
      // digitalWrite(Pin_Rele, LOW);
      // delay(60000);
      // digitalWrite(Pin_Rele, HIGH);

      Serial.println("Finalizado");
      Motor_x.sound(4);
      delay(300);
      Motor_x.sound(4);
    } else if (str == "m") {
      digitalWrite(Pin_Rele, LOW);
    }else if (str == "n") {
      digitalWrite(Pin_Rele, HIGH);
    }

  }
}
