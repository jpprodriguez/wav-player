/*
 * AppFunctions.h
 *
 *  Created on: 16/12/2013
 *      Author: elchurrito
 */

#ifndef APPFUNCTIONS_H_
#define APPFUNCTIONS_H_

#include "diskio.h"
#include "ff.h"
#include "KitInfo2.h"


//Destino de canciones
#define SONGS_DIR "0:/Musica"

//Teclas 4x1
#define KEY_1		1

#define KEY_2		2

#define KEY_3		3

#define KEY_4		4

//Teclas EXP3
#define EXP3_KEY1		5

#define EXP3_KEY2		6

#define EXP3_KEY3		7

#define EXP3_KEY4		8

#define EXP3_KEY5		9

#define EXP3_KEY6		10

#define EXP3_KEY7		11

#define EXP3_KEY8		12



//Estados
#define FRAME_START		0

#define INCOMING_DATA	1

#define FRAME_END		2

//Caracteres de inicio y fin de trama
#define FRAME_START_CHAR '<'

#define FRAME_END_CHAR '>'

//SDLIST tipos
#define NOMBRE			0

#define AUTOR			1

#define DURACION		2

#define STOP_CHECKING G_cmd[0]='\0'

//defines de MaqEstadoDMA()
#define BUFFER1 1
#define BUFFER2 2
#define TRANSFER_READY 0
#define TRANSFER_IN_PROGRESS 1
#define NO_DATA 2

//Estados de G_estado_cancion
#define REPRODUCIENDO 1
#define PAUSADA 2
#define SIN_CANCION 3

//Estados de G_modo
#define PLACA	0
#define PC		1

//Estructura Wav_Chunk para los metadatos
typedef struct{
	char ChunkID[4];
	unsigned int ChunkSize; ;
	char ChunkFormat[4];
	char SubChunk1ID[4];
	unsigned int SubChunk1Size;
	unsigned short int AudioFormat;
	unsigned short int NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	unsigned short int BlockAlign;
	unsigned short int BitsPerSample;
	char SubChunk2ID[4];
	unsigned int SubChunk2Size;
}Wav_Chunk;


extern uint8_t G_modo;
extern volatile int G_Timer_Buzzer;


/*Prototipo de funciones */
void InitApp();

void InitSDSongList();

Wav_Chunk GetSongInfo(char* Song_Name);

uint32_t GetFileQuantity(char* path);

void LoadSDInfo();

void GetSongNumber();

void UARTRx(void);

void CheckCommand();

void RutinaSDList();

void PlaySong(int song_code);

void StopSong();

void DisplayLCDCurrSong();

void PauseSong();

void ResumeSong();

void ReproducirSonido();

void FuncKey(uint8_t);

void PlayPrevSong();

void PlayNextSong();

uint8_t SDtoBuffer(FIL* fp,unsigned int* buffer);

void MaqEstadoDMA();

void CerrarCancion(FIL* fp);

void CheckSD();

void AbrirCancion(char*nombre);

void CheckPcConnection();

void PitidoBuzzer(int mseg);

void CheckEndOfSong();


#endif /* APPFUNCTIONS_H_ */
