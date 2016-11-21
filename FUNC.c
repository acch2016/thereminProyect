/*
 * \file FUNC.c
 * \brief Archivo fuente para el generador de se�ales, en este archivo utilziamos una m�quina de
 * 				estados de listas enlazadas para elegir que seal deseamos reproducir
 *
 * \date 17/9/2016
 * \author Alejandro Canale
 */
/** Archivos que contienen los tipos de datos y nombres de registros*/
#include "DataTypeDefinitions.h"
#include "MK64F12.h"

#include "FUNC.h"

/**Archivos que contienen funciones necesarias para el generador de se�ales*/
#include "DAC.h"
/**Archivo que contiene funciones para el manejo de registros*/
#include "GPIO.h"
/**Archivo que contiene funciones para el manejo de interrupciones*/

/** Definiciones para el control de los LEDs*/
#define SIGNAL_LED_1 24
#define SIGNAL_LED_2 25

/** Definiciones para cada uno de los estados de la m�quina, estas definiciones corresponden a espacios
 *  de memoria
 */
#define SQUARE &FineStateMachineMoore_Wave[0]
#define SINE &FineStateMachineMoore_Wave[1]
#define TRIANGLE &FineStateMachineMoore_Wave[2]
#define ZERO &FineStateMachineMoore_Wave[3]

/** Estructura para construir cada uno de los estados, est� contiene un apuntador  funci�n y
 * apuntadores para las transciciones a los siguiente estados*/
typedef const struct State
{
	void (*ftprSig)();
	const struct State* next[2];
}StateType;

/** Declaraci�n de la m�quina de estados*/
const StateType FineStateMachineMoore_Wave[4]=
{
		{square_1,  {SQUARE,  SINE}},
		{sine_2,    {SINE,    TRIANGLE}},
		{triangle_3,{TRIANGLE,ZERO}},
		{zero_4,    {ZERO,    SQUARE}}
};

/**Declaraci�n del estado inicial*/
StateType * currentState_Wave = ZERO;

/**Declaraci�n para el control de transcici�n dentro de la m�quina de estados*/
static uint8 input=0;
static uint8 currentState_flag=0;


void FSM_signals(uint8 flag_enable) /** Funci�n para llamar la m�quina de estados*/
{
	/**Se limpia la bandera para ir al siguiente estado*/
	currentState_flag = 0;
	/**Se manda a llamar a la funci�n dentro del estado*/
	currentState_Wave->ftprSig();

	/**Si la bandera de activaci�n y el bot�n est�n encendidos se aumenta la bandera del siguiente estado*/
	input = readFlag_PORTA();
	if(TRUE == flag_enable){
	if (TRUE == input) {
		currentState_flag++;
		clearFlag_PORTA();
	}
}
	/**Se actualiza el siguiente estado*/
	currentState_Wave = currentState_Wave->next[currentState_flag];
}

void square_1()		/**Funci�n para prender los leds del estado y mandar
						a llamar la funci�n para la se�al cuadrada*/
{
	GPIO_setPIN(GPIOE, SIGNAL_LED_1);		/** Apagar LED 1 (PTE24)*/
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2);		/** Encender LED 2(PTE25)*/

   square();								/**Llamar a la funci�n para cargar el valor de la se�al cuadrada*/
}
void sine_2()		/**Funci�n para prender los leds del estado y mandar
						a llamar la funci�n para la se�al senoidal*/
{

	GPIO_clearPIN(GPIOE, SIGNAL_LED_1);		/** Encender LED 1 (PTE24)*/
	GPIO_setPIN(GPIOE, SIGNAL_LED_2);		/** Apagar LED 2 (PTE25)*/

	sine();									/**Llamar a la funci�n para cargar el valor de la se�al senoidal*/
}

void triangle_3()	/**Funci�n para prender los leds del estado y mandar
						a llamar la funci�n para la se�al triangular*/
{
	GPIO_clearPIN(GPIOE, SIGNAL_LED_1);		/** Encender LED 1 (PTE24)*/
	GPIO_clearPIN(GPIOE, SIGNAL_LED_2);		/** Encender LED 2 (PTE25)*/
    tri();									/**Llamar a la funci�n para cargar el valor de la se�al triangular*/
}





