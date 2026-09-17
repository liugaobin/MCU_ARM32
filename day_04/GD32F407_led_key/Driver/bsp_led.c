#include "bsp_led.h"

led_t led_list[10] = {
     {GPIOC, GPIO_PIN_6},  // 开关
    {GPIOD, GPIO_PIN_8},  // led1
    {GPIOD, GPIO_PIN_9},  // led2
    {GPIOD, GPIO_PIN_10}, // led3
    {GPIOD, GPIO_PIN_11}, // led4
    {GPIOD, GPIO_PIN_12}, // led5
    {GPIOD, GPIO_PIN_13}, // led6
    {GPIOD, GPIO_PIN_14}, // led7
    {GPIOD, GPIO_PIN_15}, // led8
    {GPIOB, GPIO_PIN_2},  // 板载led
};

void led_init(void) {
  rcu_periph_clock_enable(RCU_GPIOB);
  rcu_periph_clock_enable(RCU_GPIOC);
  rcu_periph_clock_enable(RCU_GPIOD);
  for (int i = 0; i < 10; i++) {
    gpio_mode_set(led_list[i].gpiox, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                  led_list[i].gpio_pin);
    gpio_output_options_set(led_list[i].gpiox, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ,
                            led_list[i].gpio_pin);
  }
  // 将开关关闭为高电平
  gpio_bit_set(GPIOC, GPIO_PIN_6);

  // 初始化所有灯为熄灭状态
  for (int i = 0; i < 10; i++) {
    // 板载led不能亮
    if (i == 9) {
      gpio_bit_reset(led_list[i].gpiox, led_list[i].gpio_pin);
      continue;
    }
    gpio_bit_set(led_list[i].gpiox, led_list[i].gpio_pin);
  }
}

void led_switch() { gpio_bit_toggle(led_list[0].gpiox, led_list[0].gpio_pin); }

void led_on(uint32_t led_index) {
  if (led_index >= 10) {
    return;
  }
  // 开关不能亮
  if (led_index == 0) {
    return;
  }
  if (led_index == 9) {
    gpio_bit_set(led_list[led_index].gpiox, led_list[led_index].gpio_pin);
    return;
  }
  gpio_bit_reset(led_list[led_index].gpiox, led_list[led_index].gpio_pin);
}

void led_off(uint32_t led_index) {
  if (led_index >= 10) {
    return;
  }
  // 开关不能亮
  if (led_index == 0) {
    return;
  }
  if (led_index == 9) {
    gpio_bit_reset(led_list[led_index].gpiox, led_list[led_index].gpio_pin);
    return;
  }
  gpio_bit_set(led_list[led_index].gpiox, led_list[led_index].gpio_pin);
}

void led_open_all(void) {
  for (int i = 1; i < 9; i++) {
    led_on(i);
  }
}

void led_close_all(void) {
  for (int i = 1; i < 9; i++) {
    led_off(i);
  }
}
void led_toggle(uint32_t led_index) {
  gpio_bit_toggle(led_list[led_index].gpiox, led_list[led_index].gpio_pin);
}