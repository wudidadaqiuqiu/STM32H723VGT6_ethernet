#include "tcp_client.h"
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include <lwip/sockets.h>

#define DEST_IP_ADDR0 192
#define DEST_IP_ADDR1 168
#define DEST_IP_ADDR2 8
#define DEST_IP_ADDR3 6
#define DEST_PORT 5001
static void tcp_client(void *arg)
{
  int sock = -1;
  struct sockaddr_in client_addr;
 
  ip4_addr_t ipaddr;
 
  uint8_t send_buf[]= "This is a TCP Client test...\n";
 
  printf("dest IP Addr:%d.%d.%d.%d \t PORT:%d\n\n",      \
          DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT);
 
  //   printf("请将电脑上位机设置为TCP Server.在User/arch/sys_arch.h文件中将目标IP地址修改为您电脑上的IP地址\n\n");
  // printf("client ");
  //   printf("修改对应的宏定义:DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT\n\n");
 
  IP4_ADDR(&ipaddr,DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3);
  while(1)
  {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
      printf("Socket error\n");
      vTaskDelay(10);
      continue;
    }  
    client_addr.sin_family = AF_INET;      
    client_addr.sin_port = htons(DEST_PORT);    
    client_addr.sin_addr.s_addr = ipaddr.addr;
    memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));    
    if (connect(sock,  
               (struct sockaddr *)&client_addr,  
                sizeof(struct sockaddr)) == -1)  
    {
        printf("Connect failed!\n");
        closesocket(sock);
        vTaskDelay(10);
        continue;
    }                                            
   
    printf("Connect to server successful!\n");
   
    while (1)
    {
      if(write(sock,send_buf,sizeof(send_buf)) < 0)
        break;
   
      vTaskDelay(1000);
    }

    closesocket(sock);
  }
  vTaskDelete(NULL);
}

void
TCPClientTaskCreate(void)
{
  // sys_thread_new("client", client, NULL, 512, 4);
  // xTaskCreate(client, "client", 512, NULL, 1, NULL);
  TaskHandle_t handle;
  if(xTaskCreate(
					(TaskFunction_t )tcp_client,				/* 任务入口函数 */
					(const char*    )"TCPClient",				/* 任务名字 */
					( uint32_t) configMINIMAL_STACK_SIZE*2,							/* 任务栈大小 */
					(void *  ) NULL,							/* 任务入口参数 */
					(UBaseType_t ) 1,			/* 任务的优先级 */ 
          // 任务优先级在哪个层面上比较？
					(TaskHandle_t *  ) &handle		/* 返回的TCB结构体指针 */
          ) == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
          printf("FreeRTOS: errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY\n");
  printf("TaskHandle:%ld\n",(uint32_t)&handle);
}