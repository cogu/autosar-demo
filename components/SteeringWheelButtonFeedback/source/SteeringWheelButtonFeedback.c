/*****************************************************************************
* \file      SteeringWheelButtonFeedback.c
* \author    Conny Gustafsson
* \date      2017-10-05
* \brief     Description
*
* Copyright (c) 2017 Conny Gustafsson
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
******************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "Rte_SteeringWheelButtonFeedback.h"
#include "bsp_defs.h"

//////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
#define HOME             0
#define BACK             1
#define ENTER            2
#define LEFT             3
#define RIGHT            4
#define UP               5
#define DOWN             6
#define NUM_INTERNAL_ID  7
//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static BspApi_DiscreteState_T translateButtonStatus(ButtonStatus_T status, Std_ReturnType readResult);
static void updateDiscreteStatus(uint8 internalId, BspApi_DiscreteId_T bspId, BspApi_DiscreteState_T state);

//////////////////////////////////////////////////////////////////////////////
// PUBLIC VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
//////////////////////////////////////////////////////////////////////////////
BspApi_DiscreteState_T m_discreteState[NUM_INTERNAL_ID];
//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
void SteeringWheelButtonFeedback_Init(void)
{
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_HOME, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_BACK, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_ENTER, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_LEFT, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_RIGHT, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_UP, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_DOWN, BspApi_DiscreteState_Inactive);
   m_discreteState[HOME] = BspApi_DiscreteState_Inactive;
   m_discreteState[BACK] = BspApi_DiscreteState_Inactive;
   m_discreteState[ENTER] = BspApi_DiscreteState_Inactive;
   m_discreteState[LEFT] = BspApi_DiscreteState_Inactive;
   m_discreteState[RIGHT] = BspApi_DiscreteState_Inactive;
   m_discreteState[UP] = BspApi_DiscreteState_Inactive;
   m_discreteState[DOWN] = BspApi_DiscreteState_Inactive;
}

void SteeringWheelButtonFeedback_Exit(void)
{
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_HOME, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_BACK, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_ENTER, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_LEFT, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_RIGHT, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_UP, BspApi_DiscreteState_Inactive);
   Rte_Call_BspApi_SetDiscreteOutput(BSP_DISCRETE_OUTPUT_ID_LED_DOWN, BspApi_DiscreteState_Inactive);
}


void SteeringWheelButtonFeedback_Run(void)
{
   Std_ReturnType result;
   BspApi_DiscreteState_T discreteState;
   ButtonStatus_T ButtonStatus;

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Home_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(HOME, BSP_DISCRETE_OUTPUT_ID_LED_HOME, discreteState);

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Back_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(BACK, BSP_DISCRETE_OUTPUT_ID_LED_BACK, discreteState);

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Enter_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(ENTER, BSP_DISCRETE_OUTPUT_ID_LED_ENTER, discreteState);

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Left_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(LEFT, BSP_DISCRETE_OUTPUT_ID_LED_LEFT, discreteState);

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Right_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(RIGHT, BSP_DISCRETE_OUTPUT_ID_LED_RIGHT, discreteState);

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Up_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(UP, BSP_DISCRETE_OUTPUT_ID_LED_UP, discreteState);

   result = Rte_Read_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Down_ButtonStatus(&ButtonStatus);
   discreteState = translateButtonStatus(ButtonStatus, result);
   updateDiscreteStatus(DOWN, BSP_DISCRETE_OUTPUT_ID_LED_DOWN, discreteState);

}


//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static BspApi_DiscreteState_T translateButtonStatus(ButtonStatus_T status, Std_ReturnType readResult)
{
   BspApi_DiscreteState_T retval;
   if (readResult != RTE_E_OK)
   {
      status = ButtonStatus_Error;
   }
   switch(status)
   {
   case ButtonStatus_Released:
      retval = BspApi_DiscreteState_Inactive;
      break;
   case ButtonStatus_Pressed:
      retval = BspApi_DiscreteState_Active;
      break;
   case ButtonStatus_Error:
      retval = BspApi_DiscreteState_Error;
      break;
   default:
      retval = BspApi_DiscreteState_Inactive;
   }
   return retval;
}

static void updateDiscreteStatus(uint8 internalId, BspApi_DiscreteId_T bspId, BspApi_DiscreteState_T state)
{
   if (state != m_discreteState[internalId])
   {
      m_discreteState[internalId] = state;
      Rte_Call_BspApi_SetDiscreteOutput(bspId, state);
   }
}

