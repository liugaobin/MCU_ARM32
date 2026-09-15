
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

//PB8  推挽
void Monter_GPIO_config(void){
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOB);
	//2.配置GPIO模式 输出
	gpio_mode_set(GPIOB,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_8);
	//3.输出需要配置  输出模式
	gpio_output_options_set(GPIOB,GPIO_OTYPE_PP,GPIO_OSPEED_2MHZ,GPIO_PIN_8);
}

void KEY_GPIO_config(void){
	//1.打开时钟
	rcu_periph_clock_enable(RCU_GPIOC);
	//2.配置GPIO模式 上拉输入
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_0);
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_1);
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_2);
	gpio_mode_set(GPIOC,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP,GPIO_PIN_3);
}


// PB9 配置为 TIMER1_CH1 PWM 输出
void BUZZER_PWM_config(void)
{
    // 1. 打开 GPIOB 和 TIMER1 时钟
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_TIMER1);

    // 2. PB9 配置为复用推挽输出，复用功能为 AF1
    // 注意：这里使用 GPIO_AF_1
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_9); // 图中 PB9 复用 AF1 对应 TIMER1_CH1

    // 3. 定时器基础配置
    timer_parameter_struct timer_initpara;
    timer_struct_para_init(&timer_initpara);
    
    // 假设 TIMER1 时钟为 200MHz (APB2 定时器)
    // 分频系数 199，得到 1MHz 计数频率
    timer_initpara.prescaler        = 199;         
    timer_initpara.alignedmode      = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    // 周期 333，1MHz / 333 ≈ 3003Hz (3kHz，适合无源蜂鸣器)
    timer_initpara.period           = 333;         
    timer_initpara.clockdivision    = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1, &timer_initpara);

    // 4. 输出比较配置 (通道1)
    timer_oc_parameter_struct timer_ocintpara;
    timer_channel_output_struct_para_init(&timer_ocintpara);
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);

    // 5. 设置占空比 50% (333/2 = 166)
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 166);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    // 6. 使能自动重载影子，启动定时器
    timer_auto_reload_shadow_enable(TIMER1);
    timer_enable(TIMER1);
    
    // 初始静音：占空比设为 0
    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0);
}


// 矩阵按键初始化



 
uint16_t buzzer_period = 333; // 初始周期
int main(void)
{
		//系统滴答时钟初始化
    systick_config();
	
		//GPIO初始化
			LED_GPIO_config();
			KEY_GPIO_config();
			Monter_GPIO_config();
			BUZZER_PWM_config();
	   // 设置初始状态 
	   FlagStatus preState = SET;
	   FlagStatus monterPreState = SET;
	   FlagStatus buzzer_reduct_state = SET;
	   FlagStatus buzzer_add_state = SET;
	  
	
    while(1) {
			FlagStatus currState = gpio_input_bit_get(GPIOC,GPIO_PIN_0);
			FlagStatus moterState = gpio_input_bit_get(GPIOC,GPIO_PIN_1);
			if(preState == SET && currState == RESET){
			
				//拉高PC0
			gpio_bit_set(GPIOB,GPIO_PIN_2);
				preState = currState;
			} else if (preState == RESET && currState == SET) {
			
			//拉低PC0
			gpio_bit_reset(GPIOB,GPIO_PIN_2);
				preState = currState;
			}
			
		if(monterPreState == SET && moterState == RESET){ 
				//拉高PB8
			   gpio_bit_set(GPIOB,GPIO_PIN_8);
				monterPreState = moterState;
			} else if (monterPreState == RESET && moterState == SET) {
			
			//拉低PB8
			   gpio_bit_reset(GPIOB,GPIO_PIN_8);
				monterPreState = moterState;
			}
			
		     FlagStatus buzzer_reduct_now_state = gpio_input_bit_get(GPIOC, GPIO_PIN_2); 
			
			
			   if (buzzer_reduct_state == SET && buzzer_reduct_now_state == RESET) {
					if (buzzer_period > 249) {  
							buzzer_period -= 30;
					}
					timer_autoreload_value_config(TIMER1, buzzer_period);
					timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, buzzer_period / 2); 
				 
			  }else if (buzzer_reduct_state ==RESET   && buzzer_reduct_now_state == SET ) { 
				 timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0); 
				}
			   buzzer_reduct_state =  buzzer_reduct_now_state; 
			   FlagStatus buzzer_add_now_state = gpio_input_bit_get(GPIOC, GPIO_PIN_3);  
			 
			    if (buzzer_add_state == SET && buzzer_add_now_state == RESET) {
					if (buzzer_period < 499) {  
							buzzer_period += 30;
					}
					timer_autoreload_value_config(TIMER1, buzzer_period);
					timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, buzzer_period / 2);
					 
			  } else if (buzzer_add_state ==RESET   && buzzer_add_now_state == SET ){
					timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0);
				}
				buzzer_add_state =  buzzer_add_now_state;  
    }
}
