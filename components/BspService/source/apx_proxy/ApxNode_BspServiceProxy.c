//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdio.h>
#include "ApxNode_BspServiceProxy.h"
#include "pack.h"

//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
#define APX_DEFINITON_LEN 555u
#define APX_IN_PORT_DATA_LEN 7u
#define APX_OUT_PORT_DATA_LEN 7u
//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static void outPortData_writeCmd(apx_offset_t offset, apx_size_t len );
//////////////////////////////////////////////////////////////////////////////
// LOCAL VARIABLES
//////////////////////////////////////////////////////////////////////////////
static const uint8_t m_outPortInitData[APX_OUT_PORT_DATA_LEN]= {
   3, 3, 3, 3, 3, 3, 3
};

static uint8 m_outPortdata[APX_OUT_PORT_DATA_LEN];
static uint8_t m_outPortDirtyFlags[APX_OUT_PORT_DATA_LEN];
static const uint8_t m_inPortInitData[APX_IN_PORT_DATA_LEN]= {
   3, 3, 3, 3, 3, 3, 3
};

static uint8 m_inPortdata[APX_IN_PORT_DATA_LEN];
static uint8_t m_inPortDirtyFlags[APX_OUT_PORT_DATA_LEN];
static apx_nodeData_t m_nodeData;
static const char *m_apxDefinitionData=
"APX/1.2\n"
"N\"BspServiceProxy\"\n"
"T\"BspApi_DiscreteState_T\"C(0,3):VT(\"BspApi_DiscreteState_Inactive\",\"BspApi_DiscreteState_Active\",\"BspApi_DiscreteState_Error\",\"BspApi_DiscreteState_NotAvailable\")\n"
"P\"HomeButtonLED\"T[0]:=3\n"
"P\"BackButtonLED\"T[0]:=3\n"
"P\"EnterButtonLED\"T[0]:=3\n"
"P\"LeftButtonLED\"T[0]:=3\n"
"P\"RightButtonLED\"T[0]:=3\n"
"P\"UpButtonLED\"T[0]:=3\n"
"P\"DownButtonLED\"T[0]:=3\n"
"R\"HomeButtonPressed\"T[0]:=3\n"
"R\"BackButtonPressed\"T[0]:=3\n"
"R\"EnterButtonPressed\"T[0]:=3\n"
"R\"LeftButtonPressed\"T[0]:=3\n"
"R\"RightButtonPressed\"T[0]:=3\n"
"R\"UpButtonPressed\"T[0]:=3\n"
"R\"DownButtonPressed\"T[0]:=3\n"
"\n";

//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
void ApxNode_Init_BspServiceProxy(void)
{
   memcpy(&m_inPortdata[0], &m_inPortInitData[0], APX_IN_PORT_DATA_LEN);
   memset(&m_inPortDirtyFlags[0], 0, sizeof(m_inPortDirtyFlags));
   memcpy(&m_outPortdata[0], &m_outPortInitData[0], APX_OUT_PORT_DATA_LEN);
   memset(&m_outPortDirtyFlags[0], 0, sizeof(m_outPortDirtyFlags));
   apx_nodeData_create(&m_nodeData, "BspServiceProxy", (uint8_t*) &m_apxDefinitionData[0], APX_DEFINITON_LEN, &m_inPortdata[0], &m_inPortDirtyFlags[0], APX_IN_PORT_DATA_LEN, &m_outPortdata[0], &m_outPortDirtyFlags[0], APX_OUT_PORT_DATA_LEN);
#ifdef APX_POLLED_DATA_MODE
   rbfs_create(&m_outPortDataCmdQueue, &m_outPortDataCmdBuf[0], APX_NUM_OUT_PORTS, APX_DATA_WRITE_CMD_SIZE);
#endif
}

apx_nodeData_t * ApxNode_GetNodeData_BspServiceProxy(void)
{
   return &m_nodeData;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_HomeButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[0];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_BackButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[1];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_EnterButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[2];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_LeftButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[3];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_RightButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[4];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_UpButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[5];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Read_BspServiceProxy_DownButtonPressed(BspApi_DiscreteState_T *val)
{
   apx_nodeData_lockInPortData(&m_nodeData);
   *val = (uint8) m_inPortdata[6];
   apx_nodeData_unlockInPortData(&m_nodeData);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_HomeButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[0]=(uint8) val;
   outPortData_writeCmd(0, 1);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_BackButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[1]=(uint8) val;
   outPortData_writeCmd(1, 1);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_EnterButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[2]=(uint8) val;
   outPortData_writeCmd(2, 1);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_LeftButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[3]=(uint8) val;
   outPortData_writeCmd(3, 1);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_RightButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[4]=(uint8) val;
   outPortData_writeCmd(4, 1);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_UpButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[5]=(uint8) val;
   outPortData_writeCmd(5, 1);
   return E_OK;
}

Std_ReturnType ApxNode_Write_BspServiceProxy_DownButtonLED(BspApi_DiscreteState_T val)
{
   apx_nodeData_lockOutPortData(&m_nodeData);
   m_outPortdata[6]=(uint8) val;
   outPortData_writeCmd(6, 1);
   return E_OK;
}

void BspServiceProxy_inPortDataWritten(void *arg, apx_nodeData_t *nodeData, uint32_t offset, uint32_t len)
{

}
//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static void outPortData_writeCmd(apx_offset_t offset, apx_size_t len )
{
   if ( (m_outPortDirtyFlags[offset] == 0) && (true == apx_nodeData_isOutPortDataOpen(&m_nodeData) ) )
   {
      m_outPortDirtyFlags[offset] = (uint8_t) 1u;
      apx_nodeData_unlockOutPortData(&m_nodeData);
      apx_nodeData_outPortDataNotify(&m_nodeData, (uint32_t) offset, (uint32_t) len);
      return;
   }
   apx_nodeData_unlockOutPortData(&m_nodeData);
}



