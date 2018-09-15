/*
 * AppFunctions.c
 *
 *  Created on: 16/12/2013
 *      Author: elchurrito
 */

/**
 * \file AppFunctions.c
 * \brief Funciones de la aplicacion
 * \details Archivo que contiene las funciones incluidas dentro de la capa de aplicacion
 */

#include "AppFunctions.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "KitInfo2_Expansiones.h"
#include "KitInic_Expansiones.h"
#include "FW_Timer1.h"
#include "FW_DAC.h"
#include "FW_DMA.h"
#include "PR_Teclado.h"
#include "PR_LCD.h"
#include "PR_UART1_RS232.h"
#include "PR_Display7Seg.h"


//La G_ es por ser variables globales

unsigned int G_buffer1_DMA[1024]; //!< Buffer donde se guardan datos de un archivo de la SD para luego ser enviado por el DMA al dac

unsigned int G_buffer2_DMA[1024]; //!< Buffer donde se guardan datos de un archivo de la SD para luego ser enviado por el DMA al dac

volatile int G_Timer_Buzzer=0; //!< Timer del buzzer utilizado en la funcion PitidoBuzzer()

extern volatile uint32_t Delay_LCD; //Esta en FW_Timertick.c

uint8_t G_start_transfer=0; //!< Flag para iniciar la transferencia utilizado en MaqEstadoDMA()

uint8_t G_estado_DMA=NO_DATA; //!< Estado de la maquina de estados MaqEstadoDMA()

FIL G_fp; //!< Variable donde se guarda la informacion del archivo que se abra

char G_nombres_archivos[100][60]={{0}}; //!< Matriz donde se guardan los nombres de las canciones en la SD

char** G_songs_titles; //!< Matriz donde se guardan los titulos de las canciones

char** G_songs_authors; //!< Matriz donde se guardan los autores de las canciones

char **G_songs_durations; //!< Matriz donde se guardan la duracion en segundos de las canciones

uint32_t G_songs_number; //!< Cantidad de canciones encontradas en la SD

FATFS G_fatfs; //!< Variable donde se guarda la informacion de la SD montada

char G_cmd[7]; //!< Comando recibido por UART

int G_song_code=0; //!< Codigo de la cancion.Cada cancion tiene un codigo que corresponde a la posicion que tenga en G_nombres_archivos

uint8_t G_estado_cancion=SIN_CANCION; //!< Indica el estado actual de la cancion (reproduciendose,pausada,etc)

uint8_t G_modo=PLACA; //!< Indica el modo en el que esta el reproductor.Puede ser PLACA o PC

uint8_t vol=90;


/*********************************************************************//**
 * @brief		Maquina de Estado del Canal 0 el DMA
 * @details 	Dependiendo del estado,la maquina inicia el canal del DMA o transfiere datos del archivo al buffer, y cuando se trasnfirieron
 * 				todos los datos del buffer al DAC (por medio del DMA) vuelve al estado inicial y comienza el proceso devuelta.
 **********************************************************************/
void MaqEstadoDMA(){

 		switch(G_estado_DMA)
 		{
 		static uint8_t buffer_activo=BUFFER1;

 		static uint8_t buffer1_empty=1;

 		static uint8_t buffer2_empty=1;


 		case TRANSFER_READY:

 			if(buffer_activo==BUFFER1)

 				DMAChannelInit(G_buffer1_DMA); //Inicia Canal 0 DMA con direccion de origen de datos G_buffer1_DMA

 			else

 				DMAChannelInit(G_buffer2_DMA); //Inicia Canal 0 DMA con direccion de origen de datos G_buffer2_DMA


 			G_estado_DMA= TRANSFER_IN_PROGRESS;


 			break;


 		case TRANSFER_IN_PROGRESS:


 			if(buffer_activo==BUFFER1){

 				if(buffer2_empty==1)	//Mientras se envia por el DMA el buffer1 se va cargando el buffer2
 				{
 					if(!SDtoBuffer(&G_fp,G_buffer2_DMA))

					 	buffer2_empty=0;
 				}
 			}
 			else
 			{
 				if(buffer1_empty==1)	//Mientras se envia por el DMA el buffer2 se va cargando el buffer1
 					{

 					if(!SDtoBuffer(&G_fp,G_buffer1_DMA))

 					 	buffer1_empty=0;
 					 }
 			}
			if(G_dma_transfer_done)
			{
				if(buffer_activo==BUFFER1)
				{
					buffer1_empty=1;

					buffer_activo=BUFFER2;

				}else
				{
					buffer2_empty=1;

					buffer_activo=BUFFER1;
				}

				G_dma_transfer_done=0;


				if(buffer1_empty && buffer2_empty) //Si no hay mas datos en los buffers no hay mas nada que enviar

					G_estado_DMA=NO_DATA;

				else

					G_estado_DMA=TRANSFER_READY;
			}


 			break;

 		case NO_DATA:

 			if(G_start_transfer)
 			{

 			SDtoBuffer(&G_fp,G_buffer1_DMA); //Se carga el primer buffer para que ya empiece a enviar datos

 			G_start_transfer=0;

 			G_estado_DMA=TRANSFER_READY;
 			}

 			break;

 			}
}

/*********************************************************************//**
 * @brief		Copia 1024 bytes de un archivo a un buffer.
 * @param		G_fp	Puntero al fichero del que se leen los datos
 * @param		buffer	Puntero al buffer donde se guardan los datos
 * @return		0 si se leyeron 1024 bytes y 1 si se leyeron menos de 1024 bytes
 ***********************************************************************/

uint8_t SDtoBuffer(FIL* G_fp,unsigned int* buffer)
{
	unsigned char buffer_crudo[1024]={0};

	uint32_t i;

	uint32_t bytes;

	f_read(G_fp,buffer_crudo,1024,(UINT*)(&bytes)); //Se leen 1024 bytes del fichero fp y se guardan en buffer_crudo


	 		if(bytes<1024)
	 		{

	 		f_close(G_fp);

	 		StopDMA();

	 		return 1;

	 		}
	 		else{


	 	 	for(i=0;i<1024;i++)
	 	 	{
	 	 		if(((int)(buffer_crudo[i] * vol))/100 <=255) //Si el dato no se pasa del maximo de un uchar al subir el volumen

	 	 			 buffer_crudo[i]=((int)(buffer_crudo[i] * vol))/100; //Ajusto el volumen del dato a salir

	 	 		else
	 	 			 buffer_crudo[i]=255; //como me pase del maximo y pegue la vuelta,lo dejo en el maximo

	 	 		//Se transforma el dato para que pueda ser enviado por el dac(primeros 6 bits reservados y DAC_BIAS=1)
	 	 		buffer[i]=((buffer_crudo[i] << 6 ) | (1<<16));
	 	 	}


	 	 	return 0;
	 		}
}

/*********************************************************************//**
 * @brief		Guarda en la variable global G_songs_number la cantidad de archivos en la tarjeta SD
 ***********************************************************************/
void GetSongNumber()
{
	G_songs_number=GetFileQuantity(SONGS_DIR);
}

/*********************************************************************//**
 * @brief		Inicializa perifericos,teclado,LCD,Display y la SD card
 ***********************************************************************/
void InitApp()
{

		InicializarKit();

		SetPIN(BUZZ,OFF);

		InitEXP();

		InitSDSongList();

}

/*********************************************************************//**
 * @brief		Inicializa tarjeta SD y carga en los vectores G_songs_titles,G_songs_authors
 * 				y G_songs_durations la informacion de las canciones
 ***********************************************************************/
void InitSDSongList()
{


	int i;

 	if(!disk_initialize(0)) //Inicializa la SD
 	{

	if(f_mount(0, &G_fatfs)==FR_OK) //Monta la SD con el formato fatfs
	{
		GetSongNumber();	//Obtiene cantidad de canciones


		//Inicializo las matrices que contienen la informacion de las canciones

		G_songs_titles=(char**)malloc((G_songs_number)*sizeof(char*));

		G_songs_authors=(char**)malloc((G_songs_number)*sizeof(char*));

		G_songs_durations=(char**)malloc((G_songs_number)*sizeof(char*));

		for(i=0;i<G_songs_number;i++)
		{
			G_songs_titles[i]=(char*)malloc(40);

			G_songs_authors[i]=(char*)malloc(40);

			G_songs_durations[i]=(char*)malloc(4);
		}

		LoadSDInfo(); //Cargo en las matrices inicializadas la informacion de la SD


	}
 	}

}

/*********************************************************************//**
 * @brief		Averigua la cantidad de archivos encontrados en la carpeta path de la SD
 * @param		path	Direccion de la carpeta ubicada en la carpeta SD
 * @return		Entero que representa la cantidad de archivos encontrados en path
 ***********************************************************************/
uint32_t GetFileQuantity (char* path)
{
    FRESULT res;

    FILINFO fno;

    DIR dir;

    int nro=0;


    char lfn[_MAX_LFN + 1];   //Buffer donde se guarda el lfn(Long file name)

    fno.lfname = lfn;

    fno.lfsize = sizeof lfn;


    res = f_opendir(&dir, path);                       //Abre el directorio de ruta "path"

    if (res == FR_OK)	{

        for (;;){

            res = f_readdir(&dir, &fno);                   //Lee un elemento del directorio

            if (res != FR_OK || fno.fname[0] == 0) break;  // Si hay un error o si no hay mas elementos sale del for

            if (fno.fname[0] == '.') continue;             //Si un elemento tiene como nombre . lo ignora

            if (!(fno.fattrib & AM_DIR))                     //No es un directorio,entonces es un archivo

            	nro++;

        		}

    					}

    return nro;
}

/*********************************************************************//**
 * @brief		Obtiene los metadatos de la cancion dada como parametro y los devuelve
 * @param		Song_name	Puntero al string que contiene el nombre de una cancion
 * @return		Estructura Wav_chunk que contiene los metadatos de la cancion
 ***********************************************************************/
Wav_Chunk GetSongInfo(char* Song_Name)
{


	char* path;

	uint32_t bytes;

	Wav_Chunk Song_Info;


	path=(char*)malloc(15+strlen(Song_Name));

	//Armo el path completo de la cancion (0:/Musica/Nombrecancion.wav)

	strcpy(path,"0:/Musica/");

	strcat(path,Song_Name);

	strcat(path,".wav");


	if(f_open(&G_fp,path,FA_OPEN_EXISTING | FA_READ) == FR_OK) //Si existe el archivo lo abro para leer
	{
		f_read(&G_fp,&Song_Info,sizeof(Song_Info),(UINT*)(&bytes)); //Guardo los primeros 44 bytes(metadatos) de la cancion en Song_Info

		f_close(&G_fp);
	}



	free(path);

	return Song_Info;
}

/*********************************************************************//**
 * @brief		Carga en G_songs_titles,G_songs_authors y G_songs_durations la informacion de las canciones
 ***********************************************************************/
void LoadSDInfo()
{

	    FRESULT res;

	    FILINFO fno;

	    DIR dir;

	    uint32_t i,j=0,t=0,c=0,song_length;

	    char song_length_string[5];

	    char *fn;

	    char **aux;

	    Wav_Chunk Song_Info;

	    //Inicializo matriz aux
	    aux=(char**)malloc(G_songs_number*sizeof(char*));

	    for(i=0;i<G_songs_number;i++)

	    	aux[i]=(char*)malloc(40);


	    char lfn[_MAX_LFN + 1];   //Buffer donde se guarda el lfn(Long file name)

	    fno.lfname = lfn;

	    fno.lfsize = sizeof lfn;


	    res = f_opendir(&dir,SONGS_DIR);                       //Abre el directorio de ruta SONGS_DIR

	    if (res == FR_OK)
	    {
	        i = strlen(SONGS_DIR);

	        for (;;)
	        {
	            res = f_readdir(&dir, &fno);                   //Lee un elemento del directorio

	            if (res != FR_OK || fno.fname[0] == 0) break;  // Si hay un error o si no hay mas elementos sale del for

	            if (fno.fname[0] == '.') continue;             //Si un elemento tiene como nombre "." lo ignora


	            fn = *fno.lfname ? fno.lfname : fno.fname;

	            if (!(fno.fattrib & AM_DIR))					//No es un directorio,entonces es un archivo
	            {

	            	strcpy(aux[j],fn); //Guardo en la posicion j de aux el nombre del archivo

	            	strcpy(G_nombres_archivos[j],aux[j]);

	            	aux[j][strlen(fn)-4]='\0'; //Saco el ".wav" de aux

	            	Song_Info=GetSongInfo(aux[j]); //Guardo en Song_Info los metadatos de la cancion cuyo nombre esta en aux[j]

	            	//La longitud en segundos de una cancion se calcula diviendo la cantidad de bytes de la misma(SubChunk2Size)or el ByteRate
	            	song_length=Song_Info.SubChunk2Size / Song_Info.ByteRate;

	            	sprintf(song_length_string,"%d",song_length); //Transformo el entero song_length a un string

	            	strcpy(G_songs_durations[j],song_length_string);

	            	j++;


	            }
	        }

	   /*Separo la informacion de aux en G_songs_authors y G_songs_titles. El caracter "-" es el que separa.
	    * Ejemplo:	aux[0][]= "Autor - Nombre de cancion" => G_songs_authors[0][]="Autor" y G_songs_titles[0][]="Nombre de cancion"
	    */
	        for(i=0;i<j;i++)
	        {
	        	t=0;

	        	c=0;

	        	while(aux[i][t]!='-')
	        	{
	        			G_songs_authors[i][t]=aux[i][t];

	        			t++;
	        	}

	        	G_songs_authors[i][t-1]='\0';

	        	t+=2;

	        	while(aux[i][t]!='\0')
	        	{
	        		   G_songs_titles[i][c]=aux[i][t];

	        		   c++;

	        		   t++;
	        	}

	        	 G_songs_titles[i][c]='\0';
	        }

	    }

}

/*********************************************************************//**
 * @brief		Maquina de estado que maneja los datos recibidos de la UART
 * @details		Analiza los bytes recibidos por la UART.Si se valida la trama(<6caracteres>) se guardan los 6 caracteres en G_cmd.
 ***********************************************************************/
void UARTRx(void)
{
	static uint8_t estado = FRAME_START, ctr = 0;

	static char buffer[7];

	uint8_t byte;

	if(!PopRx(&byte))
	{
		switch(estado)
		{
			case FRAME_START:

				if(byte == FRAME_START_CHAR) //Cuando llega el caracter del inicio de trama,empieza a guardar los proximos 6 bytes que llegan

					estado = INCOMING_DATA;

				break;

			case INCOMING_DATA:

				if(ctr == 5)
				{
					buffer[5] = byte;

					buffer[6] = '\0';

					ctr = 0;

					estado = FRAME_END;
				}
				else
				{
					buffer[ctr] = byte;

					ctr++;
				}

				break;

			case FRAME_END:

				if(byte == FRAME_END_CHAR)	//Cuando llega el caracter de fin de trama se guarda lo recibido en la variable G_cmd
				{

					strcpy(G_cmd,buffer);

				}

				estado = FRAME_START;

				break;
		}
	}
}

/*********************************************************************//**
 * @brief Analiza G_cmd, y si es un comando valido realiza la accion correspondiente.
 ***********************************************************************/
void CheckCommand()
{


	if(strstr(G_cmd,"PLA")) //PLA009 PLA de Play y los ultimos 3 digitos representan el codigo de la cancion
	{
		/*Copio el numero de cancion que esta en G_cmd en aux*/

		char aux[4];

		aux[0]=G_cmd[3];

		aux[1]=G_cmd[4];

		aux[2]=G_cmd[5];

		aux[3]='\0';

		G_song_code=atoi(aux); //Guardo en G_song_code el string del codigo de la cancion convertido a entero

		StopSong(); //Freno la cancion si es que habia alguna reproduciendose

		PlaySong(G_song_code); //Reproduzco la cancion que tenga el codigo recibido


		STOP_CHECKING;

	}

//Si el comando arranca con "t=" lo que sigue es un numero de 4 digitos que representa el tiempo actual en segundos de la cancion en curso
//Se utiliza este comando para sincronizar el tiempo de la cancion en la placa con el tiempo en la PC
	else if(strstr(G_cmd,"t="))
	{
		char aux[5];

		aux[0]=G_cmd[2];

		aux[1]=G_cmd[3];

		aux[2]=G_cmd[4];

		aux[3]=G_cmd[5];

		aux[4]='\0';

		G_tiempo_actual=atoi(aux);

		//se multiplica el tiempo por 8000 porque cada segundo representa 8000 bytes(8khz y bit rate 8)
		//Luego se suma 44 bytes para saltear los metadatos
		f_lseek(&G_fp,(G_tiempo_actual*8000)+44);

		STOP_CHECKING;
	}
	else if(strstr(G_cmd,"VOL"))
		{
			char aux[4];

				aux[0]=G_cmd[3];

				aux[1]=G_cmd[4];

				aux[2]=G_cmd[5];

				aux[3]='\0';

				vol=atoi(aux);

				STOP_CHECKING;
		}
	else if(!strcmp(G_cmd,"PAUSAR"))
	{
		PauseSong();

		STOP_CHECKING;


	}else if(!strcmp(G_cmd,"RESUME"))
	{
		ResumeSong();

		STOP_CHECKING;

	}
		else if(!strcmp(G_cmd,"STOP00")){

		StopSong();

		STOP_CHECKING;


		}
		else if(!strcmp(G_cmd,"SDLIST")) //Con el comando "SDLIST" la PC le pide al micro que le envie los datos de la SD
		{
			RutinaSDList();
			STOP_CHECKING;

		}
		return;

	}

/*********************************************************************//**
 * @brief	Envia por la uart la informacion de las canciones de la SD en una trama que inicia con @$ y termina con $@
 ***********************************************************************/
void RutinaSDList(){

	uint8_t ctr=G_songs_number+1;

	uint32_t tipo=AUTOR;

	EnviarString ("@$"); //Inicio de trama del envio de la informacion de la SD

	//Envia la informacion de la forma /Autor1/Titulo1/Duracion1|/Autor2/Titulo2/Duracion2|...

	while(ctr!=0 || tipo!=DURACION)//Cuando el contador llega a 0 y el tipo es DURACION termina el ciclo while
	{
					switch(tipo)
					{
					case AUTOR:

						EnviarString("/");

						EnviarString (G_songs_authors[G_songs_number-ctr-1]);

						tipo=NOMBRE;

						break;

					case NOMBRE:

						EnviarString("/");

						EnviarString (G_songs_titles[G_songs_number-ctr-1]);

						tipo=DURACION;

						break;

					case DURACION:

						EnviarString("/");

						EnviarString (G_songs_durations[G_songs_number-ctr-1]);

						EnviarString("|");

						tipo=AUTOR;

						ctr--;

						break;
					}


		}

		EnviarString("/");

		//envia la duracion de la ultima cancion que no se habia enviado en el ciclo while anterior
		EnviarString (G_songs_durations[G_songs_number-1]);

		EnviarString ("$@"); //Fin de trama del envio de la informacion de la SD

}

/*********************************************************************//**
 * @brief	Muestra en el LCD el titulo y el autor de la cancion actual
 ***********************************************************************/
void DisplayLCDCurrSong()
{

	LimpiarLCD();

	DisplayLCD(G_songs_titles[G_song_code],RENGLON_1); //Muestra el titulo de la cancion en el primer renglon

	Delay_LCD=25;

	while(Delay_LCD); //Deja pasar un pequeño tiempo para que el LCD llegue a escribir el primer renglon antes de empezar a escribir el segundo

	DisplayLCD(G_songs_authors[G_song_code],RENGLON_2);//Muestra el autor de la cancion en el segundo renglon

}

/*********************************************************************//**
 * @brief		Abre una cancion y la adelanta 44 bytes para saltear los metadatos
 * @param		nombre	Puntero al string que contiene el nombre de una cancion
 ***********************************************************************/
void AbrirCancion(char*nombre)
{
	char path[100]="0:/Musica/";

	strcat(path,nombre);

	f_open(&G_fp,path,FA_OPEN_EXISTING | FA_READ); //Abre el archivo de la SD de direccion "path"

	f_lseek(&G_fp,44); //Saltea los primeros 44 bytes que obtienen los metadatos
}

/*********************************************************************//**
 * @brief	Cierra la cancion apuntada por el fichero G_fp
 * @param	G_fp	Puntero a fichero
 ***********************************************************************/


void CerrarCancion(FIL* G_fp)
{
	f_close(G_fp);
}

/*********************************************************************//**
 * @brief	Reproduce la cancion que este ubicada en la posicion "G_song_code" dentro del vector G_nombres_archivos.
 * @param	G_song_code	Entero que representa el codigo de la cancion a reproducir
 ***********************************************************************/


void PlaySong(int G_song_code)
{

	AbrirCancion(G_nombres_archivos[G_song_code]);

	G_start_transfer=1; //Le avisa a MaqEstadoDMA que comience a transmitirle datos al DAC

	G_estado_cancion=REPRODUCIENDO;

	StartTimer1();	//Empieza a contar el tiempo de la cancion

	if(GetPIN(RGBR)==ON)

			SetPIN(RGBR,OFF);

	DisplayLCDCurrSong();



}

/*********************************************************************//**
 * @brief		Detiene la cancion que se este reproduciendo actualmente y retorna el LCD,los leds y el display a su estado inicial
 ***********************************************************************/
void StopSong()
{
	G_estado_DMA=NO_DATA; //Obliga a MaqEstadoDMA a que deje de transmitir datos

	G_start_transfer=0;	//Impide que MaqEstadoDMA vuelva a empezar a enviar datos al DAC

	G_estado_cancion=SIN_CANCION;

	StopTimer1(); //Deja de contar el tiempo de la cancion y vuelve a 0 el display

	CerrarCancion(&G_fp);

	SetPIN(LED1,OFF);

	SetPIN(RGBR,OFF);

	LimpiarLCD();

}

/*********************************************************************//**
 * @brief	Pausa la cancion que se este reproduciendo en ese momento
 ***********************************************************************/
void PauseSong()
{

	if(GetPIN(RGBR)==OFF)

		SetPIN(RGBR,ON);

	G_estado_DMA=NO_DATA; //Obliga a MaqEstadoDMA a que deje de transmitir datos

	G_start_transfer=0;	//Impide que MaqEstadoDMA vuelva a empezar a enviar datos al DAC

	G_estado_cancion=PAUSADA;




}

/*********************************************************************//**
 * @brief	Resume la cancion que se estaba reproduciendo anteriormente
 ***********************************************************************/
void ResumeSong()
{
		SetPIN(RGBR,OFF);

		G_start_transfer=1;	//Empieza a contar el tiempo de la cancion

		G_estado_cancion=REPRODUCIENDO;

		G_estado_DMA=TRANSFER_READY; //Obliga a MaqEstadoDMA a que reanude a mandar datos al DAC

}

/*********************************************************************//**
 * @brief	Reproduce la cancion anterior a la que se encuentra en la posicion G_song_code,si es que hay una.
 ***********************************************************************/
void PlayPrevSong()
{
	if(G_song_code!=0)
	{
		G_song_code--;

		StopSong();

		PlaySong(G_song_code);

	}
}
/*********************************************************************//**
 * @brief	Reproduce la cancion posterior a la que se encuentra en la posicion G_song_code,si es que hay una.
 ***********************************************************************/
void PlayNextSong()
{
	if(G_song_code!=G_songs_number-1)
	{
		G_song_code++;

		StopSong();

		PlaySong(G_song_code);
	}
	else //Si no hay proxima cancion se dejan de reproducir canciones y el codigo de la cancion vuelve a la inicial
	{
		G_song_code=0;

		StopSong();
	}


}

/*********************************************************************//**
 * @brief	Realiza una accion dependediendo del valor de "key"
 * @param	key	char que contiene a la tecla pulsada
 ***********************************************************************/
void FuncKey(uint8_t key)
{

	switch(key)
			{

			case EXP3_KEY1: //La misma tecla reproduce,pausa o reanuda una cancion dependiendo del estado de G_estado_cancion

				switch(G_estado_cancion)
				{
				case SIN_CANCION:

					PlaySong(G_song_code);

					break;

				case PAUSADA:

					ResumeSong();

					break;

				case REPRODUCIENDO:

					PauseSong();

					break;
				}

			break;

			case EXP3_KEY2:

				PlayPrevSong();

				break;

			case EXP3_KEY5:

				StopSong();

				break;

			case EXP3_KEY6:


				PlayNextSong();

				break;

			case EXP3_KEY3:
				//Retrasa la cancion 5 segundos,si es que la cancion tiene mas de 5 segundos reproducidos

				if(((int)G_tiempo_actual-5) > 0)//si el tiempo actual de la cancion supera los 5 segundos

					f_lseek(&G_fp,f_tell(&G_fp)-(5*8000));//Retrasa la cancion 5 segundos que equivalen a (5*8000) bytes

				break;

			case EXP3_KEY7:

				//Adelanta la cancion 5 segundos,si es que la cancion tiene mas de 5 segundos por ser reproducidos
				if(((int)G_tiempo_actual+5) < atoi(G_songs_durations[G_song_code])) //si (tiempo actual+5) no supera el tiempo total de la cancion

					f_lseek(&G_fp,f_tell(&G_fp)+(5*8000));//Adelanta la cancion 5 segundos que equivalen a (5*8000) bytes

				break;


			case EXP3_KEY8:

					if(vol<180)
						vol+=20;

					break;


			case EXP3_KEY4:

					if(vol>20)
						vol-=20;
					else
						vol=0;

					break;
			}

}

/*********************************************************************//**
 * @brief	Cambia el valor de "G_modo" a "PC" o a "PLACA" dependiendo de si se conecto o desconecto la PC
 ***********************************************************************/
void CheckPcConnection()
{
	if(G_Timer_Rx && G_modo!=PC)
	{
		G_modo=PC;

		PitidoBuzzer(250);
	}
	else if(G_Timer_Rx==0 && G_modo!=PLACA)
	{
		G_modo=PLACA;

		PitidoBuzzer(250);
	}
}

/*********************************************************************//**
 * @brief		Emite un pitido en el buzzer que dura "mseg" milisegundos
 * @param		mseg	Tiempo en milisegundos
 ***********************************************************************/
void PitidoBuzzer(int mseg)
{
	SetPIN(BUZZ,BUZZ_OFF);

	//Se suma 1 porque G_Timer_Buzzer se va decrementando y el systick apaga el buzzer cuando G_Timer_Buzzer llega a 0
	G_Timer_Buzzer=((mseg*400)/1000)+1;

}

/*********************************************************************//**
 * @brief	Chequea que la SD este en la ranura. Si no esta,se emite un mensaje de error
 * y se detiene el programa hasta que se lo resetee manualmente
 ***********************************************************************/
void CheckSD()
{
	BYTE ptr[5];

	/*Envia a la SD el comando para obtener el OCR(Operating Conditions Register) y la SD responde al comando enviando el OCR.
	  El OCR en si no se usa para nada en este caso,es solo para corroborar que haya una conexion entre la placa y la SD*/

	if(disk_ioctl (0,MMC_GET_OCR,ptr)!=RES_OK) //si lo que devuelve no es RES_OK(0),la SD no contesta,por ende,no esta conectada
		{
		/* Reseteo*/
		StopSong();

		G_song_code=0;

		G_tiempo_actual=0;

		DisplayTime(G_tiempo_actual);

		DisplayLCD("NO HAY SDCARD",RENGLON_1);

		DisplayLCD("INGRESE UNA Y RESETEE",RENGLON_2);

		if(G_modo==PC)

			EnviarString("$#RESET");

		while(1);

		}

}

/*********************************************************************//**
 * @brief		Chequea si la cancion llego al final, y si lo hace, reproduce la proxima cancion en la lista
 ***********************************************************************/
void CheckEndOfSong()
{

if(G_tiempo_actual==atoi(G_songs_durations[G_song_code]))

    		PlayNextSong();
}



