#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define PIN1 8 //Pin entrada donde está conectada la tira jugador 1

#define NUMPIXELS 8 //Número de leds conectados
#define COND 3 //condicion para que avance al siguiente led

/////////////////////////////////PULSADORES///////////////////////////////////////
const int pulsadorPin1 = 7;


Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800); //CONTROLA LA TIRA DE LED 1


int delayval = 100; // Tiempo de espera
int j1;

int contador1=0, cont1=0; // contador del jugador 1

int FLAG1=0;



int jugador1(void);



void setup() {

      pixels1.begin(); // Inicialización
      pixels1.show(); // Muestra los pixels apagados
      pinMode(pulsadorPin1, INPUT);


}

void loop() {

    j1= jugador1();
 
}


int jugador1(){
      
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
             FLAG1=1;
}
return FLAG1;
}
