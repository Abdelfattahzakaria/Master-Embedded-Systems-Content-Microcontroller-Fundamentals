/*
/*
 *   Topic   :                                                     Clock Managament Unit
 *   File    :                                                     __CMU_C__
 *   Author  :                                                     abdelfattahzakariaelbadry@gmail.com
*/


#include <stdint.h>


typedef     volatile uint32_t                       vuint32_t;

#define      RCC_BASE                               0x40021000
#define      GPIO_BASE                              0x40010800

#define      APB2ENR_OFFEST                         0x18
#define      CRH_OFFEST                             0x04
#define      ODR_OFFEST                             0x0C


#define      RCC_APB2ENR                            *((vuint32_t *)(RCC_BASE + APB2ENR_OFFEST))
#define      GPIO_CRH                               *((vuint32_t *)(GPIO_BASE + CRH_OFFEST))
#define      GPIO_ODR                               *((vuint32_t *)(GPIO_BASE + ODR_OFFEST))

#define     SET_RCC_APB2ENR_BIT_2                	RCC_APB2ENR |= (1<< 2)
#define     RESET_GPIO_CRH_BIT_20_21_22_23          GPIO_CRH    &= 0XFF0FFFFF
#define     SET_GPIO_CRH_BIT_20_21_22_23            GPIO_CRH    |= 0X00200000


typedef union
{
	vuint32_t All_Pins;
	struct
	{
		vuint32_t reserved0t12: 13;
		vuint32_t bin13       : 1;
	}Pin;
}URegister;
volatile URegister *R_ODR= (volatile URegister *)(GPIO_BASE + ODR_OFFEST);

void Toggle_GPIO_ODR_PIN13(void)
{
	unsigned char i;
	R_ODR->Pin.bin13= 1;
	for(i= 0; i <= 250; i++);
	R_ODR->Pin.bin13= 0;
	for(i= 0; i <= 250; i++);
      
	return;
}

int main(void)
{
	SET_RCC_APB2ENR_BIT_2;
	RESET_GPIO_CRH_BIT_20_21_22_23;
	SET_GPIO_CRH_BIT_20_21_22_23;

	while(1)
	{
		Toggle_GPIO_ODR_PIN13();
	}

	return 0;
}
 
 
  
           
		    