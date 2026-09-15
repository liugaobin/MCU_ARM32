#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include <stdint.h>
#include "gd32f4xx.h"
#define MATRIX_ROW_NUM 4
#define MATRIX_COL_NUM 4

 


// 定义单个GPIO引脚的结构体
typedef struct {
    uint32_t gpio_periph; // GPIO端口，如 GPIOC, GPIOE
    uint32_t pin;         // GPIO引脚，如 GPIO_PIN_8 
} gpio_key_pin_t;


extern gpio_key_pin_t key_list[5];

typedef struct {
    gpio_key_pin_t rows[MATRIX_ROW_NUM]; // 行引脚数组 (4行)
    gpio_key_pin_t cols[MATRIX_COL_NUM]; // 列引脚数组 (4列)
    // 按键状态机（用于非阻塞消抖）
    uint8_t key_state[MATRIX_ROW_NUM][MATRIX_COL_NUM]; // 0:松开, 1:按下待确认, 2:确认按下
    uint8_t key_val[MATRIX_ROW_NUM][MATRIX_COL_NUM];   // 键值映射表
} matrix_keypad_t;

extern gpio_key_pin_t key_list[5];

// 声明一个全局的矩阵键盘对象
extern matrix_keypad_t keypad;



// 独立按键
void independent_key_init(void);

uint8_t independent_key_state(uint8_t key_index);


// 矩阵键盘
void matrix_keypad_init(void);
uint8_t key_scan(void);




#endif /* __BSP_KEY_H__ */

