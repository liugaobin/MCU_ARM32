#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "gd32f4xx.h"

typedef struct {
    uint32_t gpiox;
    uint32_t gpio_pin;
} led_t;
/**
 * @brief 
 * 
 */
extern led_t led_list[10];

// 初始化项目所有灯资源
void led_init(void);


void led_switch(void);
void led_on(uint32_t led_index);
void led_off(uint32_t led_index);
void led_open_all(void);
void led_close_all(void);
void led_toggle(uint32_t led_index);
#endif