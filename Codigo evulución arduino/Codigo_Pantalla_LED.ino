#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2); //Donde se va a contar la pantalla

const int interrup = 6;
int interrpest = 0;
void inicio(void);

void setup() {

  lcd.begin(16,2); //Indica el tamaño de la pantalla (c y f) y la inicia
  
}

void loop() {
  if(digitalRead(interrup) == HIGH){
   inicio();
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
