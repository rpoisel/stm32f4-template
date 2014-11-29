/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include <stm32f4xx_tim.h>
#include <stm32f4xx_rcc.h>

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void InitializeTimer() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 40000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
}

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void) {
	int timerValue = 0;

	InitializeTimer();

	/**
	 *  IMPORTANT NOTE!
	 *  The symbol VECT_TAB_SRAM needs to be defined when building the project
	 *  if code has been located to RAM and interrupts are used.
	 *  Otherwise the interrupt table located in flash will be used.
	 *  See also the <system_*.c> file and how the SystemInit() function updates
	 *  SCB->VTOR register.
	 *  E.g.  SCB->VTOR = 0x20000000;
	 */

	/* TODO - Add your application code here */

	/* Initialize LEDs */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	/* Infinite loop */
	for(;;) {
		timerValue = TIM_GetCounter(TIM2);
		if (timerValue == 400) {
			/* Turn on LEDs */
			STM_EVAL_LEDOn(LED3);
			STM_EVAL_LEDOff(LED4);
			STM_EVAL_LEDOn(LED5);
			STM_EVAL_LEDOff(LED6);
		} else if (timerValue == 500) {
			STM_EVAL_LEDOff(LED3);
			STM_EVAL_LEDOn(LED4);
			STM_EVAL_LEDOff(LED5);
			STM_EVAL_LEDOn(LED6);
		}
	}
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size) {
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void) {
	/* TODO, implement your code here */
	return -1;
}
