
#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "bsp_leds.h"


//PC0
void KEY_GPIO_config(void){
	//PC0  按键1
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOC);
	//2.配置GPIO模式
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_0);
	
	//PC1  按键2
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOC);
	//2.配置GPIO模式
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_1);
	
	//PC2  按键3
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOC);
	//2.配置GPIO模式
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_2);
	
	
	//PC3  按键4
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOC);
	//2.配置GPIO模式
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_3);
}



int main(void)
{
		//系统滴答时钟初始化
    systick_config();
	
		//GPIO初始化
		bsp_leds_config();
		KEY_GPIO_config();
		
	
		//保存按键之前的状态
		FlagStatus key1_preSta = SET;
		FlagStatus key2_preSta = SET;
		FlagStatus key3_preSta = SET;
		FlagStatus key4_preSta = SET;
    while(1) {
			//当前状态
			FlagStatus key1_curSta = gpio_input_bit_get(GPIOC,GPIO_PIN_0);
			
			if(key1_preSta==SET&&key1_curSta==RESET){
				//下降沿  按下   之前是低电平,现在是高电平
				bsp_leds_open(LED1);
				key1_preSta = key1_curSta;
			}else if(key1_preSta==RESET&&key1_curSta==SET){
				//上升沿  松开   之前是高电平,现在是低电平
				bsp_leds_close(LED1);
				key1_preSta = key1_curSta;
			}

			
			//当前状态
			FlagStatus key2_curSta = gpio_input_bit_get(GPIOC,GPIO_PIN_1);  
			
			if(key2_preSta==SET&&key2_curSta==RESET){
				//下降沿  按下   之前是低电平,现在是高电平
				bsp_leds_open(LED2);
				key2_preSta = key2_curSta;
			}else if(key2_preSta==RESET&&key2_curSta==SET){
				//上升沿  松开   之前是高电平,现在是低电平
				bsp_leds_close(LED2);
				key2_preSta = key2_curSta;
			}
			
			
			//当前状态
			FlagStatus key3_curSta = gpio_input_bit_get(GPIOC,GPIO_PIN_2);  
			
			if(key3_preSta==SET&&key3_curSta==RESET){
				//下降沿  按下   之前是低电平,现在是高电平
				bsp_leds_open(LED3);
				key3_preSta = key3_curSta;
			}else if(key3_preSta==RESET&&key3_curSta==SET){
				//上升沿  松开   之前是高电平,现在是低电平
				bsp_leds_close(LED3);
				key3_preSta = key3_curSta;
			}
			
			
			//当前状态
			FlagStatus key4_curSta = gpio_input_bit_get(GPIOC,GPIO_PIN_3);  
			
			if(key4_preSta==SET&&key4_curSta==RESET){
				//下降沿  按下   之前是低电平,现在是高电平
				bsp_leds_open(LED4);
				key4_preSta = key4_curSta;
			}else if(key4_preSta==RESET&&key4_curSta==SET){
				//上升沿  松开   之前是高电平,现在是低电平
				bsp_leds_close(LED4);
				key4_preSta = key4_curSta;
			}
			
			delay_1ms(20);
			
    }
}
