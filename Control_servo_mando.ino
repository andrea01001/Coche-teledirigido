#include <ESP32Servo.h>
#include <PS4Controller.h>

const int pinServo = 13;
Servo servoMotor;

void setup() {
	PS4.begin();
	servoMotor.attach(pinServo);
	servoMotor.write(90);
}

void loop() {
	if (PS4.isConnected()) {//Comprueba que el mando este conectado
		if (PS4.RStickX() <= 10 && PS4.RStickX() >= -10) { //Zona muerta del jostick (evita el drift)
			servoMotor.write(90); //Centra el servo "Ruedas Rectas"
		}
		if (PS4.RStickX() >= 10 || PS4.RStickX() <= -10) { //PS4.RStickX() Lee el valor del jostick derecho en el eje x
			int angle = map(PS4.RStickX(), 127, -127, 45, 135);
			servoMotor.write(constrain(angle, 45, 135)); //Mueve el servo segun la posicion del jostick
		}
	}
}
/* Depende de como funciona a la hora de controlar el coche, podriamos modificar el codigo para
que el movimiento sea mas suave a la hora de girar */
