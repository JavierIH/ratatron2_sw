#include "main.h"
#include "clock.h"
#include "timer.h"
//#include "dma.h"
#include "uart.h"
#include "gpio.h"


void SystemClock_Config(void);
void Error_Handler(void);

int main(void){
    HAL_Init();
    SystemClock_Config();

    gpio_init();
    //dma_init();
    uart_init();
    //MX_TIM1_Init();
    //MX_TIM2_Init();
    //MX_TIM3_Init();
    //MX_TIM5_Init();
    //MX_USART2_UART_Init();
    //HAL_TIM_Base_Start(&htim5);

    char text_buffer[1000];
    for(int i=0; i<1000; i++){
        text_buffer[i]='X';
    }
    text_buffer[996]='\r';
    text_buffer[997]='\n';
    text_buffer[998]='\n';
    text_buffer[999]='\n';
    while(1){
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
        //sprintf(text_buffer,"IR T\n\r"); send_uart(text_buffer);
        //printf("ok\n");
        //sprintf(text_buffer,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\r\n");
        send_uart(text_buffer);
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

        HAL_Delay(100);
    }
}



void SysTick_Handler(void){
    HAL_IncTick();
    //HAL_SYSTICK_IRQHandler();
}

void Error_Handler(void){while(1);}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line){}

#endif
