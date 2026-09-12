#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
/*********************
  模板工程
**********************/

void GPIO_config(void) {
  // 1. 时钟初始化
  rcu_periph_clock_enable(RCU_GPIOB);
  // 2. 配置GPIO 输入输出模式
  gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_2);
  // 3. 配置GPIO 模式的操作方式
  gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_2);
}

int main(void) {

  // 系统滴答定时器初始化
  systick_config();

  // IO引脚初始化
  GPIO_config();
  // 设置PB2为高电平
  
  while (1) {
    gpio_bit_reset(GPIOB, GPIO_PIN_2);
    delay_1ms(500);
    
    gpio_bit_set(GPIOB, GPIO_PIN_2);
    delay_1ms(500);
  }
}