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
#define DIEZ_MIL_ARREGLO 10000
#include "FlexTimer.h"


uint16 random_freq = 3000;
uint16 random_freq2 = 700;
uint16 random_freq3 = 400;
uint16 random_freq4 = 500;
uint16 random_freq5 = 140;
uint16 random_freq6 = 760;
uint16 random_freq7 = 340;
uint16 random_freq8 = 200;
uint16 random_freq9 = 3070;
uint16 random_freq10 = 709;
uint16 random_freq11 = 406;
uint16 random_freq12= 504;
uint16 random_freq13= 146;
uint16 random_freq14= 768;
uint16 random_freq15= 342;
uint16 random_freq16= 201;

float step = 0;//paso en el cual se recorreran los 10000 valores
float step2 = 0;
float step3 = 0;
float step4 = 0;
float step5 = 0;
float step6 = 0;
float step7 = 0;
float step8 = 0;
float step9 = 0;//paso en el cual se recorreran los 10000 valores
float step10 = 0;
float step11 = 0;
float step12 = 0;
float step13 = 0;
float step14 = 0;
float step15 = 0;
float step16 = 0;


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







/**VARIABLE COUNTERS*/

float FTM0_0_counter = 0;
float FTM0_1_counter =  0;
float FTM0_2_counter =  0;
float FTM0_3_counter =  0;
float FTM0_4_counter =  0;
float FTM0_5_counter =  0;
float FTM0_6_counter =  0;
float FTM0_7_counter =  0;
float FTM0_8_counter =  0;
float FTM0_9_counter =  0;
float FTM0_10_counter =  0;
float FTM0_11_counter =  0;
float FTM0_12_counter =  0;
float FTM0_13_counter =  0;
float FTM0_14_counter =  0;
float FTM0_15_counter =  0;

//uint8 FTM2_C0_counter = 0;
//uint8 FTM2_C1SC_counter =  0;

float FTM3_C0SC_counter = 0;
float FTM3_C1SC_counter =  0;
float FTM3_C2SC_counter =  0;
float FTM3_C3SC_counter =  0;
float FTM3_C4SC_counter =  0;
float FTM3_C5SC_counter =  0;
float FTM3_C6SC_counter =  0;
float FTM3_C7SC_counter =  0;

float FTM4_C0SC_counter = 0;
float FTM4_C1SC_counter =  0;
float FTM4_C2SC_counter =  0;
float FTM4_C3SC_counter =  0;
float FTM4_C4SC_counter =  0;
float FTM4_C5SC_counter =  0;
float FTM4_C6SC_counter =  0;
float FTM4_C7SC_counter =  0;


 void freq_per(){
	step=(random_freq/11);
	step2=(random_freq2/11);
	step3=(random_freq3/11);
	step4=(random_freq4/11);
	step5=(random_freq5/11);
	step6=(random_freq6/11);
	step7=(random_freq7/11);
	step8=(random_freq8/11);
	step9=(random_freq9/11);
	step10=(random_freq10/11);
	step11=(random_freq11/11);
	step12=(random_freq12/11);
	step13=(random_freq13/11);
	step14=(random_freq14/11);
	step15=(random_freq15/11);
	step16=(random_freq16/11);

 }



void FTM0_IRQHandler(){

	FTM0_SC &=~(FLEX_TIMER_TOF);


	FTM0_0_counter=FTM0_0_counter+step;
	if( DIEZ_MIL_ARREGLO <= FTM0_0_counter ){
		FTM0_0_counter=FTM0_0_counter-10000;
	}

	//si asgreagamos mas lineas se desajusta la frdcuencia


	FTM0_1_counter=FTM0_1_counter+step2;
	if( DIEZ_MIL_ARREGLO <= FTM0_1_counter ){
		FTM0_1_counter=(FTM0_1_counter-10000);
	}

	FTM0_2_counter=FTM0_2_counter+step3;
	if( DIEZ_MIL_ARREGLO <= FTM0_2_counter ){
		FTM0_2_counter=(FTM0_2_counter-10000);
	}

	FTM0_3_counter=FTM0_3_counter+step4;
	if( DIEZ_MIL_ARREGLO <= FTM0_3_counter ){
		FTM0_3_counter=(FTM0_3_counter-10000);
	}

	FTM0_4_counter=FTM0_4_counter+step5;
	if( DIEZ_MIL_ARREGLO <= FTM0_4_counter ){
		FTM0_4_counter=(FTM0_4_counter-10000);
	}

	FTM0_5_counter=FTM0_5_counter+step6;
	if( DIEZ_MIL_ARREGLO <= FTM0_5_counter ){
		FTM0_5_counter=(FTM0_5_counter-10000);
	}

	FTM0_6_counter=FTM0_6_counter+step7;
	if( DIEZ_MIL_ARREGLO <= FTM0_6_counter ){
		FTM0_6_counter=(FTM0_6_counter-10000);
	}
	FTM0_7_counter=FTM0_7_counter+step8;
	if( DIEZ_MIL_ARREGLO <= FTM0_7_counter ){
		FTM0_7_counter=(FTM0_7_counter-10000);
	}

	FTM0_8_counter=FTM0_8_counter+step9;
	if( DIEZ_MIL_ARREGLO <= FTM0_8_counter ){
		FTM0_8_counter=(FTM0_8_counter-10000);
	}

	FTM0_9_counter=FTM0_9_counter+step10;
	if( DIEZ_MIL_ARREGLO <= FTM0_9_counter ){
		FTM0_9_counter=(FTM0_9_counter-10000);
	}

	FTM0_10_counter=FTM0_10_counter+step11;
	if( DIEZ_MIL_ARREGLO <= FTM0_10_counter ){
		FTM0_10_counter=(FTM0_10_counter-10000);
	}

	FTM0_11_counter=FTM0_11_counter+step12;
	if( DIEZ_MIL_ARREGLO <= FTM0_11_counter ){
		FTM0_11_counter=(FTM0_11_counter-10000);
	}

	FTM0_12_counter=FTM0_12_counter+step13;
	if( DIEZ_MIL_ARREGLO <= FTM0_12_counter ){
		FTM0_12_counter=(FTM0_12_counter-10000);
	}
	FTM0_13_counter=FTM0_13_counter+step14;
	if( FTM0_13_counter <= FTM0_13_counter ){
		FTM0_13_counter=(FTM0_13_counter-10000);
	}

	FTM0_14_counter=FTM0_14_counter+step15;
	if( DIEZ_MIL_ARREGLO <= FTM0_14_counter ){
		FTM0_14_counter=(FTM0_14_counter-10000);
	}

	FTM0_15_counter=FTM0_15_counter+step16;
	if( DIEZ_MIL_ARREGLO <= FTM0_15_counter ){
		FTM0_15_counter=(FTM0_15_counter-10000);
	}









}

void FTM1_IRQHandler(){
	FTM1_SC &= ~FLEX_TIMER_TOF;


sine( FTM0_0_counter,  FTM0_1_counter, FTM0_2_counter, FTM0_3_counter, FTM0_4_counter, FTM0_5_counter, FTM0_6_counter, FTM0_7_counter, FTM0_8_counter, FTM0_9_counter, FTM0_10_counter, FTM0_11_counter, FTM0_12_counter, FTM0_13_counter, FTM0_14_counter, FTM0_15_counter);


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




