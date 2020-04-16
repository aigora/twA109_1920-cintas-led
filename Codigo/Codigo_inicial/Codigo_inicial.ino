
#include <Adafruit_NeoPixel.h>

int PIN=6; //Pin donde está conectada la tira de leds
int NUMPIXELS=8; //Número de leds conectados
const int pulsadorPin = 2;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // Tiempo de espera 
int valorPulsador = 0;

void setup() {
      pixels.begin(); // Inicialización
      pixels.show(); // Inicializa pixels apagados
      pinMode(pulsadorPin, INPUT);
}

void loop() {
  valorPulsador = digitalRead(pulsadorPin);
  if (valorPulsador == HIGH){
      
       //Encender led
    pixels.setPixelColor(i, 100,0,0); // Brillo moderado de color rojo
    pixels.show(); // Envia la orden al hardware
    delay(delayval); 
        
        //Apagar led
    pixels.setPixelColor(i-1, pixels.Color(0,0,0)); // Apagar
    pixels.show(); // Envia la orden al hardware
    delay(delayval); 
  }

   
}

// https://programarfacil.com/blog/utilizar-pulsadores-en-arduino/
// https://www.youtube.com/watch?v=BQHMMlEAj3g
