#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define PIN1 8 //Pin entrada donde está conectada la tira jugador 1
#define PIN2 9 //Pin entrada donde está conectada la tira jugador 2
#define NUMPIXELS 8 //Número de leds conectados
#define COND 3 

const int pulsadorPin1 = 7;
const int pulsadorPin2 = 10;
const int interrup = 6;

LiquidCrystal lcd(12,11,5,4,3,2); 
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800); 
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800); 

int delayval = 100; 
int j1,j2; 

int contador1=0, cont1=0;
int contador2=0, cont2=0; 

int FLAGinicio=0;
int FLAG1=0;
int FLAG2=0;

void inicio(void);

int jugador1(void);
int jugador2(void);
void ganador1(void);
void ganador2(void);

void setup() {
      Serial.begin(9600);
      lcd.begin(16,2);
      pixels1.begin(); 
      pixels1.show(); 
      pixels2.begin(); 
      pixels2.show(); 
      pinMode(pulsadorPin1, INPUT);
      pinMode(pulsadorPin2, INPUT);
      pinMode(interrup, INPUT);
}

void loop() {

   //Al pulsar en el pulsadorInicio comienza la cuenta atrás
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
 lcd.setCursor(2,0);
 lcd.print("Preparados..."); 
 delay(1500);
 lcd.clear();
 delay(500);

 lcd.setCursor(4,0); 
 lcd.print("Listos..."); 
 delay(1500);
 lcd.clear();
 delay(500);

 lcd.setCursor(6,0); 
 lcd.print("Ya!!"); 
 delay(1500);
 lcd.clear();
 delay(500);

 lcd.noBlink();
}


int jugador1(){
      
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
  
    pixels1.setPixelColor(cont1-1, 0,0,250);
    pixels1.show(); 
    delay(delayval); 
   
    pixels1.setPixelColor(cont1-2, pixels1.Color(0,0,0));
    pixels1.show();
    delay(delayval);
 
  }

  if (cont1 == NUMPIXELS){
      for (int i=0;i<NUMPIXELS;i++){
            pixels1.setPixelColor(i, 0,0,250);
            pixels1.show();
            delay(delayval);

      }
             FLAG1=1;
}
return FLAG1;
}


int jugador2(){
     
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
        
    pixels2.setPixelColor(cont2-1, 0,250,0);
    pixels2.show();
    delay(delayval); 
   
    pixels2.setPixelColor(cont2-2, pixels2.Color(0,0,0));
    pixels2.show();
    delay(delayval);
 
  }

  if (cont2 == NUMPIXELS){
      for (int j=0;j<NUMPIXELS;j++){
            pixels2.setPixelColor(j, 0,250,0);
            pixels2.show();
            delay(delayval);
      }
            FLAG2=1;
}
return FLAG2;
}


void ganador1(){
                             Serial.print("1");
                             lcd.setCursor(0,0); 
                             lcd.print("!Ganador Jugador");
                             lcd.setCursor(7,1);
                             lcd.print("1!");
                             delay(10000);
                             lcd.clear();
                             delay(100);
                             FLAGinicio=0;
                             for(int i=0;i<NUMPIXELS;i++){ 
                                  pixels1.setPixelColor(i, pixels1.Color(0,0,0));
                                  pixels1.show(); 
                                  delay(delayval);
                                  pixels2.setPixelColor(i, pixels2.Color(0,0,0));
                                  pixels2.show();
                                  delay(50);
                       
                      }
                            cont1=0;
                            cont2=0;
                            FLAG1=0;
                           
}


void ganador2(){
                             Serial.print("2");
                             lcd.setCursor(0,0); 
                             lcd.print("!Ganador Jugador");
                             lcd.setCursor(7,1);
                             lcd.print("2!");
                             delay(8000);
                             lcd.clear();
                             delay(100);
                             FLAGinicio=0;
                             for(int i=0;i<NUMPIXELS;i++){
                                  pixels1.setPixelColor(i, pixels1.Color(0,0,0));
                                  pixels1.show(); 
                                  delay(delayval);
                                  pixels2.setPixelColor(i, pixels2.Color(0,0,0));
                                  pixels2.show();
                                  delay(50);
                             }
                             cont1=0;
                             cont2=0;
                             FLAG2=0;
                          
}
