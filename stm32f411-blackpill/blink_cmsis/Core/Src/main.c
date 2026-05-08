#include"stm32f4xx.h"

void delay()
{
	for(volatile uint32_t i=0;i<1000000;i++);
}

int main(void)
{
	//enable peripheral clock
	RCC->AHB1ENR |=  RCC_AHB1ENR_GPIOCEN;

	//Set pin PC13 to output mode
	GPIOC->MODER &= ~(3U<<26);
	GPIOC->MODER |= (1U<<26);

	while(1)
	{
		GPIOC->ODR &= ~(1<<13); //Turn on led
		delay();

		GPIOC->ODR |= (1<<13); //Turn of led
		delay();

	}

}
