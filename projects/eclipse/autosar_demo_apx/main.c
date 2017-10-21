#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "systime.h"
#include "os.h"
#include "RteApi.h"
#include "osmacro.h"
#include "ApxNode_BspServiceProxy.h"
#include "ApxNode_ApxCom.h"
#include "apx_client.h"

int main(int argc, char **argv)
{
   uint16_t default_tcp_port = 5000;
   const char *default_tcp_address = "127.0.0.1";
   static apx_client_t m_client;

   ApxNode_Init_ApxCom();
   ApxNode_Init_BspServiceProxy();
   apx_client_create(&m_client);
   apx_client_attachLocalNode(&m_client, ApxNode_GetNodeData_ApxCom());
   apx_client_attachLocalNode(&m_client, ApxNode_GetNodeData_BspServiceProxy());

   printf("connecting...\n");
   apx_client_connect_tcp(&m_client, default_tcp_address, default_tcp_port);

   Rte_Start();
   SysTime_init(1);
   os_init(&g_os_cfg);
   os_start();
   Rte_SetMode_EcuM_Mode(RTE_MODE_EcuM_Mode_RUN);

   for(;;)
   {
      SLEEP(1000);
   }
   os_stop();
   os_shutdown();
   return 0;
}
