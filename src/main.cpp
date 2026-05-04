#include <Arduino.h>

// Definimos nuestros pines
const int pinIzq = 12;
const int pinDer = 13;
const int pinDisp = 14;
const int ledPin = 2; 

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Configuramos el LED como salida
  pinMode(ledPin, OUTPUT);
  Serial.println("--- Iniciando monitor de sensores Touch ---");
}

void loop() {
  // Leemos los valores de los 3 sensores
  int valIzq = touchRead(pinIzq);
  int valDer = touchRead(pinDer);
  int valDisp = touchRead(pinDisp);

  // Imprimimos los valores para verlos en tiempo real
  Serial.print("Izq (12): "); Serial.print(valIzq);
  Serial.print(" | Der (13): "); Serial.print(valDer);
  Serial.print(" | Disparo (14): "); Serial.println(valDisp);

  // --- PRUEBA DE PWM Y FEEDBACK ---
  // Si tocamos el cable de disparo (el valor baja de 30), encendemos el LED con PWM
  if (valDisp < 30) { 
    // analogWrite manda una señal PWM (0 a 255). 
    // 10 = Brillo muy tenue, 127 = Brillo medio, 255 = Brillo máximo
    analogWrite(ledPin, 10); 
  } else {
    analogWrite(ledPin, 0); // Apagamos el LED si no tocamos
  }

  // Pequeña pausa para poder leer la terminal sin que vuelva loco a VS Code
  delay(200); 
}