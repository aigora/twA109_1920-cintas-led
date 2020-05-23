#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"
#define MAX_DATA_LENGTH 255

void Crear_Conexion(SerialPort *PuertoSerie,char *portName);
void CerrarConexion(SerialPort *PueroSerie);
int readSerialPort(SerialPort * PuertoSerie,char *, unsigned int buf_size);
int writeSerialPort(SerialPort *PuertoSerie,char *, unsigned int buf_size);
int isConnected(SerialPort *PuertoSerie);
void autoConnect(SerialPort arduino,char);
void anotar(SerialPort *arduino,char *incomingData,int);
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

    while (!isConnected(arduino))
    {
      Sleep(100);
      Crear_Conexion(arduino,arduino->portName);
    }
 //Comprueba si arduino est� connectado
    if (isConnected(arduino))
    {
      printf ("Conectado con Arduino en el puerto %s\n",arduino->portName);
    }
 // Bucle de la aplicaci�n
    while (isConnected(arduino))
    {
      readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);
      if (readResult!=0){
      	  	    printf("Ya tenemos al ganador de la partida %d\n", i);
      	  	    printf("El ganador es el jugador: %s\n", incomingData);
      	  	    anotar(arduino,incomingData,i);
      	  	    i++;
			}
			 Sleep(10);
	}
    
    if (!isConnected(arduino))
       printf ("Se ha perdido la conexi�n con Arduino\n");
}

void anotar(SerialPort *arduino,char *incomingData,int i){
	
	FILE *fichero;
	int readResult;
   	int cv1=0,cd1=0,cv2=0,cd2=0;
	
	fichero = fopen ("Resultados.txt","a+");
	
	readResult = readSerialPort(arduino,incomingData,MAX_DATA_LENGTH);

		if(fichero == NULL){ 
        	printf("Error al abrir el fichero\n");
		}else{
			if(strcmp(incomingData , "1")){
			fprintf(fichero, "Partida %d: Equipo 1 +3puntos\n           Equipo 2 +1punto\n", i);
			cv1++;
			cd2++;
			}
			else{
				if(strcmp(incomingData , "2")){
				fprintf(fichero, "Partida %d: Equipo 2 +3puntos\n           Equipo 1 +1punto\n", i);
				cv2++;
				cd1++;
			}
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
}
