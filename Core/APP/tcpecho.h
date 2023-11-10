#ifndef _TCPSERVER_ECHO_H
#define _TCPSERVER_ECHO_H
#include "cmsis_os.h"

TaskHandle_t tcpecho_init(void);
extern char RunTimeInfo[400];

#endif