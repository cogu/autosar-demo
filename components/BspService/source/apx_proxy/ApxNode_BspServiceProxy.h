#ifndef APXNODE_BSPSERVICEPROXY_H
#define APXNODE_BSPSERVICEPROXY_H

#include "apx_nodeData.h"
#include "Rte_Type.h"

//////////////////////////////////////////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
void ApxNode_Init_BspServiceProxy(void);
apx_nodeData_t * ApxNode_GetNodeData_BspServiceProxy(void);

Std_ReturnType ApxNode_Read_BspServiceProxy_HomeButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Read_BspServiceProxy_BackButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Read_BspServiceProxy_EnterButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Read_BspServiceProxy_LeftButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Read_BspServiceProxy_RightButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Read_BspServiceProxy_UpButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Read_BspServiceProxy_DownButtonPressed(BspApi_DiscreteState_T *val);
Std_ReturnType ApxNode_Write_BspServiceProxy_HomeButtonLED(BspApi_DiscreteState_T val);
Std_ReturnType ApxNode_Write_BspServiceProxy_BackButtonLED(BspApi_DiscreteState_T val);
Std_ReturnType ApxNode_Write_BspServiceProxy_EnterButtonLED(BspApi_DiscreteState_T val);
Std_ReturnType ApxNode_Write_BspServiceProxy_LeftButtonLED(BspApi_DiscreteState_T val);
Std_ReturnType ApxNode_Write_BspServiceProxy_RightButtonLED(BspApi_DiscreteState_T val);
Std_ReturnType ApxNode_Write_BspServiceProxy_UpButtonLED(BspApi_DiscreteState_T val);
Std_ReturnType ApxNode_Write_BspServiceProxy_DownButtonLED(BspApi_DiscreteState_T val);
void BspServiceProxy_inPortDataWritten(void *arg, apx_nodeData_t *nodeData, uint32_t offset, uint32_t len);

#endif //APXNODE_BSPSERVICEPROXY_H
