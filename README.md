## Título del trabajo
Cintas led

##Descripcion del trabajo
El trabajo consiste en hacer una carrera con cintas led, habrá dos usuarios que serán los participantes, cada uno contara con un controlador con un pulsador que hara que avancen los leds, de tal modo que el que consiga encender antes el ultimo led de la su cinta, gana.

## Integrantes del equipo
Fernando María del Castillo Belloso, fmdelcastillo
Luis Pérez González, luispgonzalez
Víctor Rodríguez Sánchez, victorroriguezsanchez

## Objetivos del trabajo
Con este trabajo pretendemos desarrollar e implementar nuestros conocimientos en el ámbito de arduino, combinado con el lenguaje de programación C. Y así combinar el software con el hardware en el proyecto.

## Elementos
Una placa de arduino, dos cintas led, dos pulsadores, pantalla led. El proyecto se desarrollará el código C y arduino.

## Montaje del proyecto

![](https://github.com/aigora/twA109_1920-cintas-led/blob/master/Images/Montaje%20de%20la%20carrera%20con%20cintas%20led.JPG)

## Codigo Arduino

"#include <LiquidCrystal.h>
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
int j1,j2; //varibles de cada jugador

/////////////////////////////////CONTADORES//////////////////////////////////////
int contador1=0, cont1=0; // contadores del jugador 1
int contador2=0, cont2=0; // contadores del jugador 2

//////////////////////////////////BANDERAS///////////////////////////////////////
int FLAGinicio=0; //Con esta bandera se permite el acceso para que los pulsadores 1 y 2 vayan
int FLAG1=0; //Se utiliz para saber si el jugador 1 ha llegado al final de la tira
int FLAG2=0; //Se utiliz para saber si el jugador 2 ha llegado al final de la tira

//////////////////////////////////FUNCIONES//////////////////////////////////////
void inicio(void);//Temporizador en la pantalla LED

int jugador1(void);//Contabiliza las pulsaciones y hace que los leds se enciendan y se apaguen del jugador 1
int jugador2(void);//Contabiliza las pulsaciones y hace que los leds se enciendan y se apaguen del jugador 2

void ganador1(void);//En caso de que gane el jugador 1
void ganador2(void);//En caso de que gane el jugador 2

//////////////////////////////////CÓDIGO//////////////////////////////////////
void setup() {
      lcd.begin(16,2); //Indica el tamaño de la pantalla (c y f) y la inicia
      pixels1.begin(); // Inicialización tira 1
      pixels1.show(); // Muestra los pixels
      pixels2.begin(); // Inicialización tira 2
      pixels2.show(); // Muestra los pixels
      Serial.begin(9600);

      //Inicia la señal de los pulsadores
      pinMode(pulsadorPin1, INPUT);
      pinMode(pulsadorPin2, INPUT);
      pinMode(interrup, INPUT);
}

void loop() {

   //Al pulsar en el pulsadorInicio (el de la izquierda del todo) comienza la cuenta atrás
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


/////////////////////////////////////////////FUNCION INICIO/////////////////////////////////////////////

void inicio(){
 lcd.setCursor(2,0); //Indica la posición donde se desea escribir (c y f)
 lcd.print("Preparados..."); //para imprimir por pantalla
 delay(1500);
 lcd.clear();//Limpiar la pantalla
 delay(500);

 lcd.setCursor(4,0); //Indica la posición donde se desea escribir (c y f)
 lcd.print("Listos..."); //para imprimir por pantalla
 delay(1500);
 lcd.clear();//Limpiar la pantalla
 delay(500);

 lcd.setCursor(6,0); //Indica la posición donde se desea escribir (c y f)
 lcd.print("Ya!!"); //para imprimir por pantalla
 delay(1500);
 lcd.clear();//Limpiar la pantalla
 delay(500);

 lcd.noBlink();
}


/////////////////////////////////////////////FUNCION JUGADOR1/////////////////////////////////////////////

int jugador1(){
      
    //Para que se cumpla la condición para que avance un LED al pulsar el pulsador1 (de los dos pegados el de la izquierda)
          if(digitalRead(pulsadorPin1)== HIGH){
            delay(100);
           if(digitalRead(pulsadorPin1) == LOW){
              contador1++;
              delay(50);
            }
          }
                 
       if (contador1 == COND){
        cont1++;//Contador que controla los LED para que se enciendad y apaguen en orden
        contador1=0; //Reiniciar contador a 0 para la siguiente vez que pulse las veces de la COND
       //Encender led
    pixels1.setPixelColor(cont1-1, 0,0,250); // Brillo de color azul
    pixels1.show(); // Envia la orden al hardware
    delay(delayval); 
   
  
        //Apagar led
    pixels1.setPixelColor(cont1-2, pixels1.Color(0,0,0)); // Apagar
    pixels1.show(); // Envia la orden al hardware
    delay(delayval);
 
  }

  //Si gana el jugador 1 se encenderan todos los LEDs de su tira
  if (cont1 == NUMPIXELS){
      for (int i=0;i<NUMPIXELS;i++){
            pixels1.setPixelColor(i, 0,0,250); // Brillo de color azul
            pixels1.show(); // Envia la orden al hardware
            delay(delayval);

      }
             FLAG1=1;
}
return FLAG1;
}


/////////////////////////////////////////////FUNCION JUGADOR2/////////////////////////////////////////////

int jugador2(){
      
    //Para que se cumpla la condición para que avance un LED al pulsar el pulsador2 (de los dos pegados el de la derecha)
          if(digitalRead(pulsadorPin2)== HIGH){
            delay(100);
           if(digitalRead(pulsadorPin2) == LOW){
              contador2++;
              delay(50);
            }
          }
                 
       if (contador2 == COND){
        cont2++;  //Contador que controla los LED para que se enciendad y apaguen en orden
        contador2=0; //Reiniciar contador a 0 para la siguiente vez que pulse las veces de la COND
       //Encender led
    pixels2.setPixelColor(cont2-1, 0,250,0); // Brillo de color verde
    pixels2.show(); // Envia la orden al hardware
    delay(delayval); 
   
  
        //Apagar led
    pixels2.setPixelColor(cont2-2, pixels2.Color(0,0,0)); // Apagar
    pixels2.show(); // Envia la orden al hardware
    delay(delayval);
 
  }

  //Si gana el jugador 2 se encenderan todos los LEDs de su tira
  if (cont2 == NUMPIXELS){
      for (int j=0;j<NUMPIXELS;j++){
            pixels2.setPixelColor(j, 0,250,0); // Brillo de color verde
            pixels2.show(); // Envia la orden al hardware
            delay(delayval);
      }
            FLAG2=1;
}
return FLAG2;
}


/////////////////////////////////////////////FUNCION GANADOR1/////////////////////////////////////////////

void ganador1(){
                             Serial.print("1");
                             lcd.setCursor(0,0); 
                             lcd.print("!Ganador Jugador");
                             lcd.setCursor(7,1);
                             lcd.print("1!");
                             delay(8000);//Pasaran 8 segundos y la pantalla se apagara y reiniciará el juego a partir de aqui
                             lcd.clear();
                             delay(100);
                             FLAGinicio=0; //Para resetear el juego y que se vuelva a dar la salida
                             for(int i=0;i<NUMPIXELS;i++){ //Apagar los LEDs de las dos tiras
                                  pixels1.setPixelColor(i, pixels1.Color(0,0,0)); // Apagar
                                  pixels1.show(); 
                                  delay(delayval);
                                  pixels2.setPixelColor(i, pixels2.Color(0,0,0)); // Apagar
                                  pixels2.show();
                                  delay(50);
                       
                      }
                            //Volver a dejar las variables a 0
                            cont1=0;
                            cont2=0;
                            FLAG1=0;
}


/////////////////////////////////////////////FUNCION GANADOR2/////////////////////////////////////////////

void ganador2(){
                             Serial.print("2"); //Le enviamos el 2 al dec C++ para que imprima por pantalla el ganador
                             lcd.setCursor(0,0); 
                             lcd.print("!Ganador Jugador");
                             lcd.setCursor(7,1);
                             lcd.print("2!");
                             delay(8000);//Pasaran 8 segundos y la pantalla se apagara y reiniciará el juego a partir de aqui
                             lcd.clear();
                             delay(100);
                             FLAGinicio=0; //Para resetear el juego y que se vuelva a dar la salida
                             for(int i=0;i<NUMPIXELS;i++){ //Apagar los LEDs de las dos tiras
                                  pixels1.setPixelColor(i, pixels1.Color(0,0,0)); // Apagar
                                  pixels1.show(); 
                                  delay(delayval);
                                  pixels2.setPixelColor(i, pixels2.Color(0,0,0)); // Apagar
                                  pixels2.show();
                                  delay(50);
                             }
                             //Volver a dejar las variables a 0
                             cont1=0;
                             cont2=0;
                             FLAG2=0;
}
"

## Codigo C

'#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"
#define MAX_DATA_LENGTH 255

void Crear_Conexion(SerialPort *PuertoSerie,char *portName);
void CerrarConexion(SerialPort *PueroSerie);
int readSerialPort(SerialPort * PuertoSerie,char *, unsigned int buf_size);
int writeSerialPort(SerialPort *PuertoSerie,char *, unsigned int buf_size);
int isConnected(SerialPort *PuertoSerie);
void autoConnect(SerialPort *arduino,char*);
void anotar(SerialPort *arduino,char *incomingData,int,int*,int*);
int main(void)
{
    SerialPort *arduino;
    char* portName = "\\\\.\\COM5";
    char incomingData[MAX_DATA_LENGTH];

    arduino = (SerialPort *)malloc(sizeof(SerialPort));
 // Apertura del puerto serie
    Crear_Conexion(arduino,portName);
    autoConnect(arduino,incomingData);
}
void autoConnect(SerialPort *arduino,char *incomingData)
{
    int readResult;
    int i=1;
    int cont1=0, cont2=0;

    while (!isConnected(arduino))
    {
      Sleep(100);
      Crear_Conexion(arduino,arduino->portName);
    }
 //Comprueba si arduino está connectado
    if (isConnected(arduino))
    {
      printf ("Conectado con Arduino en el puerto %s\n",arduino->portName);
    }
 // Bucle de la aplicación
    while (isConnected(arduino))
    {
      readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
      if (readResult!=0){
      	  	    printf("Ya tenemos al ganador de la partida %d\n", i);
      	  	    printf("El ganador es el jugador: %s\n", incomingData);
      	  	    printf("\n");
      	  	    if(strcmp(incomingData,"1")==0 || strcmp(incomingData,"2")==0)
      	  	    anotar(arduino,incomingData,i,&cont1,&cont2);
      	  	    i++;
			}
			 Sleep(10);
	}
    
    if (!isConnected(arduino))
       printf ("Se ha perdido la conexión con Arduino\n");
}

void anotar(SerialPort *arduino,char *incomingData,int i,int *contador1,int *contador2){
	
	FILE *fichero;
	int readResult;
   	int aux1, aux2;
	int est1=0;
	int est2=0;
	
	aux1=*contador1;
	aux2=*contador2;	
	fichero = fopen ("Resultados.txt","a+");
	readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
	
	if(fichero == NULL)
        	printf("Error al abrir el fichero\n");
		
	else{
readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);

	while(strcmp(incomingData,"1") && est1==0){

			fprintf(fichero, "Partida %d: \n", i);
			aux1=aux1+3;
			aux2=aux2+1;
			fprintf(fichero,"Marcador: Equipo 1: %d puntos           Equipo 2: %d puntos\n\n", aux1, aux2);

			*contador1=aux1;
			*contador2=aux2;
			est1=1;
		readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
	}
	while(strcmp(incomingData,"2") && est2==0){
		
			fprintf(fichero, "Partida %d:\n", i);
			aux1=aux1+1;
			aux2=aux2+3;
			fprintf(fichero,"Marcador: Equipo 1: %d puntos           Equipo 2: %d puntos\n\n", aux1, aux2);

			*contador1=aux1;
			*contador2=aux2;
			est2=1;
	readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
	}
	}
fclose(fichero);

}
void Crear_Conexion(SerialPort *PuertoSerie, char *portName)
{

	PuertoSerie->connected = 0;
	PuertoSerie->portName = portName;
    PuertoSerie->handler = CreateFileA((portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (PuertoSerie->handler == INVALID_HANDLE_VALUE)
	{
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
            printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
        }
    	else
        {
            printf("ERROR!!!");
        }
    }
    else 
	{
        DCB dcbSerialParameters = {0};

        if (!GetCommState(PuertoSerie->handler, &dcbSerialParameters))
		{
            printf("failed to get current serial parameters");
        }
        else 
		{
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(PuertoSerie->handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else 
			{
                PuertoSerie->connected = 1;
                PurgeComm(PuertoSerie->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
    return ;
}

void CerrarConexion(SerialPort * PuertoSerie)
{
    if (PuertoSerie->connected)
	{
        PuertoSerie->connected = 0;
        CloseHandle(PuertoSerie->handler);
    }
}

int readSerialPort(SerialPort * PuertoSerie,char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status);

    if (PuertoSerie->status.cbInQue > 0)
	{
        if (PuertoSerie->status.cbInQue > buf_size)
		{
            toRead = buf_size;
        }
        else toRead = PuertoSerie->status.cbInQue;
    }

    memset(buffer, 0, buf_size);

    if (ReadFile(PuertoSerie->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

    return 0;
}

int writeSerialPort(SerialPort *PuertoSerie,char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(PuertoSerie->handler, (void*) buffer, buf_size, &bytesSend, 0))
	{
        ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status);
        return 0;
    }
    else return 1;
}

int isConnected(SerialPort *PuertoSerie)
{
    if (!ClearCommError(PuertoSerie->handler, &PuertoSerie->errors, &PuertoSerie->status))
		PuertoSerie->connected = 0;
    return PuertoSerie->connected;
}'
