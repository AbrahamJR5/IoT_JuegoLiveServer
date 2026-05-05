#include <Arduino.h>

const int pinIzq = 12;
const int pinDer = 13;
const int pinDisp = 14;
const int ledPin = 2; 

const int umbral = 90; 

unsigned long tiempoGolpe = 0;
bool recibioGolpe = false;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0); 
}

void loop() {
  int valIzq = touchRead(pinIzq);
  int valDer = touchRead(pinDer);
  int valDisp = touchRead(pinDisp);

  if (valIzq < umbral) {
    Serial.println("I");
  }
  if (valDer < umbral) {
    Serial.println("D");
  }
  if (valDisp < umbral) {
    Serial.println("A");
  }

  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    if (comando == "HIT") {
      recibioGolpe = true;
      tiempoGolpe = millis();
    }
  }


  if (recibioGolpe) {
    unsigned long tiempoPasado = millis() - tiempoGolpe;
    
    if (tiempoPasado < 500) {
      int intensidad = (tiempoPasado / 50) % 2 == 0 ? 255 : 50; 
      analogWrite(ledPin, intensidad);
    } else {
      recibioGolpe = false; 
      analogWrite(ledPin, 0); 
    }
  }

  delay(30);
}