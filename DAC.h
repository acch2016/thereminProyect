/*
 *\file DAC.h
 *\brief	Este es un header para la implementaci�n del modulo DAC que se utiliza
 *				 para el generador de se�ales.
 * \date 17/9/2016
 * \Author Alejandro Canale
 */

#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funci�n que carga los datos de un arreglo con los valores de una se�al senoidal al DAC
 	 	 	 de la K64
 	 \return void
 */
void sine();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funci�n que carga los datos de un arreglo con los valores de una se�al triangular al DAC
 	 	 	 de la K64
 	 \return void
 */
void tri();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funci�n que carga los datos de un arreglo con los valores de una se�al cuadrada al DAC
 	 	 	 de la K64
 	 \return void
 */
void square();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funci�n que carga datos al DAC de la K64
 	 \return void
 */
void writeDAC(uint8 valor);

#endif /* SOURCES_DAC_H_ */
