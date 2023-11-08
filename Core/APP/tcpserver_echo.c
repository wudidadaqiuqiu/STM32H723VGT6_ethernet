#include "tcpecho.h"
#include "lwip/opt.h"
#if LWIP_SOCKET
#include <lwip/sockets.h>
#include "lwip/sys.h"
#include "lwip/api.h"
/*-----------------------------------------------------------------------------------*/
#define RECV_DATA         (1024)
uint8_t echo_recv_data[RECV_DATA] = {0};
#define LOCAL_PORT 5001
static void  
tcpecho_task(void *arg)
{
  int sock = -1,connected;
  char *recv_data;
  struct sockaddr_in server_addr,client_addr;
  socklen_t sin_size;
  int recv_data_len;
 
  printf("Local port:%d\n\n",LOCAL_PORT);
 
  // recv_data = (char *)pvPortMalloc(RECV_DATA);
  recv_data = (char *)echo_recv_data;

  if (recv_data == NULL)
  {
      printf("No memory\n");
      goto __exit;
  }
 
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
      printf("Socket error\n");
      goto __exit;
  }
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(LOCAL_PORT);
  memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
 
  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
  {
      printf("Unable to bind\n");
      goto __exit;
  }
 
  if (listen(sock, 5) == -1)
  {
      printf("Listen error\n");
      goto __exit;
  }
 
  while(1)
  {
    sin_size = sizeof(struct sockaddr_in);
    connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
    printf("new client connected from (%s, %d)\n",
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    {
      int flag = 1;
     
      setsockopt(connected,
                 IPPROTO_TCP,     /* set option at TCP level */
                 TCP_NODELAY,     /* name of option */
                 (void *) &flag,  /* the cast is historical cruft */
                 sizeof(int));    /* length of option value */
    }
   
    while(1)
    {
      recv_data_len = recv(connected, recv_data, RECV_DATA, 0);
     
      if (recv_data_len <= 0)  
        break;
     
      printf("recv %d len data\n",recv_data_len);
     
      write(connected,recv_data,recv_data_len);
     
    }
    if (connected >= 0)  
      closesocket(connected);
   
    connected = -1;
  }
__exit:
  if (sock >= 0) closesocket(sock);
  // if (recv_data) free(recv_data);
  vTaskDelete(NULL);
}
/*-----------------------------------------------------------------------------------*/
TaskHandle_t* tcpecho_init(void)
{
  static uint8_t created_count = 0;
  // sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, 512, 4);
  // printf("tcp_echo Task created %d times\n", (created_count++));
  TaskHandle_t *task_handle = NULL;
  xTaskCreate(
					(TaskFunction_t )tcpecho_task,				/* 任务入口函数 */
					(const char*    )"Server_Echo_Task",				/* 任务名字 */
					( uint32_t) configMINIMAL_STACK_SIZE*2,							/* 任务栈大小 */
					(void *  ) NULL,							/* 任务入口参数 */
					(UBaseType_t ) 1,			/* 任务的优先级 */ 
          // 任务优先级在哪个层面上比较？
					(TaskHandle_t *  ) task_handle		/* 返回的TCB结构体指针 */
					);
  return task_handle;
}
/*-----------------------------------------------------------------------------------*/
#endif