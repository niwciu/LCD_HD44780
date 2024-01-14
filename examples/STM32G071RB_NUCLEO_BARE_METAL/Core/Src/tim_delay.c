/*
 * tim_delay.c
 *
 *  Created on: 26 wrz 2014
 *      Author: niw-lap
 */
#include "tim_delay.h"

void _delay_ms(uint32_t delay_ms)
{
	RCC-> APBENR1 |= RCC_APBENR1_TIM6EN;

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
	RCC-> APBENR1 &= ~((uint32_t)RCC_APBENR1_TIM6EN);  //wy��cz clocka dla timera

}

void _delay_us(uint32_t delay_us)
{
	RCC-> APBENR1 |= RCC_APBENR1_TIM6EN;

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
	RCC-> APBENR1 &= ~((uint32_t)RCC_APBENR1_TIM6EN);  //wy��cz clocka dla timera
}

void count_ms(uint16_t *delay_ms)
{
	if((TIM6 ->CR1 & TIM_CR1_CEN) ==0)
	{
		RCC-> APBENR1 |= RCC_APBENR1_TIM6EN;

		TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
		TIM6 -> PSC = 0;
		TIM6 -> ARR =47999;

		TIM6 -> CR1 |= TIM_CR1_ARPE;
		TIM6 -> EGR |= TIM_EGR_UG;
		TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));

		TIM6 -> CR1 |= TIM_CR1_CEN;
	}

	if ((TIM6 -> SR & TIM_SR_UIF) == TIM_SR_UIF)
	{
		TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));
		(*delay_ms)--;
	}

	if(*delay_ms==0)
	{
		TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
		RCC-> APBENR1 &= ~((uint32_t)RCC_APBENR1_TIM6EN);  //wy��cz clocka dla timera
	}
}

void count_s(uint16_t *delay_s)
{
	if((TIM6 ->CR1 & TIM_CR1_CEN) ==0)
	{
		RCC-> APBENR1 |= RCC_APBENR1_TIM6EN;

		TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
		TIM6 -> PSC = 999;
		TIM6 -> ARR =47999;

		TIM6 -> CR1 |= TIM_CR1_ARPE;
		TIM6 -> EGR |= TIM_EGR_UG;
		TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));

		TIM6 -> CR1 |= TIM_CR1_CEN;
	}

	if ((TIM6 -> SR & TIM_SR_UIF) == TIM_SR_UIF)
	{
		TIM6 -> SR &=~((uint32_t)(TIM_SR_UIF));
		(*delay_s)--;
	}

	if(*delay_s==0)
	{
		TIM6 -> CR1 &=~((uint32_t)(TIM_CR1_CEN));
		RCC-> APBENR1 &= ~((uint32_t)RCC_APBENR1_TIM6EN);  //wy��cz clocka dla timera
	}
}
