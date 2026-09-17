#include "bsp_key.h"
#include "bsp_led.h"
#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
/*********************
  模板工程
**********************/

int main(void) {

  // 系统滴答定时器初始化
  systick_config();

  // led初始化
  led_init();
  // 设置PC6为高电平
  led_switch();

  // 独立按键初始化
  independent_key_init();
  // 矩阵键盘初始化
  matrix_keypad_init();

  while (1) {
    // 读取矩阵键盘状态
    uint8_t key_pressed = key_scan();

    if (key_pressed != 0) {
       led_toggle(key_pressed%8 ? key_pressed%8 : 8);
    } 
    
  }
}

