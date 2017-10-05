/*****************************************************************************
* \file      BspServiceProxy.c
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
#include "Rte_BspService.h"
#include "ApxNode_BspServiceProxy.h"
#include "bsp_defs.h"

//////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PUBLIC VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
void BspService_Exit(void)
{

}

void BspService_Init(void)
{

}

void BspService_GetDiscreteInput(BspApi_DiscreteId_T inputId, BspApi_DiscreteState_T *inputValue)
{
   if (inputValue != 0)
   {
      switch(inputId)
      {
      case BSP_DISCRETE_INPUT_ID_SWS_HOME:
         (void) ApxNode_Read_BspServiceProxy_HomeButtonPressed(inputValue);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_BACK:
         (void) ApxNode_Read_BspServiceProxy_BackButtonPressed(inputValue);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_ENTER:
         (void) ApxNode_Read_BspServiceProxy_EnterButtonPressed(inputValue);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_LEFT:
         (void) ApxNode_Read_BspServiceProxy_LeftButtonPressed(inputValue);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_RIGHT:
         (void) ApxNode_Read_BspServiceProxy_RightButtonPressed(inputValue);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_UP:
         (void) ApxNode_Read_BspServiceProxy_UpButtonPressed(inputValue);
         break;
      case BSP_DISCRETE_INPUT_ID_SWS_DOWN:
         (void) ApxNode_Read_BspServiceProxy_DownButtonPressed(inputValue);
         break;
      default:
         *inputValue = BspApi_DiscreteState_NotAvailable;
      }
   }
}

Std_ReturnType BspService_SetDiscreteOutput(BspApi_DiscreteId_T outputId, BspApi_DiscreteState_T outputValue)
{
   Std_ReturnType retval = E_OK;
   switch(outputId)
   {
   case BSP_DISCRETE_INPUT_ID_SWS_HOME:
      (void) ApxNode_Write_BspServiceProxy_HomeButtonLED(outputValue);
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_BACK:
      (void) ApxNode_Write_BspServiceProxy_BackButtonLED(outputValue);
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_ENTER:
      (void) ApxNode_Write_BspServiceProxy_EnterButtonLED(outputValue);
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_LEFT:
      (void) ApxNode_Write_BspServiceProxy_LeftButtonLED(outputValue);
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_RIGHT:
      (void) ApxNode_Write_BspServiceProxy_RightButtonLED(outputValue);
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_UP:
      (void) ApxNode_Write_BspServiceProxy_UpButtonLED(outputValue);
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_DOWN:
      (void) ApxNode_Write_BspServiceProxy_DownButtonLED(outputValue);
      break;
   default:
      retval = E_NOT_OK;
   }
   return retval;
}

//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


