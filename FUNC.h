/*
 *\filde FUNC.h
 *\brief Archivo header del generador de se�ales, esta es una m�quina de estados que
 *	utiliza el m�dulo DAC para generar las se�ales
 *\date 17/9/2016
 *\author: Alejandro Canale
 */

#ifndef SOURCES_FUNC_H_
#define SOURCES_FUNC_H_

/** Archivos que contienen variables y nombres de registros*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"




/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funci�n para la maquina de estados del generador de se�ales

 	 \param[uint8]  Este par�metro se utiliza para activar el switch
 	 \return void
 */
void FSM_signals(uint8 flag_enable);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion del estado que activa la onda cuadrada
 	 \return void
 */
void square_1();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion del estado que activa la onda senoidal
 	 \return void
 */
void sine_2();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion del estado que activa la onda triangular
 	 \return void
 */
void triangle_3();


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	Funcion que desactiva el generador de se�ales
 	 \return void
 */
void zero_4();

#endif /* SOURCES_FUNC_H_ */
