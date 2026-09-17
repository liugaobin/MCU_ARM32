#include "bsp_key.h"

// 定义按键列表，PA0 是第一个按键，PC0~PC3 是第二到第五个
gpio_key_pin_t key_list[5] = {
    {GPIOA, GPIO_PIN_0}, // 按键1 (PA0)
    {GPIOC, GPIO_PIN_0}, // 按键2 (PC0)
    {GPIOC, GPIO_PIN_1}, // 按键3 (PC1)
    {GPIOC, GPIO_PIN_2}, // 按键4 (PC2)
    {GPIOC, GPIO_PIN_3}  // 按键5 (PC3)
};

matrix_keypad_t keypad = {
    // 1. 填充行引脚
    .rows = {{GPIOE, GPIO_PIN_8},
             {GPIOE, GPIO_PIN_9},
             {GPIOE, GPIO_PIN_10},
             {GPIOE, GPIO_PIN_11}},

    // 2. 填充列引脚
    .cols = {{GPIOE, GPIO_PIN_12},
             {GPIOE, GPIO_PIN_13},
             {GPIOE, GPIO_PIN_14},
             {GPIOE, GPIO_PIN_15}},

    // 3. 直接填充键值映射表
    .key_val = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}

};

// 初始化独立按键
void independent_key_init(void) {
  // 1. 打开时钟 (PA0 和 PC0~PC3)
  rcu_periph_clock_enable(RCU_GPIOA);

  gpio_mode_set(key_list[0].gpio_periph, GPIO_MODE_INPUT, GPIO_PUPD_NONE,
                key_list[0].pin);
  rcu_periph_clock_enable(RCU_GPIOC);
  // 2. 遍历数组，配置为上拉输入
  for (int i = 1; i < 5; i++) {
    gpio_mode_set(key_list[i].gpio_periph, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
                  key_list[i].pin);
  }
}

// 获取按键状态（返回 0：未按下，1：按下）
// 注意：底层仅提供即时电平读取，建议在应用层（主循环）加入状态机消抖
uint8_t independent_key_state(uint8_t key_index) {
  if (key_index >= 5) {
    return 0; // 越界保护
  }

  // 硬件设计：按键按下接 GND，未按下靠上拉电阻拉高
  if (gpio_input_bit_get(key_list[key_index].gpio_periph,
                         key_list[key_index].pin) == RESET) {
    // 低电平，按键被按下
    if (key_index == 0) {
      return 0;
    } else {
      return 1;
    }
  } else {
    if (key_index == 0) {
      return 1;
    } else {
      return 0;
    }
  }
}

// 初始化结构体数据
void matrix_keypad_init(void) {

  //  初始化硬件GPIO
  rcu_periph_clock_enable(RCU_GPIOE);

  // 行引脚：推挽输出，初始输出高电平（不选中）
  for (int i = 0; i < MATRIX_ROW_NUM; i++) {
    gpio_mode_set(keypad.rows[i].gpio_periph, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  keypad.rows[i].pin);
    gpio_output_options_set(keypad.rows[i].gpio_periph, GPIO_OTYPE_PP,
                            GPIO_OSPEED_2MHZ, keypad.rows[i].pin);
    gpio_bit_set(keypad.rows[i].gpio_periph, keypad.rows[i].pin);
  }
  // 列引脚：上拉输入
  for (int j = 0; j < MATRIX_COL_NUM; j++) {
    gpio_mode_set(keypad.cols[j].gpio_periph, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
                  keypad.cols[j].pin);
  }
}

// 扫描矩阵键盘，返回按下的键值（0表示无按键）
uint8_t key_scan(void) {
  uint8_t key_pressed = 0;

  for (int i = 0; i < MATRIX_ROW_NUM; i++) {
    // 1. 当前行输出低电平，其他行输出高电平
    for (int r = 0; r < MATRIX_ROW_NUM; r++) {
      if (r == i) {
        gpio_bit_reset(keypad.rows[r].gpio_periph,
                       keypad.rows[r].pin); // 拉低选中行
      }
      else {
        gpio_bit_set(keypad.rows[r].gpio_periph,
                     keypad.rows[r].pin); // 拉高其他行
      }
    }

    // 2. 读取所有列的状态
    for (int j = 0; j < MATRIX_COL_NUM; j++) {
      uint8_t col_state =
          gpio_input_bit_get(keypad.cols[j].gpio_periph, keypad.cols[j].pin);

      if (col_state == RESET) { // 列被拉低了，说明(i, j)位置的按键被按下

        // 3. 简单的状态机消抖
        if (keypad.key_state[i][j] == 0) {
          keypad.key_state[i][j] = 1; // 第一次检测到按下，进入待确认状态
        } else if (keypad.key_state[i][j] == 1) {
          keypad.key_state[i][j] = 2; // 第二次检测到还是按下，确认按下
          key_pressed = keypad.key_val[i][j]; // 返回键值
        }
      } else {
        keypad.key_state[i][j] = 0; // 松开，状态清零
      }
    }
  }

  // 扫描完后恢复所有行为高电平
  for (int r = 0; r < MATRIX_ROW_NUM; r++) {
    gpio_bit_set(keypad.rows[r].gpio_periph, keypad.rows[r].pin);
  }

  return key_pressed; // 返回0表示没有按键按下，返回其他值表示按下的键值
}
