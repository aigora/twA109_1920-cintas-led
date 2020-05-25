#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define PIN1 8 //Pin entrada donde está conectada la tira jugador 1
#define PIN2 9 //Pin entrada donde está conectada la tira jugador 2
#define NUMPIXELS 8 //Número de leds conectados
#define COND 3 //condicion para que avance al siguiente led

const int pulsadorPin1 = 7;
const int pulsadorPin2 = 10;

Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

int delayval = 100; // Tiempo de espera
int valorPulsador = 0;
int contador1=0, cont1=0; // contador del jugador 1
int contador2=0, cont2=0;

void jugador1(void);
void jugador2(void);

void setup() {

      pixels1.begin(); // Inicialización
      pixels1.show(); // Muestra los pixels apagados
      pixels2.begin(); // Inicialización
      pixels2.show(); // Muestra los pixels apagados
      pinMode(pulsadorPin1, INPUT);
      pinMode(pulsadorPin2, INPUT);
}

void loop() {
 
        jugador1();
        jugador2();
}

void jugador1(){
      
    //Para que se cumpla la condición para que avance uno
          if(digitalRead(pulsadorPin1)== HIGH){
            delay(100);
           if(digitalRead(pulsadorPin1) == LOW){
              contador1++;
              delay(50);
            }
          }
                 
       if (contador1 == COND){
        cont1++;
        contador1=0; 
       //Encender led
    pixels1.setPixelColor(cont1-1, 0,0,250); // Brillo moderado de color rojo
    pixels1.show(); // Envia la orden al hardware
    delay(delayval); 
   
  
        //Apagar led
    pixels1.setPixelColor(cont1-2, pixels1.Color(0,0,0)); // Apagar
    pixels1.show(); // Envia la orden al hardware
    delay(delayval);
 
  }
 
  if (cont1 == NUMPIXELS){
      for (int i=0;i<NUMPIXELS;i++){
            pixels1.setPixelColor(i, 0,0,250); // Brillo moderado de color rojo
            pixels1.show(); // Envia la orden al hardware
            delay(delayval);
      }
}

}

void jugador2(){
      
    //Para que se cumpla la condición para que avance uno
          if(digitalRead(pulsadorPin2)== HIGH){
            delay(100);
           if(digitalRead(pulsadorPin2) == LOW){
              contador2++;
              delay(50);
            }
          }
                 
       if (contador2 == COND){
        cont2++;
        contador2=0; 
       //Encender led
    pixels2.setPixelColor(cont2-1, 0,250,0); // Brillo moderado de color rojo
    pixels2.show(); // Envia la orden al hardware
    delay(delayval); 
   
  
        //Apagar led
    pixels2.setPixelColor(cont2-2, pixels2.Color(0,0,0)); // Apagar
    pixels2.show(); // Envia la orden al hardware
    delay(delayval);
 
  }
 
  if (cont2 == NUMPIXELS){
      for (int j=0;j<NUMPIXELS;j++){
            pixels2.setPixelColor(j, 0,250,0); // Brillo moderado de color rojo
            pixels2.show(); // Envia la orden al hardware
            delay(delayval);
      }
}

}
