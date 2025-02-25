#include <ESP32Servo.h>
#include <PS4Controller.h>

const int escPin = 18;  // Pin donde conectas la señal del ESC
Servo motorESC; //El motor se controla por PWM como un servo

const int pinServo = 13; //Pin donde conectas la señal del servo
Servo servoMotor; //Servo se controla por PWM

void setup() {

	Serial.begin(115200); //Inicializa el monitor a 115200 baudios
	PS4.begin(); // Inicializa el mando
	motorESC.attach(escPin); // Rango del ESC (1000-2000 µs)

	// Calibración del ESC:  Importante para que el motor se configure
	motorESC.writeMicroseconds(2000); // Máxima señal (arranque seguro)
	delay(2000); //Mas o menos lo que dura el motor en calibrar
	motorESC.writeMicroseconds(1000); // Mínima señal
	delay(2000);
	motorESC.writeMicroseconds(1500); // Neutro
	delay(2000);

	servoMotor.attach(pinServo);
	servoMotor.write(90);
	delay(2000);
}

void Control_Motor() {

	int escValue;
	if (PS4.L2()) {  // Si se presiona L2 (marcha atrás)
		escValue = map(PS4.L2Value(), 0, 255, 1500, 1000); // 1000 = reversa
		Serial.printf("Reversa: %d\n", escValue);
	}
	else if (PS4.R2()) {  // Si se presiona R2 (marcha adelante)
		escValue = map(PS4.R2Value(), 0, 255, 1500, 2000); // 2000 = máxima velocidad
		Serial.printf("Adelante: %d\n", escValue);
	}
	else {
		escValue = 1500;
	}
	// Envía la señal PWM al ESC y asegura que el valor esté dentro del rango permitido
	motorESC.writeMicroseconds(constrain(escValue, 1000, 2000));

	millis(10); //Para estabilidad del ESC
}

void Control_Servo() {
	if (PS4.RStickX() <= 10 && PS4.RStickX() >= -10) { //Zona muerta del jostick (evita el drift)
		servoMotor.write(90); //Centra el servo "Ruedas Rectas"
	}
	if (PS4.RStickX() >= 10 || PS4.RStickX() <= -10) {
		int angle = map(PS4.RStickX(), 127, -127, 45, 135);
		servoMotor.write(constrain(angle, 45, 135)); //Mueve el servo segun la posicion del jostick
	}
}

void loop() {
	// put your main code here, to run repeatedly:
	if (PS4.isConnected()) {
		Control_Motor();
		Control_Servo();
	}
}
