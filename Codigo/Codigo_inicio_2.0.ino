#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define PIN1 8 //Pin entrada donde está conectada la tira jugador 1
#define PIN2 9 //Pin entrada donde está conectada la tira jugador 2
#define NUMPIXELS 8 //Número de leds conectados
#define COND 3 //condicion para que avance al siguiente led

LiquidCrystal lcd(12,11,5,4,3,2); //Donde se va a conectar la pantalla
const int interrup = 6;
int interrpest = 0;


const int pulsadorPin1 = 7;
const int pulsadorPin2 = 10;

Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
int delayval = 100; // Tiempo de espera
int valorPulsador = 0;
int contador1=0, cont1=0; // contador del jugador 1
int contador2=0, cont2=0; // contador del jugador 2

void inicio(void);
void jugador1(void);
void jugador2(void);

void setup() {
      lcd.begin(16,2); //Indica el tamaño de la pantalla (c y f) y la inicia
      pixels1.begin(); // Inicialización
      pixels1.show(); // Muestra los pixels apagados
      pixels2.begin(); // Inicialización
      pixels2.show(); // Muestra los pixels apagados
      pinMode(pulsadorPin1, INPUT);
      pinMode(pulsadorPin2, INPUT);
}

void loop() {
        if(digitalRead(interrup) == HIGH){
                inicio();
        }
        jugador1();
        jugador2();
}

//Funcion encargada de la pantalla
void inicio(){
 lcd.setCursor(2,0); //Indica la posición donde se desea escribir (c y f)
 lcd.print("Preparados..."); //para imprimir por pantalla
 delay(1500);
 lcd.clear();
 delay(500);

 lcd.setCursor(4,0); //Indica la posición donde se desea escribir (c y f)
 lcd.print("Listos..."); //para imprimir por pantalla
 delay(1500);
 lcd.clear();
 delay(500);

 lcd.setCursor(6,0); //Indica la posición donde se desea escribir (c y f)
 lcd.print("Ya!!"); //para imprimir por pantalla
 delay(1500);
 lcd.clear();
 delay(500);

 lcd.noBlink();
}

void jugador1(){
     
     for(int i=0;i< NUMPIXELS; i++){ 
    
    //Para que se cumpla la condición para que avance uno
        while (contador1 < COND){
          if(digitalRead(pulsadorPin1)== HIGH){
            delay(100);
            if(digitalRead(pulsadorPin1) == LOW){
              contador1++;
              delay(50);
            }
          }
                 
        }
       
       if (contador1 == COND){
       //Encender led
    pixels1.setPixelColor(i, 0,0,250); // Brillo moderado de color rojo
    pixels1.show(); // Envia la orden al hardware
    delay(delayval); 
    cont1++;   
        //Apagar led
    pixels1.setPixelColor(i-1, pixels1.Color(0,0,0)); // Apagar
    pixels1.show(); // Envia la orden al hardware
    delay(delayval);
 
  }
   contador1=0;
  if (cont1 == NUMPIXELS){
      for (int i=0;i<NUMPIXELS;i++){
            pixels1.setPixelColor(i, 0,0,250); // Brillo moderado de color rojo
            pixels1.show(); // Envia la orden al hardware
            delay(delayval);
      }
}
}
}

void jugador2(){
     
     for(int j=0;j< NUMPIXELS; j++){ 
    
    //Para que se cumpla la condición para que avance uno
        while (contador2 < COND){
          if(digitalRead(pulsadorPin2)== HIGH){
            delay(100);
            if(digitalRead(pulsadorPin2) == LOW){
              contador2++;
              delay(50);
            }
          }
                 
        }
       
       if (contador2 == COND){
       //Encender led
    pixels2.setPixelColor(j, 250,0,0); // Brillo moderado de color rojo
    pixels2.show(); // Envia la orden al hardware
    delay(delayval); 
    cont2++;   
        //Apagar led
    pixels2.setPixelColor(j-1, pixels2.Color(0,0,0)); // Apagar
    pixels2.show(); // Envia la orden al hardware
    delay(delayval);
 
  }
   contador2=0;
  if (cont2 == NUMPIXELS){
      for (int j=0;j<NUMPIXELS;j++){
            pixels2.setPixelColor(j, 250,0,0); // Brillo moderado de color rojo
            pixels2.show(); // Envia la orden al hardware
            delay(delayval);
      }
}
}
}

// https://programarfacil.com/blog/utilizar-pulsadores-en-arduino/
// https://www.youtube.com/watch?v=BQHMMlEAj3g
