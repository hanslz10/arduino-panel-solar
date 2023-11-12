#include <Arduino.h>
#include <Servo.h>

// put function declarations here:
Servo servoH;
Servo servoV;
int fr1, fr2, fr3, fr4 = A0, A1, A2, A3; // declaraciones de puertos analogicos a usar por las fotoresistencias
int LDR1, LDR2, LDR3, LDR4; // declaracion de variables de lectura de fotoresistencias
int anguloV, anguloH; //declaracion de variables para almacenar los angulos de los servomotores

void setup() 
{
  // put your setup code here, to run once:
  pinMode(fr1, INPUT); // establecer comportamiendo de los pines analogicos tomados por las fotoresistencias
  pinMode(fr2, INPUT);
  pinMode(fr3, INPUT);
  pinMode(fr4, INPUT);
  servoH.attach(9); //establece numero de entrada de pin a usar del servomotor horizontal
  servoV.attach(6); //establece numero de entrada de pin a usar del servomotor vertical
  servoH.write(90); //establecer posicion inicial de H
  delay(25);
  servoV.write(90); //establecer posicion inicial de V
  delay(25);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  for (int i = 0; i < 360; i++) // Dar vuelta entera para analizar el angulo de giro de un servomotor de 360° donde haya menor resistencia o maxima cantidad de luz, 
  {
    servoH.write(i);
    delay(20); //permite realizar un giro suave y estable
    anguloH = servoH.read(); // lectura del angulo del servo, que se guardara en la variable anguloH
    LDR1 = analogRead(fr1); // lectura de la fotoresistencia, que se guardara en la variable  LDR1
    LDR2 = analogRead(fr2);
    LDR3 = analogRead(fr3);
    LDR4 = analogRead(fr4);
  }

  
  for (int n = 0; n < 90; n++) // Girar servo VERTICAL a 90
  {
    servoV.write(n);
    delay(20); //permite realizar un giro suave y estable
    anguloV = servoV.read();// lectura del angulo del servo, que se guardara en la variable anguloV
    LDR1 = analogRead(fr1);// lectura de la fotoresistencia, que se guardara en la variable  LDR1
    LDR2 = analogRead(fr2);
    LDR3 = analogRead(fr3);
    LDR4 = analogRead(fr4);
  } 
  
  int LDRp = (LDR1 + LDR2 + LDR3 + LDR4)/4; //resistencia promedio a partir de las lecturas realizadas que se almacenaron en las variables LDR
  
   if (LDRp < 80) // condicion cuando se detecte la minima resistencia promedio y en consecuencia la maxima luz
  {
    servoH.write(anguloH); //establece la posicion del servomotor horizontal con el angulo donde se encuentre la maxima fuente de luz
    servoV.write(anguloV); //establece la posicion del servomotor vertical con el angulo donde se encuentre la maxima fuente de luz
  }
}
