/*
 * 	DAC.c
 *	Descripción: Este es un archivo fuente para el control del convertidor digitl analógico
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
/** Tamaño del arreglo que utilizamos para cargar valores en el DAC*/
#define CIEN_VALORES 100


/** Valores para la senal senoidal */
static uint8 y_values_for_sine[] = {0,8,16,24,32,40,47,55,62,69,75,82,88,
		93,99,103,108,112,116,119,121,123,125,126,127,127,
		127,126,124,122,120,117,114,110,106,101,96,91,85,
		79,72,65,58,51,43,36,28,20,12,4,-4,-12,
		-20,-28,-36,-43,-51,-58,-65,-72,-79,-85,-91,-96,-101,
		-106,-110,-114,-117,-120,-122,-124,-126,-127,-127,-127,-126,-125,
		-123,-121,-119,-116,-112,-108,-103,-99,-93,-88,-82,-75,-69,
		-62,-55,-47,-40,-32,-24,-16,-8,0 };


void sine()/**Función para generar una señal senoidal utilizando el DAC de la K64,
			está función utiliza un arreglo de valores que carga continuamente al DAC*/
{
	static uint8 sine_value=0;					/**Variable de control para cambiar los valores en el arreglo*/

	if(CIEN_VALORES==sine_value){				/**Condición para regresar al inicio del arreglo cuando ya se leyeron todos
													Todos los valores*/
		sine_value=0;
	}
	writeDAC(y_values_for_sine[sine_value]);	/**Función para cargar el valor actual al DAC*/
	sine_value++;
};


void writeDAC(uint8 valor)/** Función utilizada en las anteriores funciones para cargar valores en el DAC*/
{
	DAC0_DAT0L=valor;		/**Registro de la parte baja del DAC*/
	DAC0_DAT0H=0;			/**Registro de la parte alta del DAC*/
};
