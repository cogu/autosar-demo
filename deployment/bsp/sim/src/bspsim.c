/*****************************************************************************
* \file      bspsim.c
* \author    Conny Gustafsson
* \date      2017-09-03
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
#include <string.h>
#include "bspsim.h"

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
static Bsp_DigitalState_t m_digitalInState[BSP_DIGITAL_IN_UPPER_LIMIT+1];
static Bsp_DigitalState_t m_digitalOutState[BSP_DIGITAL_OUT_UPPER_LIMIT+1];
//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
void Bsp_Init(void)
{
   memset(&m_digitalInState[0], Bsp_DigitalState_NotAvailable, sizeof(m_digitalInState));
   memset(&m_digitalOutState[0], Bsp_DigitalState_NotAvailable, sizeof(m_digitalOutState));
}

void Bsp_StartDigitalControl(void)
{
   memset(&m_digitalInState[0], Bsp_DigitalState_Inactive, sizeof(m_digitalInState));
   memset(&m_digitalOutState[0], Bsp_DigitalState_Inactive, sizeof(m_digitalOutState));
}

void Bsp_StopDigitalControl(void)
{
   memset(&m_digitalInState[0], Bsp_DigitalState_NotAvailable, sizeof(m_digitalInState));
   memset(&m_digitalOutState[0], Bsp_DigitalState_NotAvailable, sizeof(m_digitalOutState));
}

Bsp_DigitalState_t Bsp_GetDigitalInput(Bsp_DigitalId_t inputId)
{
   if (inputId<=BSP_DIGITAL_IN_UPPER_LIMIT)
   {
      return m_digitalInState[inputId];
   }
   return Bsp_DigitalState_NotAvailable;
}

Bsp_Result_t Bsp_SetDigitalOutput(Bsp_DigitalId_t outputId, Bsp_DigitalState_t outputValue )
{
   if ( (outputId<=BSP_DIGITAL_OUT_UPPER_LIMIT) && (outputValue < Bsp_DigitalState_Error) )
   {
      m_digitalOutState[outputId] = outputValue;
      return BSP_E_OK;
   }
   return BSP_E_INVALID_ARG;
}

Bsp_Result_t BspSim_SetDigitalInput(Bsp_DigitalId_t inputId, Bsp_DigitalState_t inputValue)
{
   if ( (inputId<=BSP_DIGITAL_IN_UPPER_LIMIT) && (inputValue < Bsp_DigitalState_Error) )
   {
      m_digitalInState[inputId] = inputValue;
      return BSP_E_OK;
   }
   return BSP_E_INVALID_ARG;
}

Bsp_DigitalState_t BspSim_GetDigitalOutput(Bsp_DigitalId_t outputId)
{
   if (outputId<=BSP_DIGITAL_OUT_UPPER_LIMIT)
   {
      return m_digitalOutState[outputId];
   }
   return Bsp_DigitalState_NotAvailable;
}


//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


