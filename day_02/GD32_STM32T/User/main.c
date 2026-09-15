
#include "main.h"
#include "systick.h"
//static __IO uint32_t uwTimingDelay;
//RCC_ClocksTypeDef RCC_Clocks;

///* Private function prototypes -----------------------------------------------*/
//static void Delay(__IO uint32_t nTime);

void GPIO_config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int main(void)
{
	
	//系统滴答时钟初始化
  systick_config();
	//GPIO初始化
	GPIO_config();
//  GPIO_InitTypeDef GPIO_InitStructure;
// 
// /*!< At this stage the microcontroller clock setting is already configured, 
//       this is done through SystemInit() function which is called from startup
//       files before to branch to application main.
//       To reconfigure the default setting of SystemInit() function, 
//       refer to system_stm32f4xx.c file */

//  /* SysTick end of count event each 10ms */
//  RCC_GetClocksFreq(&RCC_Clocks);
//  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
//  
//  /* Add your application code here */
//  /* Insert 50 ms delay */
//  Delay(5);
//  
//  /* Output HSE clock on MCO1 pin(PA8) ****************************************/ 
//  /* Enable the GPIOA peripheral */ 
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//  
//  /* Configure MCO1 pin(PA8) in alternate function */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//    
//  /* HSE clock selected to output on MCO1 pin(PA8)*/
//  RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);
//  
//  
//  /* Output SYSCLK/4 clock on MCO2 pin(PC9) ***********************************/ 
//  /* Enable the GPIOACperipheral */ 
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//  
//  /* Configure MCO2 pin(PC9) in alternate function */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//    
//  /* SYSCLK/4 clock selected to output on MCO2 pin(PC9)*/
//  RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_4);
  
     
  /* Infinite loop */
	//如果没有循环会一直重启
  while (1){
		//拉高
		GPIO_SetBits(GPIOB, GPIO_Pin_2);
		//睡眠
		delay_1ms(1000);
		//拉低
		GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		//睡眠
		delay_1ms(1000);
  }
}

///**
//  * @brief  Inserts a delay time.
//  * @param  nTime: specifies the delay time length, in milliseconds.
//  * @retval None
//  */
//void Delay(__IO uint32_t nTime)
//{ 
//  uwTimingDelay = nTime;

//  while(uwTimingDelay != 0);
//}

///**
//  * @brief  Decrements the TimingDelay variable.
//  * @param  None
//  * @retval None
//  */
//void TimingDelay_Decrement(void)
//{
//  if (uwTimingDelay != 0x00)
//  { 
//    uwTimingDelay--;
//  }
//}

//#ifdef  USE_FULL_ASSERT

///**
//  * @brief  Reports the name of the source file and the source line number
//  *         where the assert_param error has occurred.
//  * @param  file: pointer to the source file name
//  * @param  line: assert_param error line source number
//  * @retval None
//  */
//void assert_failed(uint8_t* file, uint32_t line)
//{ 
//  /* User can add his own implementation to report the file name and line number,
//     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

//  /* Infinite loop */
//  while (1)
//  {
//  }
//}
//#endif

///**
//  * @}
//  */


