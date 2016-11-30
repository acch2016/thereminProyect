/*
 * FREQ_SELECT.c
 *
 *  Created on: 29/11/2016
 *      Author: alejandrocanale
 */



#include "FREQ_SELECT.h"


#define LOWER_LIMIT_RANGE1 0.0
#define UPPER_LIMIT_RANGE1 343.75
#define LOWER_LIMIT_RANGE2 343.76
#define UPPER_LIMIT_RANGE2 590.83
#define LOWER_LIMIT_RANGE3 590.84
#define UPPER_LIMIT_RANGE3 1015.51
#define LOWER_LIMIT_RANGE4 1015.52
#define UPPER_LIMIT_RANGE4 1745.43
#define LOWER_LIMIT_RANGE5 1745.44
#define UPPER_LIMIT_RANGE5 3000.0

#define LOWER_LIMIT_C0V_1 0
#define UPPER_LIMIT_C0V_1 13107
#define LOWER_LIMIT_C0V_2 13108
#define UPPER_LIMIT_C0V_2 26214
#define LOWER_LIMIT_C0V_3 26215
#define UPPER_LIMIT_C0V_3 39321
#define LOWER_LIMIT_C0V_4 39322
#define UPPER_LIMIT_C0V_4 52428
#define LOWER_LIMIT_C0V_5 52429
#define UPPER_LIMIT_C0V_5 65536

#define RANGE1 &FiniteStateMachineMoore[0]
#define RANGE2 &FiniteStateMachineMoore[1]
#define RANGE3 &FiniteStateMachineMoore[2]
#define RANGE4 &FiniteStateMachineMoore[3]
#define RANGE5 &FiniteStateMachineMoore[4]


/** Estructura para construir cada uno de los estados, está contiene un apuntador función y
 * apuntadores para las transciciones a los siguiente estados*/
typedef const struct State
{
	void (*fptrRange)();
	const struct State* next[2];
}StateType;

/** Declaración de la máquina de estados*/
const StateType FiniteStateMachineMoore[5]=
{
		{range1,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range2,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range3,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range4,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
		{range5,    {RANGE1, RANGE2, RANGE3, RANGE4, RANGE5}},
};


/**Declaración del estado inicial*/
StateType * currentState_range = RANGE1;

/**Declaración para el control de transcición dentro de la máquina de estados*/
static uint16 input=0;/**Usamos Uint 16 porque se usará CnV el cual tiene de 0 a 65536*/
static uint8 currentState=0;

void FSMRange(uint8 flag_enable) /** Función para llamar la máquina de estados*/
{
	/**Se limpia la bandera para ir al siguiente estado*/
	currentState = 0;
	/**Se manda a llamar a la función dentro del estado*/
	currentState_range->fptrRange();

	/**Si la bandera de activación y el botón están encendidos se aumenta la bandera del siguiente estado*/
	input = FTM0_C0V;
	if (TRUE == flag_enable){
	if (TRUE == input) {
		currentState++;

	}
}
	/**Se actualiza el siguiente estado*/
	currentState_range = currentState_range->next[currentState_flag];
}

void range1(){
	if ( UPPER_LIMIT_C0V_1 >=input ){

	}currentState++;
}

void range2(){
	if ( LOWER_LIMIT_C0V_2 <=input && UPPER_LIMIT_C0V_2 >=input ){

	}currentState++;
}

void range3(){
	if ( LOWER_LIMIT_C0V_3 <=input && UPPER_LIMIT_C0V_3 >=input ){

	}currentState++;

}

void range4(){
	if ( LOWER_LIMIT_C0V_4 <=input && UPPER_LIMIT_C0V_4 >=input ){

	}currentState++;

}

void range5(){
	if ( LOWER_LIMIT_C0V_5 <=input && UPPER_LIMIT_C0V_5 >=input ){

	}currentState++;

}
