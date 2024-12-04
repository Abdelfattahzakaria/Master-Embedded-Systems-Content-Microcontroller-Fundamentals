/*
/*
 *   Topic   :                                                     STM32F103XX Interrputs
 *   File    :                                                     __CMU_C__
 *   Author  :                                                     abdelfattahzakariaelbadry@gmail.com
*/

#include "datatype.h" 

/*define function prototype*/: 
void clock_init();
// Override On EXTI0_IRQHandler ISR Function
void EXTI0_IRQHandler(); 
void GPIO_Pin13_Output_Init(); 

/*define macros*/ 
#define GPIO_BASE                                 0X40010800
#define RCC_BASE                                  0X40021000
#define EXTL_BASE                                 0X40010400
#define NVIC_BASE                                 0XE000E100

#define GPIOA_ODR                                 *((vuint32_t *)(GPIO_BASE + 0X0C))
#define GPIOA_CRH                                 *((vuint32_t *)(GPIO_BASE + 0X04))
#define RCC_APB2ENR                               *((vuint32_t *)(RCC_BASE + 0X18))
#define EXTL_IMR                                  *((vuint32_t *)(EXTL_BASE + 0X0))
#define EXTL_RTSR                                 *((vuint32_t *)(EXTL_BASE + 0X0))
#define EXTL_PR                                   *((vuint32_t *)(EXTL_BASE + 0X14))
#define AFIO_EXTICRL                              *((vuint32_t *)(GPIO_BASE + 0X08))
#define GPIO_CRL                                  *((vuint32_t *)(GPIO_BASE + 0X0))
#define NVIC_EXTL0                                *((vuint32_t *)(NVIC_BASE + 0X0))

int main(void)
{
	/*init clock*/
	clock_init();
	
	/*init pin13 as output*/
	GPIO_Pin13_Output_Init();
	
	/*enable floating point*/
	GPIO_CRL |= (1 << 2);
	
	/*set extl0_mux select line to select porta0*/
	AFIO_EXTICRL |= 0; 
	
	/*enable mask register*/
	EXTL_IMR |= 1; 
	
	/*set interrput occurrence with the rising edge*/
	EXTL_RTSR |= 1; 
	
	/*enable nvic extl0 line*/
	NVIC_EXTL0 |= (1 << 6); 
	
	/*start infinite loop*/
	while(True) ; 
	
	return 0;
}

void clock_init(void)
{
	/*enable the gpio clock*/
	RCC_APB2ENR |= (1 << 2);
	
	/*enable alt clock*/
	RCC_APB2ENR |= 1; 
}

void GPIO_Pin13_Output_Init(void)
{
	/*init register*/
	GPIOA_CRH &= 0XFF0FFFFF;
	
	/*set as output*/
	GPIOA_CRH |= 0X00200000;
}

void EXTI0_IRQHandler(void)
{
	/*toggle led at pin 13*/
	GPIOA_ODR ^= (1 << 13);
	
	/*clear pending register*/
	EXTL_PR |= 1; 
}


      