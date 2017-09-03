/*****************************************************************************
* \file      bsp_api.h
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
#ifndef BSP_API_H
#define BSP_API_H

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "Platform_Types.h"

//////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
typedef uint8 Bsp_DigitalState_t;
#define Bsp_DigitalState_Inactive         0
#define Bsp_DigitalState_Active           1
#define Bsp_DigitalState_Error            2
#define Bsp_DigitalState_NotAvailable     3

typedef uint8 Bsp_Result_t;
#define BSP_E_OK                     0
#define BSP_E_FAILURE                1
#define BSP_E_INVALID_ARG            2

typedef uint8 Bsp_DigitalId_t;

//////////////////////////////////////////////////////////////////////////////
// PUBLIC VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////

void Bsp_Init(void);
void Bsp_StartDigitalControl(void);
void Bsp_StopDigitalControl(void);
Bsp_DigitalState_t Bsp_GetDigitalInput(Bsp_DigitalId_t inputId);
Bsp_Result_t Bsp_SetDigitalOutput(Bsp_DigitalId_t outputId, Bsp_DigitalState_t outputValue );



#endif //BSP_API_H
