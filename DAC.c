/*
 * 	DAC.c
 *	Descripci�n: Este es un archivo fuente para el control del convertidor digitl anal�gico
 *				 Este contiene funciones para generar ondas cuadradas, senoidales y triangulares
 *				 a partir de este modulo de la kinetis
 *  Created on: 17/9/2016
 *  Author: Alejandro Canale
/**



/**Archivos incluididos para */
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
/**Header de este archivo*/
#include "DAC.h"
#include "FlexTimer.h"
/** Tama�o del arreglo que utilizamos para cargar valores en el DAC*/
#define CIEN_VALORES 100


/** Valores para la senal senoidal */
static sint8 y_values_for_sine[] = {0,8,16,24,32,40,47,55,62,69,75,82,88,
		93,99,103,108,112,116,119,121,123,125,126,127,127,
		127,126,124,122,120,117,114,110,106,101,96,91,85,
		79,72,65,58,51,43,36,28,20,12,4,-4,-12,
		-20,-28,-36,-43,-51,-58,-65,-72,-79,-85,-91,-96,-101,
		-106,-110,-114,-117,-120,-122,-124,-126,-127,-127,-127,-126,-125,
		-123,-121,-119,-116,-112,-108,-103,-99,-93,-88,-82,-75,-69,
		-62,-55,-47,-40,-32,-24,-16,-8,0 };


//void sine()/**Funci�n para generar una se�al senoidal utilizando el DAC de la K64,
//			est� funci�n utiliza un arreglo de valores que carga continuamente al DAC*/
//{
//	static uint8 sine_value=0;					/**Variable de control para cambiar los valores en el arreglo*/
//
//	if(CIEN_VALORES==sine_value){				/**Condici�n para regresar al inicio del arreglo cuando ya se leyeron todos
//													Todos los valores*/
//		sine_value=0;
//	}
//	writeDAC(y_values_for_sine[sine_value]);	/**Funci�n para cargar el valor actual al DAC*/
//	sine_value++;
//};

void sin(uint8 FTM0_C0SC_counter){

	writeDAC(y_values_for_sine[FTM0_C0SC_counter]);	/**Funci�n para cargar el valor actual al DAC*/

};

void writeDAC(sint8 valor)/** Funci�n utilizada en las anteriores funciones para cargar valores en el DAC*/
{
	DAC0_DAT0L = valor;		   /**Registro de la parte baja del DAC*/
	DAC0_DAT0H = valor >> 8;   /**Registro de la parte alta del DAC*/
};



//sint16 adding_sines(sint8 ftm0ch0, sint8 ftm0ch1, sint8 ftm0ch2, sint8 ftm0ch3, sint8 ftm0ch4, sint8 ftm0ch5, sint8 ftm0ch6, sint8 ftm0ch7,sint8 ftm3ch0, sint8 ftm3ch1, sint8 ftm3ch2, sint8 ftm3ch3, sint8 ftm3ch4, sint8 ftm3ch5, sint8 ftm3ch6, sint8 ftm3ch7){
//
//	if (TRUE == flag_startAdding){
//		writeDAC(ftm0ch0+ftm0ch1+ftm0ch2+ftm0ch3+ftm0ch4+ftm0ch5+ftm0ch6+ftm0ch7+ftm3ch0+ftm3ch1+ftm3ch2+ftm3ch3+ftm3ch4+ftm3ch5+ftm3ch6,ftm3ch7);	/**Funci�n para cargar el valor actual al DAC*/
//	}
//}
