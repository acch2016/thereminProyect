/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */


#define FTM_FQ 30000000.0
#define CIEN_PUNTOS 148
#include "FlexTimer.h"
#include "DAC.h"

//uint8 hola = FALSE;

volatile uint32* FTMx_SC[4]={&FTM0_SC, &FTM1_SC, &FTM2_SC};
volatile uint32* FTMx_MODE[4]={&FTM0_MODE, &FTM1_MODE, &FTM2_MODE};
volatile uint32* FTMx_MOD[4]={&FTM0_MOD, &FTM1_MOD, &FTM2_MOD};
volatile uint32* FTMx_CONF[4]={&FTM0_CONF, &FTM1_CONF, &FTM2_CONF};
volatile uint32* FTMx_COMBINE[4] = {&FTM0_COMBINE, &FTM1_COMBINE, &FTM2_COMBINE};

volatile uint32* FTMx_CnV[4][8] =  {{&FTM0_C0V,&FTM0_C1V,&FTM0_C2V,&FTM0_C3V,&FTM0_C4V,&FTM0_C5V,&FTM0_C6V,&FTM0_C7V},
									{&FTM1_C0V,&FTM1_C1V},
									{&FTM2_C0V,&FTM2_C1V},
									{&FTM3_C0V,&FTM3_C1V,&FTM3_C2V,&FTM3_C3V,&FTM3_C4V,&FTM3_C5V,&FTM3_C6V,&FTM3_C7V}};

volatile uint32* FTMx_CnSC[4][8] = {{&FTM0_C0SC,&FTM0_C1SC,&FTM0_C2SC,&FTM0_C3SC,&FTM0_C4SC,&FTM0_C5SC,&FTM0_C6SC,&FTM0_C7SC},
									{&FTM1_C0SC,&FTM1_C1SC},
									{&FTM2_C0SC,&FTM2_C1SC},
									{&FTM3_C0SC,&FTM3_C1SC,&FTM3_C2SC,&FTM3_C3SC,&FTM3_C4SC,&FTM3_C5SC,&FTM3_C6SC,&FTM3_C7SC}};


typedef enum {
	PRIMER_VALOR,
	SEGUNDO_VALOR,
}ValorDefinitionType;

/** Variable to contain the FTM0 counter value*/
volatile float cntTimerValue = 0.0f;
volatile float cntTimerValue2 = 0.0f;
volatile uint8 flag = 0;
 float period = 0.0f;
 float  frequency = 0.0f;
 float tempValue = 0.0f;

 uint16 MOD = 0x014D;
 uint16 multiplier = 1;

/**STATUS FLAG*/
uint8 flag_FTM0_C0SC_status = 0;
uint8 flag_FTM0_C1SC_status =  0;
uint8 flag_FTM0_C2SC_status =  0;
uint8 flag_FTM0_C3SC_status =  0;
uint8 flag_FTM0_C4SC_status =  0;
uint8 flag_FTM0_C5SC_status =  0;
uint8 flag_FTM0_C6SC_status =  0;
uint8 flag_FTM0_C7SC_status =  0;

//uint8 flag_FTM2_C0SC_status = 0;
//uint8 flag_FTM2_C1SC_status =  0;

uint8 flag_FTM3_C0SC_status = 0;
uint8 flag_FTM3_C1SC_status =  0;
uint8 flag_FTM3_C2SC_status =  0;
uint8 flag_FTM3_C3SC_status =  0;
uint8 flag_FTM3_C4SC_status =  0;
uint8 flag_FTM3_C5SC_status =  0;
uint8 flag_FTM3_C6SC_status =  0;
uint8 flag_FTM3_C7SC_status =  0;

uint8 flag_FTM4_C0SC_status = 0;
uint8 flag_FTM4_C1SC_status =  0;
uint8 flag_FTM4_C2SC_status =  0;
uint8 flag_FTM4_C3SC_status =  0;
uint8 flag_FTM4_C4SC_status =  0;
uint8 flag_FTM4_C5SC_status =  0;
uint8 flag_FTM4_C6SC_status =  0;
uint8 flag_FTM4_C7SC_status =  0;

/**VARIABLE COUNTERS*/

uint8 FTM0_C0SC_counter = 0;
uint8 FTM0_C1SC_counter =  0;
uint8 FTM0_C2SC_counter =  0;
uint8 FTM0_C3SC_counter =  0;
uint8 FTM0_C4SC_counter =  0;
uint8 FTM0_C5SC_counter =  0;
uint8 FTM0_C6SC_counter =  0;
uint8 FTM0_C7SC_counter =  0;

//uint8 FTM2_C0SC_counter = 0;
//uint8 FTM2_C1SC_counter =  0;

uint8 FTM3_C0SC_counter = 0;
uint8 FTM3_C1SC_counter =  0;
uint8 FTM3_C2SC_counter =  0;
uint8 FTM3_C3SC_counter =  0;
uint8 FTM3_C4SC_counter =  0;
uint8 FTM3_C5SC_counter =  0;
uint8 FTM3_C6SC_counter =  0;
uint8 FTM3_C7SC_counter =  0;

uint8 FTM4_C0SC_counter = 0;
uint8 FTM4_C1SC_counter =  0;
uint8 FTM4_C2SC_counter =  0;
uint8 FTM4_C3SC_counter =  0;
uint8 FTM4_C4SC_counter =  0;
uint8 FTM4_C5SC_counter =  0;
uint8 FTM4_C6SC_counter =  0;
uint8 FTM4_C7SC_counter =  0;


 void freq_per(){
	 	 	 if(cntTimerValue>cntTimerValue2){
	 	 		 period = (65536-cntTimerValue+cntTimerValue2)*(1.0/FTM_FQ);
	 	 	 }else{
	      		period=(cntTimerValue2-cntTimerValue)*(1.0/FTM_FQ);
	 	 	 }

 			frequency=(1.0/period);

 }
//no se necesita
void FTM0_IRQHandler(){

	FTM0_SC &=~(FLEX_TIMER_TOF);
	flag_FTM0_C0SC_status = (FLEX_TIMER_CHF & FTM0_C0SC)>>7;
	flag_FTM0_C1SC_status = (FLEX_TIMER_CHF & FTM0_C1SC)>>7;
	flag_FTM0_C2SC_status = (FLEX_TIMER_CHF & FTM0_C2SC)>>7;
	flag_FTM0_C3SC_status = (FLEX_TIMER_CHF & FTM0_C3SC)>>7;
	flag_FTM0_C4SC_status = (FLEX_TIMER_CHF & FTM0_C4SC)>>7;
	flag_FTM0_C5SC_status = (FLEX_TIMER_CHF & FTM0_C5SC)>>7;
	flag_FTM0_C6SC_status = (FLEX_TIMER_CHF & FTM0_C6SC)>>7;
	flag_FTM0_C7SC_status = (FLEX_TIMER_CHF & FTM0_C7SC)>>7;

	FTM0_C0SC &= ~FLEX_TIMER_CHF;
	FTM0_C1SC &= ~FLEX_TIMER_CHF;
	FTM0_C2SC &= ~FLEX_TIMER_CHF;


	if ( TRUE == flag_FTM0_C0SC_status){
		FTM0_C0SC_counter++;
		FTM0_C0SC_counter++;
		FTM0_C0SC_counter++;
	//	FTM0_C1SC_counter++;
		//FTM0_C2SC_counter++;
		flag_FTM0_C0SC_status = FALSE;
		if ( CIEN_PUNTOS < FTM0_C0SC_counter ){
			FTM0_C0SC_counter=FALSE;
		}
	}

	else if (TRUE == flag_FTM0_C1SC_status){
		FTM0_C1SC_counter++;
		flag_FTM0_C1SC_status = FALSE;
		if ( CIEN_PUNTOS < FTM0_C1SC_counter ){
			FTM0_C1SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM0_C2SC_status){
		FTM0_C2SC_counter++;
//		FTM_CnV(FTM_0, Channel2, MOD * 2);
		flag_FTM0_C2SC_status = FALSE;
		if ( CIEN_PUNTOS < FTM0_C2SC_counter ){
			FTM0_C2SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM0_C3SC_status && CIEN_PUNTOS >= FTM0_C3SC_counter ){
		FTM0_C3SC_counter++;
		flag_FTM0_C3SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM0_C3SC_counter ){
			FTM0_C3SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM0_C4SC_status && CIEN_PUNTOS >= FTM0_C4SC_counter ){
		FTM0_C4SC_counter++;
		flag_FTM0_C4SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM0_C4SC_counter ){
			FTM0_C4SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM0_C5SC_status && CIEN_PUNTOS >= FTM0_C5SC_counter ){
		FTM0_C5SC_counter++;
		flag_FTM0_C5SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM0_C5SC_counter ){
			FTM0_C5SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM0_C6SC_status && CIEN_PUNTOS >= FTM0_C6SC_counter ){
		FTM0_C6SC_counter++;
		flag_FTM0_C6SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM0_C6SC_counter ){
			FTM0_C6SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM0_C7SC_status && CIEN_PUNTOS >= FTM0_C7SC_counter ){
		FTM0_C7SC_counter++;
		flag_FTM0_C7SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM0_C7SC_counter ){
			FTM0_C7SC_counter=FALSE;
		}
	}



//	if (PRIMER_VALOR == flag){
//		cntTimerValue = (float)FTM0_C0V;
//		flag++;
//	} else if (SEGUNDO_VALOR == flag) {
//		cntTimerValue2 = (float)FTM0_C0V;
//
//		freq_per();
//
//		flag = 0;
//	}

}

void FTM2_IRQHandler(){
	FTM2_SC &= ~FLEX_TIMER_TOF;
	//GPIO_tooglePIN(GPIOB,BIT18);

//	flag_FTM2_C0SC_status = FLEX_TIMER_CHF & FTM2_C0SC;
//	flag_FTM2_C1SC_status = FLEX_TIMER_CHF & FTM2_C1SC;
//
//
//	if ( TRUE == flag_FTM2_C0SC_status && CIEN_PUNTOS >= FTM2_C0SC_counter ){
//		FTM2_C0SC_counter++;
//		flag_FTM2_C0SC_status = FALSE;
//		if ( CIEN_PUNTOS == FTM2_C0SC_counter ){
//			FTM2_C0SC_counter=FALSE;
//		}
//	}
//
//	else if ( TRUE == flag_FTM2_C1SC_status && CIEN_PUNTOS >= FTM2_C1SC_counter ){
//		FTM2_C1SC_counter++;
//		flag_FTM2_C1SC_status = FALSE;
//		if ( CIEN_PUNTOS == FTM2_C1SC_counter ){
//			FTM2_C1SC_counter=FALSE;
//		}
//	}

sine(FTM0_C0SC_counter,FTM0_C1SC_counter,FTM0_C2SC_counter);

}


void FTM3_IRQHandler(){
	FTM3_SC &= ~FLEX_TIMER_TOF;
	//GPIO_tooglePIN(GPIOB,BIT18);

	flag_FTM3_C0SC_status = FLEX_TIMER_CHF & FTM3_C0SC;
	flag_FTM3_C1SC_status = FLEX_TIMER_CHF & FTM3_C1SC;
	flag_FTM3_C2SC_status = FLEX_TIMER_CHF & FTM3_C2SC;
	flag_FTM3_C3SC_status = FLEX_TIMER_CHF & FTM3_C3SC;
	flag_FTM3_C4SC_status = FLEX_TIMER_CHF & FTM3_C4SC;
	flag_FTM3_C5SC_status = FLEX_TIMER_CHF & FTM3_C5SC;
	flag_FTM3_C6SC_status = FLEX_TIMER_CHF & FTM3_C6SC;
	flag_FTM3_C7SC_status = FLEX_TIMER_CHF & FTM3_C7SC;



	if ( TRUE == flag_FTM3_C0SC_status && CIEN_PUNTOS >= FTM3_C0SC_counter ){
		FTM3_C0SC_counter++;
		flag_FTM3_C0SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C0SC_counter ){
			FTM3_C0SC_counter=FALSE;
		}
	}

	else if ( TRUE == flag_FTM3_C1SC_status && CIEN_PUNTOS >= FTM3_C1SC_counter ){
		FTM3_C1SC_counter++;
		flag_FTM3_C1SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C1SC_counter ){
			FTM3_C1SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM3_C2SC_status && CIEN_PUNTOS >= FTM3_C2SC_counter ){
		FTM3_C2SC_counter++;
		flag_FTM3_C2SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C2SC_counter ){
			FTM3_C2SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM3_C3SC_status && CIEN_PUNTOS >= FTM3_C3SC_counter ){
		FTM3_C3SC_counter++;
		flag_FTM3_C3SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C3SC_counter ){
			FTM3_C3SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM3_C4SC_status && CIEN_PUNTOS >= FTM3_C4SC_counter ){
		FTM3_C4SC_counter++;
		flag_FTM3_C4SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C4SC_counter ){
			FTM3_C4SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM3_C5SC_status && CIEN_PUNTOS >= FTM3_C5SC_counter ){
		FTM3_C5SC_counter++;
		flag_FTM3_C5SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C5SC_counter ){
			FTM3_C5SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM3_C6SC_status && CIEN_PUNTOS >= FTM3_C6SC_counter ){
		FTM3_C6SC_counter++;
		flag_FTM3_C6SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C6SC_counter ){
			FTM3_C6SC_counter=FALSE;
		}
	}


	else if ( TRUE == flag_FTM3_C7SC_status && CIEN_PUNTOS >= FTM3_C7SC_counter ){
		FTM3_C7SC_counter++;
		flag_FTM3_C7SC_status = FALSE;
		if ( CIEN_PUNTOS == FTM3_C7SC_counter ){
			FTM3_C7SC_counter=FALSE;
		}
	}


}


void FTM_ClockGating(FTMType FTM){
	switch(FTM){
	case FTM_0:
		SIM_SCGC6 |= FLEX_TIMER_0_CLOCK_GATING;
		break;
	case FTM_1:
		SIM_SCGC6 |= FLEX_TIMER_1_CLOCK_GATING;
		break;
	case FTM_2:
		SIM_SCGC6 |= FLEX_TIMER_2_CLOCK_GATING;
		break;
	case FTM_3:
		SIM_SCGC3 |= FLEX_TIMER_3_CLOCK_GATING;
		break;
	}
}

void FTM_Stat_Control(FTMType FTM, uint32 mask, FTMState state) {
	if (ENABLE == state) {
		*FTMx_SC[FTM] |= mask;
	} else if (DISABLE == state) {
		*FTMx_SC[FTM] &= mask;
	}

}

void FTM_MODE(FTMType FTM, uint32 mask){
	if(FTM == FTM_2){
		FTM2_MODE &= ~FLEX_TIMER_FTMEN;
	}
	*FTMx_MODE[FTM] |= mask;

}

void FTM_MOD(FTMType FTM, uint32 mask){
	*FTMx_MOD[FTM] |= mask;
}

void FTM_CnSC(FTMType FTM, FTMChannelType channel, uint32 mask, FTMState state){
	if(FALSE == state){
	*FTMx_CnSC[FTM][channel] |= mask;
	}else{
	*FTMx_CnSC[FTM][channel] &= mask;
	}
}

void FTM_CnV(FTMType FTM, FTMChannelType channel, uint32 mask){
	*FTMx_CnV[FTM][channel] = mask;

}


void FTM_CONF(FTMType FTM, uint32 mask){
	*FTMx_CONF[FTM] |= mask;
}

void FTM_COMBINE(FTMType FTM, uint32 mask){
	*FTMx_COMBINE[FTM] &= mask;
}

void FTM_updateCHValue(FTMType FTM,FTMChannelType channel, uint16 channelValue)
{
	/**Assigns a new value for the duty cycle*/
	*FTMx_CnV[FTM][channel] = channelValue;
}


void FTM_Init(const FTM_ConfigType * FTM_Config)
{
	FTM_ClockGating(FTM_Config->FTM);
	FTM_Stat_Control(FTM_Config->FTM, FTM_Config->FTM_SC_Mask, ENABLE);
	FTM_MODE(FTM_Config->FTM, FTM_Config->FTM_MODE_Mask);
	FTM_MOD(FTM_Config->FTM, FTM_Config->FTM_MOD_Mask);
	FTM_CnSC(FTM_Config->FTM,FTM_Config->FTM_Channel, FTM_Config->FTM_CnSC_Mask,ENABLE);
	FTM_CONF(FTM_Config->FTM, FTM_Config->FTM_CONF_Mask);
}

//float frecuency_value(){
//	return frequency;
//}


//void clean_frecuency(){
//	frequency = 0;
//}


