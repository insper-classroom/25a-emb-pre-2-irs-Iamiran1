#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>


const int LED_PIN_R = 4;
const int BTN_PIN = 28;
volatile int btn_flag_fall = 0;
volatile int btn_flag_rise = 0;


void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    btn_flag_fall = 1;
  } else if (events == 0x8) { // rise edge
    btn_flag_rise = 1;

  }
}


int main() {
  stdio_init_all();
  gpio_init(LED_PIN_R);
  gpio_init(BTN_PIN);

  gpio_set_dir(LED_PIN_R,GPIO_OUT);
  gpio_set_dir(BTN_PIN,GPIO_IN);
  gpio_pull_up(BTN_PIN);
  gpio_set_irq_enabled_with_callback(BTN_PIN,GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE,true , btn_callback);
  while (true) {
    if(btn_flag_fall){
      gpio_put(LED_PIN_R,1);
      btn_flag_fall = 0;

    }
    if(btn_flag_rise){
      gpio_put(LED_PIN_R,0);
      btn_flag_rise = 0;

    }

  }
}
