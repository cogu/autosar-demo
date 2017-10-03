/*****************************************************************************
* \file      SteeringWheelButtonReader.c
* \author    Conny Gustafsson
* \date      2017-09-04
* \brief     SteeringWheelButtonReader
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
#include "Rte_SteeringWheelButtonReader.h"
#include "bsp_defs.h"

//////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
#define DEBOUNCE_LIMIT 3
typedef struct debouncedState_tag
{
   ButtonStatus_T status;
   uint8 count;
}debouncedState_t;
//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static ButtonStatus_T translateDiscreteInput(BspApi_DiscreteState_T inputState);
static void updateDebouncedButtonState(debouncedState_t *debounced, ButtonStatus_T newButtonStatus);

//////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
//////////////////////////////////////////////////////////////////////////////
debouncedState_t m_debouncedState[NUM_BSP_DISCRETE_INPUTS];

//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
void SteeringWheelButtonReader_Exit(void)
{
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus(ButtonStatus_NotAvailable);

}

void SteeringWheelButtonReader_Init(void)
{
   uint16 i;
   for (i=0; i<NUM_BSP_DISCRETE_INPUTS; i++)
   {
      m_debouncedState[i].status = BspApi_DiscreteState_Inactive;
      m_debouncedState[i].count = 0;
   }
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus(ButtonStatus_NotAvailable);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus(ButtonStatus_NotAvailable);
}

void SteeringWheelButtonReader_Run(void)
{
   const BspApi_DiscreteId_T idList[NUM_BSP_DISCRETE_INPUTS] = {
         BSP_DISCRETE_INPUT_ID_SWS_LEFT,
         BSP_DISCRETE_INPUT_ID_SWS_RIGHT,
         BSP_DISCRETE_INPUT_ID_SWS_UP,
         BSP_DISCRETE_INPUT_ID_SWS_DOWN,
         BSP_DISCRETE_INPUT_ID_SWS_ENTER,
         BSP_DISCRETE_INPUT_ID_SWS_BACK,
         BSP_DISCRETE_INPUT_ID_SWS_HOME
   };
   uint16 i;

   for (i = 0; i<NUM_BSP_DISCRETE_INPUTS; i++)
   {
      BspApi_DiscreteState_T inputState;
      BspApi_DiscreteId_T id = idList[i];
      Rte_Call_SteeringWheelButtonReader_BspApi_GetDiscreteInput(id, &inputState);
      ButtonStatus_T newState = translateDiscreteInput(inputState);
      updateDebouncedButtonState(&m_debouncedState[i], newState);
   }
   for (i = 0; i<NUM_BSP_DISCRETE_INPUTS; i++)
   {
      BspApi_DiscreteId_T id = idList[i];
      ButtonStatus_T buttonStatus = m_debouncedState[i].status;
      switch(id)
      {
      case BSP_DISCRETE_INPUT_ID_SWS_LEFT:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus(buttonStatus);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_RIGHT:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus(buttonStatus);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_UP:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus(buttonStatus);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_DOWN:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus(buttonStatus);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_ENTER:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus(buttonStatus);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_BACK:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus(buttonStatus);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_HOME:
         Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus(buttonStatus);
         break;
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static ButtonStatus_T translateDiscreteInput(BspApi_DiscreteState_T inputState)
{
   ButtonStatus_T retval;
   if (inputState == BspApi_DiscreteState_Inactive)
   {
      retval = ButtonStatus_Released;
   }
   else if (inputState == BspApi_DiscreteState_Active)
   {
      retval = ButtonStatus_Pressed;
   }
   else if (inputState == BspApi_DiscreteState_Error)
   {
      retval = ButtonStatus_Error;
   }
   else
   {
      retval = ButtonStatus_NotAvailable;
   }
   return retval;
}

static void updateDebouncedButtonState(debouncedState_t *debounced, ButtonStatus_T newButtonStatus)
{
   if (debounced->status == newButtonStatus)
   {
      debounced->count = 0;
   }
   else
   {
      if (++debounced->count >= DEBOUNCE_LIMIT )
      {
         debounced->status = newButtonStatus;
         debounced->count = 0;
      }
   }
}


