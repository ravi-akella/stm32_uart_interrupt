

#include <stdarg.h>
#include <stdint.h>


#include "stm32f4xx_hal.h"
extern UART_HandleTypeDef huart2;


static char uart_buffer[1024];
static uint32_t UartErrCnt=0;


int uart_vprintf(const char *msg, va_list ap){
    int n;
    int status;

    n=vsnprintf(uart_buffer, sizeof(uart_buffer),  msg, ap);
    status = HAL_UART_Transmit(&huart2, (uint8_t*)uart_buffer, n, 10000 );
    if( status ){
        UartErrCnt++;

    }

    return n;
}


int puts(const char *msg){

    int n;
    int status;

    n=strlen(msg);
    status = HAL_UART_Transmit(&huart2, (uint8_t*)msg, n, 10000 );
    if( status ){
        UartErrCnt++;

    }

    return n;
}
int printf(const char *msg, ...){
	va_list ap;
    int n;
    va_start(ap, msg);
    n=uart_vprintf(msg, ap);
    va_end(ap);
    return n;
}

