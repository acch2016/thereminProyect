/*
 *\file DAC.h
 *\brief	Este es un header para la implementación del modulo DAC que se utiliza
 *				 para el generador de señales.
 * \date 17/9/2016
 * \Author Alejandro Canale
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"


void sine(uint8 FTM0_C0SC_counter, uint8 FTM0_C1SC_counter, uint8 FTM0_C2SC_counter);
//void sin(sint8 FTM0_C0SC_counter);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal senoidal al DAC
 	 	 	 de la K64
 	 \return void
 */
//void sine();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal triangular al DAC
 	 	 	 de la K64
 	 \return void
 */
void tri();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga los datos de un arreglo con los valores de una señal cuadrada al DAC
 	 	 	 de la K64
 	 \return void
 */
void square();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Función que carga datos al DAC de la K64
 	 \return void
 */
void writeDAC(uint16 valor);
sint16 adding_sines(sint8 ftm0ch0, sint8 ftm0ch1, sint8 ftm0ch2, sint8 ftm0ch3, sint8 ftm0ch4, sint8 ftm0ch5, sint8 ftm0ch6, sint8 ftm0ch7,sint8 ftm3ch0, sint8 ftm3ch1, sint8 ftm3ch2, sint8 ftm3ch3, sint8 ftm3ch4, sint8 ftm3ch5, sint8 ftm3ch6, sint8 ftm3ch7);
//

#endif /* SOURCES_DAC_H_ */
