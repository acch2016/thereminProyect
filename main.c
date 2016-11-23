/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MK64F12.h"
#include "MCG.h"
#include "FlexTimer.h"
#include "stdio.h"
#include "NVIC.h"

#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/
/** Macros for debugging*/
#define DEBUG

int main(void)
{
	int mcg_clk_hz;
	unsigned char modeMCG = 0;

	mcg_clk_hz = fei_fbi(SLOW_IRC_FREQ,SLOW_IRC); //64 Hz ----> 32768
	mcg_clk_hz = fbi_fbe(CLK_FREQ_HZ,LOW_POWER,EXTERNAL_CLOCK); //97.656KHz ----> 50MHz
	mcg_clk_hz = fbe_pbe(CLK_FREQ_HZ,PLL0_PRDIV,PLL0_VDIV); //97.656KHz --------> 50MHz
	mcg_clk_hz = pbe_pee(CLK_FREQ_HZ);

	modeMCG = what_mcg_mode();
#ifdef DEBUG
	printf("\nMCG mode =  %d\n",modeMCG);
	printf("Clock Rate =  %d MHz\n",mcg_clk_hz);
#endif
	/* Write your code here */
	const FTM_ConfigType FTM0_Config={	FTM_0,
			Channel0,
			FLEX_TIMER_0_CLOCK_GATING,
			FLEX_TIMER_TOIE | FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_1,
			FLEX_TIMER_WPDIS,
			0x0320,//3k750
			FLEX_TIMER_MSA | FLEX_TIMER_ELSA | FTM_CnSC_CHIE_MASK,
			FTM_CONF_BDMMODE(3),
			FALSE};

	const FTM_ConfigType FTM1_Config={	FTM_1,
			Channel0,
			FLEX_TIMER_1_CLOCK_GATING,
			FLEX_TIMER_TOIE | FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_1,
			FLEX_TIMER_WPDIS,
			0x0,
			FALSE,
			FALSE,
			FALSE};

	const FTM_ConfigType FTM2_Config={	FTM_2,
			Channel0,
			FLEX_TIMER_2_CLOCK_GATING,
			FLEX_TIMER_TOIE | FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_1,
			FLEX_TIMER_WPDIS,
			0x02A9,
			FLEX_TIMER_MSA | FLEX_TIMER_ELSA,
			FTM_CONF_BDMMODE(3),
			FALSE};

	const FTM_ConfigType FTM3_Config={	FTM_3,
			Channel0,
			FLEX_TIMER_3_CLOCK_GATING,
			FLEX_TIMER_TOIE | FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_1,
			FLEX_TIMER_WPDIS,
			0x0,
			FALSE,
			FALSE,
			FALSE};

	////////////////////////////////////////////DAC
	SIM_SCGC2  |= SIM_SCGC2_DAC0_MASK;//clock gating del DAC0
	DAC0_C0 |= DAC_C0_DACEN_MASK;//pin DAC enable
	DAC0_C0 |= DAC_C0_DACRFS_MASK;//pin DAC reference Select
	////////////////////////////////////////////DAC

	FTM_Init(&FTM0_Config);
	FTM_Init(&FTM2_Config);
	/**Initialization of FlexTimer in output compare mode*/

	NVIC_enableInterruptAndPriotity(FTM0_IRQ,PRIORITY_9);
	NVIC_enableInterruptAndPriotity(FTM2_IRQ,PRIORITY_8);

	EnableInterrupts;/** Enabling Global interrupts with PRIMASK bit*/

	/* This for loop should be replaced. By default this loop allows a single stepping. */

	for (;;) {

	}
	/* Never leave main */
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
