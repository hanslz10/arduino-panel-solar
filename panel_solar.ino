#include <Servo.h>

// put function declarations here:
Servo servoH;
Servo servoV;
int fotoRes1 = A0;
int LDR;
int anguloV;
int anguloH;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(fotoRes1, INPUT);
  servoH.attach(9);
  servoV.attach(6);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  servoH.write(0); //establecer posicion inicial de H
  delay(25);
  servoV.write(0); //establecer posicion inicial de V
  delay(25);

  
  
  // Dar vuelta entera para analizar el angulo de giro donde menor resistencia haya en la fotoresistencia
  for (int i = 0; i < 360; i++)
  {
    servoH.write(i);
    delay(20); //permite realizar un giro suave y lento
    anguloH = servoH.read(); //lee los valores de los angulos que tomo el giro del motor en horizontal
    LDR = analogRead(fotoRes1); //lee la resistencia del fotoresistor
  }
  delay(100); // tiempo de espera para realizar el siguiente giro del otro servomotor

  // Girar servo VERTICAL a 90 (ya que aun no se como se hace para que gire a 90 en derecha y 90 a izquierda, sin que ocurra un problema con la lectura de angulo y sensores), y analizar donde este la menor resitencia en vertical
  for (int n = 0; n < 90; n++)
  {
    servoV.write(n);
    delay(20);
    anguloV = servoV.read();
    LDR = analogRead(fotoRes1);
  } 
  delay(25); // tiempo de espera para que en las siguiente lineas se ejecute el guarado de angulos donde se recibio la menor resistencia

   if (LDR < 700) // condicion cuando se detecte la maxima resistencia
  {
    servoH.write(anguloH);
    delay(25); // tiempo para que no cambien la poscion ambos servomotores a la vez, y no ocurra un problema
    servoV.write(anguloV);
  }
  delay(60000); // tiempo de espera en que se va a quedar en la posicion de maxima luz para que el panel se alimente en ese tiempo
}