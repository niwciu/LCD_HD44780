/*
 * tim_delay.c
 *
 *  Created on: 26 wrz 2014
 *      Author: niw-lap
 */
#include "tim_delay.h"
#include "stm32g474xx.h"


void _delay_ms(uint32_t delay_ms)
{
	RCC-> AHB1ENR |= RCC_APB1ENR1_TIM6EN;

	TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
	TIM6 -> PSC = 0;
	TIM6 -> ARR =47999;

	TIM6 -> CR1 |= TIM_CR1_ARPE;
	TIM6 -> EGR |= TIM_EGR_UG;
	TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));

	TIM6 -> CR1 |= TIM_CR1_CEN;
	while (delay_ms!=0)
	{
		if ((TIM6 -> SR & TIM_SR_UIF) == TIM_SR_UIF)
		{
			TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));
			delay_ms--;
		}
	}
	TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
	RCC-> AHB1ENR &= ~((uint32_t)RCC_APB1ENR1_TIM6EN);  //wy��cz clocka dla timera

}

void _delay_us(uint32_t delay_us)
{
	RCC-> AHB1ENR |= RCC_APB1ENR1_TIM6EN;

	TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
	TIM6 -> PSC = 0;
	TIM6 -> ARR =47;

	TIM6 -> CR1 |= TIM_CR1_ARPE;
	TIM6 -> EGR |= TIM_EGR_UG;
	TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));

	TIM6 -> CR1 |= TIM_CR1_CEN;
	while (delay_us!=0)
	{
		if ((TIM6 -> SR & TIM_SR_UIF) == TIM_SR_UIF)
		{
			TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));
			delay_us--;
		}
	}
	TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
	RCC-> AHB1ENR &= ~((uint32_t)RCC_APB1ENR1_TIM6EN);  //wy��cz clocka dla timera
}

