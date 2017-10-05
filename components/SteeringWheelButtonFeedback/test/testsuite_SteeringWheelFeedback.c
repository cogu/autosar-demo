/*****************************************************************************
* \file      testsuite_SteeringWheelFeedback.c
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
#include "MockRte.h"
#include "CuTest.h"
#include "bsp_defs.h"

//////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
typedef struct bsp_discreteOutputState_tag
{
   BspApi_DiscreteState_T Up;
   BspApi_DiscreteState_T Down;
   BspApi_DiscreteState_T Left;
   BspApi_DiscreteState_T Right;
   BspApi_DiscreteState_T Back;
   BspApi_DiscreteState_T Enter;
   BspApi_DiscreteState_T Home;
} bsp_discreteOutputState_t;

//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static void test_setup(void);
Std_ReturnType bspCallHandler_SetDiscreteOutput(BspApi_DiscreteId_T outputId, BspApi_DiscreteState_T outputValue);
static void test_init(CuTest* tc);
static void test_exit(CuTest* tc);
static void test_run(CuTest* tc);
//////////////////////////////////////////////////////////////////////////////
// PUBLIC VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
//////////////////////////////////////////////////////////////////////////////
bsp_discreteOutputState_t m_bsp_discreteOutputState;
//////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
CuSuite* testsuite_SteeringWheelButtonFeedback(void)
{
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, test_init);
   SUITE_ADD_TEST(suite, test_exit);
   SUITE_ADD_TEST(suite, test_run);

   return suite;

}

Std_ReturnType bspCallHandler_SetDiscreteOutput(BspApi_DiscreteId_T outputId, BspApi_DiscreteState_T outputValue)
{
   switch(outputId)
   {
   case BSP_DISCRETE_INPUT_ID_SWS_HOME:
      m_bsp_discreteOutputState.Home = outputValue;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_BACK:
      m_bsp_discreteOutputState.Back = outputValue;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_ENTER:
      m_bsp_discreteOutputState.Enter = outputValue;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_LEFT:
      m_bsp_discreteOutputState.Left = outputValue;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_RIGHT:
      m_bsp_discreteOutputState.Right = outputValue;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_UP:
      m_bsp_discreteOutputState.Up = outputValue;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_DOWN:
      m_bsp_discreteOutputState.Down = outputValue;
      break;
   default:
      return RTE_E_INVALID;
   }
   return RTE_E_OK;
}


//////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
//////////////////////////////////////////////////////////////////////////////

static void test_setup(void)
{
   Rte_Start();
   Rte_SetCallHandler_SteeringWheelButtonFeedback_BspApi_SetDiscreteOutput(bspCallHandler_SetDiscreteOutput);
   m_bsp_discreteOutputState.Up = BspApi_DiscreteState_NotAvailable;
   m_bsp_discreteOutputState.Down = BspApi_DiscreteState_NotAvailable;
   m_bsp_discreteOutputState.Left = BspApi_DiscreteState_NotAvailable;
   m_bsp_discreteOutputState.Right = BspApi_DiscreteState_NotAvailable;
   m_bsp_discreteOutputState.Enter = BspApi_DiscreteState_NotAvailable;
   m_bsp_discreteOutputState.Back = BspApi_DiscreteState_NotAvailable;
   m_bsp_discreteOutputState.Home = BspApi_DiscreteState_NotAvailable;

}

Std_ReturnType bspCallHandler_SetDiscreteOutput(BspApi_DiscreteId_T outputId, BspApi_DiscreteState_T outputValue);
static void test_init(CuTest* tc)
{
   test_setup();
   SteeringWheelButtonFeedback_Init();
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Up);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Down);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Left);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Right);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Home);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Back);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Enter);
}

static void test_exit(CuTest* tc)
{
   test_setup();
   SteeringWheelButtonFeedback_Exit();
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Up);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Down);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Left);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Right);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Home);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Back);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Enter);
}

static void test_run(CuTest* tc)
{
   test_setup();
   SteeringWheelButtonFeedback_Init();
   Rte_SetReadData_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Home_ButtonStatus(ButtonStatus_Released);
   SteeringWheelButtonFeedback_Run();
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Up);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Down);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Left);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Right);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Home);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Back);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Enter);

   Rte_SetReadData_SteeringWheelButtonFeedback_SWS_PushButtonStatus_Home_ButtonStatus(ButtonStatus_Pressed);
   SteeringWheelButtonFeedback_Run();
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Up);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Down);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Left);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Right);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Active, m_bsp_discreteOutputState.Home);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Back);
   CuAssertUIntEquals(tc, BspApi_DiscreteState_Inactive, m_bsp_discreteOutputState.Enter);

}
