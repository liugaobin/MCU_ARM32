#include "bsp_leds.h"

LED_PARAM leds[] = {
	{RCU_GPIOC,GPIOC,GPIO_PIN_6}, //0
	{RCU_GPIOD,GPIOD,GPIO_PIN_8}, //1
	{RCU_GPIOD,GPIOD,GPIO_PIN_9},
	{RCU_GPIOD,GPIOD,GPIO_PIN_10},
	{RCU_GPIOD,GPIOD,GPIO_PIN_11},
	{RCU_GPIOD,GPIOD,GPIO_PIN_12},
	{RCU_GPIOD,GPIOD,GPIO_PIN_13},
	{RCU_GPIOD,GPIOD,GPIO_PIN_14},
	{RCU_GPIOD,GPIOD,GPIO_PIN_15},
};


static void GPIO_config(rcu_periph_enum rcu,uint32_t port,uint32_t pin){
	//1.打开时钟
	rcu_periph_clock_enable(rcu);
	//2.配置GPIO模式 输出
	gpio_mode_set(port,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,pin);
	//3.输出需要配置  输出模式
	gpio_output_options_set(port,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,pin);
}

//初始化LED灯
void bsp_leds_config(){
	//所有引脚初始化
	for(uint8_t i=0;i<sizeof(leds)/sizeof(leds[0]);i++){
		GPIO_config(leds[i].rcu,leds[i].port,leds[i].pin);
	}
	
	//打开开关
	gpio_bit_reset(leds[0].port,leds[0].pin);
	
	//关闭所有的灯
	for(uint8_t i=1;i<sizeof(leds)/sizeof(leds[0]);i++){
		gpio_bit_set(leds[i].port,leds[i].pin);
	}
}

//打开所有的灯
void bsp_leds_open_all(){
	for(uint8_t i=1;i<sizeof(leds)/sizeof(leds[0]);i++){
		gpio_bit_reset(leds[i].port,leds[i].pin);
	}
}

//关闭所有的灯
void bsp_leds_close_all(){
	for(uint8_t i=1;i<sizeof(leds)/sizeof(leds[0]);i++){
		gpio_bit_set(leds[i].port,leds[i].pin);
	}
}

//打开一盏灯
void bsp_leds_open(LED_NUM led){
	gpio_bit_reset(leds[led].port,leds[led].pin);
}

//关闭一盏灯
void bsp_leds_close(LED_NUM led){
	gpio_bit_set(leds[led].port,leds[led].pin);
}


