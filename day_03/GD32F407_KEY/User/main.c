
#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

//PB2  推挽
void LED_GPIO_config(void){
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOB);
	//2.配置GPIO模式 输出
	gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_2);
	//3.输出需要配置  输出模式
	gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,GPIO_PIN_2);
}


void KEY_GPIO_config(void){
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOA);
	//2.配置GPIO模式 输出
	gpio_mode_set(GPIOB,GPIO_MODE_INPUT,GPIO_PUPD_NONE,GPIO_PIN_0);
	//3.输出需要配置  输出模式
	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,GPIO_PIN_0);
}


 

int main(void)
{
		//系统滴答时钟初始化
    systick_config();
	
		//GPIO初始化
		LED_GPIO_config();
	  KEY_GPIO_config();
	// 设置初始状态 
	 FlagStatus preState = RESET;
    while(1) {
			FlagStatus currState = gpio_input_bit_get(GPIOA,GPIO_PIN_0);
			
			if(preState == RESET && currState == SET){
			
				//拉高PB2
			gpio_bit_set(GPIOB,GPIO_PIN_2);
				preState = currState;
			} else if (preState == SET && currState == RESET) {
			
			//拉低PB2
			gpio_bit_reset(GPIOB,GPIO_PIN_2);
				preState = currState;
			}
			
		
			 
			
		 
    }
}
