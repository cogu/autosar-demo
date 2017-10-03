/*****************************************************************************
* \file      BspServiceTypes.h
* \author    Conny Gustafsson
* \date      2017-10-01
* \brief     BSP Types and IDs
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
#ifndef BSP_SERVICE_TYPES_H
#define BSP_SERVICE_TYPES_H

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "Rte_Type.h"

//////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
#define BSP_DISCRETE_INPUT_ID_SWS_LEFT    ((BspApi_DiscreteId_T) 0u)
#define BSP_DISCRETE_INPUT_ID_SWS_RIGHT   ((BspApi_DiscreteId_T) 1u)
#define BSP_DISCRETE_INPUT_ID_SWS_UP      ((BspApi_DiscreteId_T) 2u)
#define BSP_DISCRETE_INPUT_ID_SWS_DOWN    ((BspApi_DiscreteId_T) 3u)
#define BSP_DISCRETE_INPUT_ID_SWS_ENTER   ((BspApi_DiscreteId_T) 4u)
#define BSP_DISCRETE_INPUT_ID_SWS_BACK    ((BspApi_DiscreteId_T) 5u)
#define BSP_DISCRETE_INPUT_ID_SWS_HOME    ((BspApi_DiscreteId_T) 6u)
#define NUM_BSP_DISCRETE_INPUTS           7u

//////////////////////////////////////////////////////////////////////////////
// PUBLIC VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////


#endif //BSP_SERVICE_TYPES_H
