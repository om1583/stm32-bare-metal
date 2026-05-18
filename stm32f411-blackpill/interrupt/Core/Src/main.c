
#include"stm32f4xx.h"

#define led 5 //Connected on PA5
#define button 0 // Connected on PA0

void EXTI0_IRQHandler(void)
{
	if((EXTI->PR)&(1U<<button)) //Checks interrupt pending register
	{
		GPIOA->ODR ^= (1U<<led); //Led toggles on button press
		EXTI->PR = (1U<<button);
	}
}

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //Enable RCC for port A
	GPIOA->MODER &= ~(3U<<2*led);
	GPIOA->MODER |= (1U<<2*led); //LED as output

	GPIOA->MODER &= ~(3U<<2*button); //button on A0 as input mode
	GPIOA->PUPDR &= ~(1U<<2*button);
	GPIOA->PUPDR |= (1U<<2*button);

	//Enable syscfg RCC
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~(0xFU); //Map PA[0] to EXTI0

	//configures EXTI
	EXTI->IMR |=(0x1UL << button);
	EXTI->FTSR |=(0x1UL << button); //Trigger interrupt on falling edge

	//Enables NVIC IrQ
	NVIC->ISER[0] |= (1U<<EXTI0_IRQn);

	while(1)
	{

	}
}
