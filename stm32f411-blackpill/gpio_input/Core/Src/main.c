#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN; //Enable clock for port A
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOBEN; //Enable clock for port B

	GPIOA->MODER &= ~(3U<<(2*5)); //button is on A5 so pin 5 is configured as input
	GPIOA->PUPDR &=~(3U<<(2*5));
	GPIOA->PUPDR |= (1U<<(2*5));  //enable pul-up to avoid floating pin input

	GPIOB->MODER &= ~(3U<<(2*0));
	GPIOB->MODER |= (1U<<(2*0));//LED is connected on B0 pin 0 is configured as output

	while(1)
	{
		if(!((GPIOA->IDR) & (1U<<5)))
		{
			GPIOB->ODR |= 1U; //turn on led
		}
		else
		{
			GPIOB->ODR &= ~(1U); //turn off led
		}
	}

}
