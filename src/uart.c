#include "uart.h"
#include "gpio.h"
#include  <errno.h>
#include  <sys/unistd.h>


UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

void uart_init(void){
      __USART2_CLK_ENABLE();
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK){
        Error_Handler();
    }

    __HAL_RCC_DMA1_CLK_ENABLE();
    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK){
      Error_Handler();
    }

    __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);

    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

int _write(int file, char *data, int size){
    if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)){
        errno = EBADF;
        return -1;
    }
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, (uint8_t*)data, size, 1000);
    return (status == HAL_OK ? size : 0);
}

void send_uart(char* data){
    uint16_t size = strlen(data);
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)data, size);
}
