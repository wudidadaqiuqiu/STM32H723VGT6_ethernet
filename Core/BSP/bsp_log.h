#ifndef _BSP_LOG_H
#define _BSP_LOG_H


void print_log(const char * sFormat, ...);
void segger_rtt_init(char * str);

#endif