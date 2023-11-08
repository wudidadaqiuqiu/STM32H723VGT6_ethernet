#include "stdio.h"
#include "string.h"
#include "bsp_log.h"
/* segger rtt includes. */
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

#define BUFFER_INDEX 0

/*!
* @brief 封装 RTT 打印接口
*        执行条件：无
*
* @retval: 无
*/
void print_log(const char * sFormat, ...)
{	
	va_list ParamList;
	va_start(ParamList, sFormat);
	SEGGER_RTT_vprintf(BUFFER_INDEX, sFormat, &ParamList);
	va_end(ParamList);
}

/*!
* @brief 初始化 RTT 打印接口
*        执行条件：无
*
* @retval: 无
*/
void segger_rtt_init(char * str)
{
	SEGGER_RTT_Init();
	print_log(str);  // 封装接口，无需填写 BUFFER_INDEX
}

// #include <stdio.h>
// int fputc(int ch, FILE* stream)
// {
//     //USART_SendData(USART1, (unsigned char) ch);
//     //while (!(USART1->SR & USART_FLAG_TXE));
//     // USART_SendChar(USART1, (uint8_t)ch);
// 	// print_log((const char*)&ch);
// 	print_log("1\n");
//     return ch;
// }

int _write(int fd, char *ch, int len)
{
//   HAL_UART_Transmit(&huart1, (uint8_t*)ch, len, 0xFFFF);
	// uint8_t c[2];
	// c[0] = *ch;
	// c[1] = '\0';
	// memcpy(www, ch, len);
	// print_log((const char *)c);
	
	char* p = (char*)calloc(len+1, sizeof(uint8_t));
	memcpy(p, ch, len);
	print_log(p);
	free(p);
	return len;
}
