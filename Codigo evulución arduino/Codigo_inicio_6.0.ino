#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define PIN1 8 //Pin entrada donde está conectada la tira jugador 1
#define PIN2 9 //Pin entrada donde está conectada la tira jugador 2
#define NUMPIXELS 8 //Número de leds conectados
#define COND 3 //condicion para que avance al siguiente led

/////////////////////////////////PULSADORES///////////////////////////////////////
const int pulsadorPin1 = 7;
const int pulsadorPin2 = 10;
const int interrup = 6;

LiquidCrystal lcd(12,11,5,4,3,2); //Donde se va a conectar la pantalla
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800); //CONTROLA LA TIRA DE LED 1
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800); //CONTROLA LA TIRA DE LED 2

int delayval = 100; // Tiempo de espera
int j1,j2;
/////////////////////////////////CONTADORES//////////////////////////////////////
int contador1=0, cont1=0; // contador del jugador 1
int contador2=0, cont2=0;
//////////////////////////////////BANDERAS///////////////////////////////////////
int FLAGinicio=0;
int FLAG1=0;
int FLAG2=0;
//////////////////////////////////FUNCIONES//////////////////////////////////////
void inicio(void);
int jugador1(void);
int jugador2(void);
void ganador1(void);
void ganador2(void);

void setup() {
      lcd.begin(16,2); //Indica el tamaño de la pantalla (c y f) y la inicia
      pixels1.begin(); // Inicialización
      pixels1.show(); // Muestra los pixels apagados
      pixels2.begin(); // Inicialización
      pixels2.show(); // Muestra los pixels apagados
      pinMode(pulsadorPin1, INPUT);
      pinMode(pulsadorPin2, INPUT);
      pinMode(interrup, INPUT);
}

void loop() {

   if(digitalRead(interrup) == HIGH){
           inicio();
           FLAGinicio=1;
   }
   if (FLAGinicio == 1){
               j1= jugador1();
               j2= jugador2();  

               if (j1 != j2){
                      if(j1<j2){
                             ganador2();
                      }
                      else{
                             ganador1();
               }
        
   }

      
}
}


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


int jugador2(){
      
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
            FLAG2=1;
}
return FLAG2;
}


void ganador1(){
                             lcd.setCursor(0,0); 
                             lcd.print("!Ganador Jugador");
                             lcd.setCursor(7,1);
                             lcd.print("1!");
                             delay(10000);
                             lcd.clear();
                             delay(100);
                             FLAGinicio=0;
                             for(int i=0;i<NUMPIXELS;i++){
                                  pixels1.setPixelColor(i, pixels1.Color(0,0,0)); // Apagar
                                  pixels1.show(); 
                                  delay(delayval);
                                  pixels2.setPixelColor(i, pixels2.Color(0,0,0)); // Apagar
                                  pixels2.show();
                                  delay(50);
                       
                      }

                            cont1=0;
                            cont2=0;
                            FLAG1=0;
}


void ganador2(){
                             lcd.setCursor(0,0); 
                             lcd.print("!Ganador Jugador");
                             lcd.setCursor(7,1);
                             lcd.print("2!");
                             delay(8000);
                             lcd.clear();
                             delay(100);
                             FLAGinicio=0;
                             for(int i=0;i<NUMPIXELS;i++){
                                  pixels1.setPixelColor(i, pixels1.Color(0,0,0)); // Apagar
                                  pixels1.show(); 
                                  delay(delayval);
                                  pixels2.setPixelColor(i, pixels2.Color(0,0,0)); // Apagar
                                  pixels2.show();
                                  delay(50);
                             }
                             cont1=0;
                             cont2=0;
                             FLAG2=0;
}
