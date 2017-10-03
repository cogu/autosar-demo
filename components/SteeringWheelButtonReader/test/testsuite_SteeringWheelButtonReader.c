//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "MockRte.h"
#include "Rte_SteeringWheelButtonReader.h"
#include "CuTest.h"
#include "bsp_defs.h"



//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////
typedef struct bsp_discreteInputState_tag
{
   BspApi_DiscreteState_T Up;
   BspApi_DiscreteState_T Down;
   BspApi_DiscreteState_T Left;
   BspApi_DiscreteState_T Right;
   BspApi_DiscreteState_T Back;
   BspApi_DiscreteState_T Enter;
   BspApi_DiscreteState_T Home;
} bsp_discreteInputState_t;

#define DEBOUNCE_LIMIT 3

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static void test_setup(void);
static void bspCallHandler_GetDiscreteInput(BspApi_DiscreteId_T inputId, BspApi_DiscreteState_T *inputValue);
static void test_init(CuTest* tc);
static void test_exit(CuTest* tc);
static void test_up(CuTest* tc);
static void test_down(CuTest* tc);
static void test_left(CuTest* tc);
static void test_right(CuTest* tc);

//////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL VARIABLES
//////////////////////////////////////////////////////////////////////////////
bsp_discreteInputState_t m_bsp_discreteInputState;

//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
CuSuite* testsuite_SteeringWheelButtonReader(void)
{
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, test_init);
   SUITE_ADD_TEST(suite, test_exit);
   SUITE_ADD_TEST(suite, test_up);
   SUITE_ADD_TEST(suite, test_down);
   SUITE_ADD_TEST(suite, test_left);
   SUITE_ADD_TEST(suite, test_right);

   return suite;

}

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static void test_init(CuTest* tc)
{
   test_setup();
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus(ButtonStatus_Released);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus(ButtonStatus_Released);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus(ButtonStatus_Released);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus(ButtonStatus_Released);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus(ButtonStatus_Released);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus(ButtonStatus_Released);
   Rte_Write_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus(ButtonStatus_Released);
   SteeringWheelButtonReader_Init();
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_NotAvailable, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
}

static void test_up(CuTest* tc)
{
   uint16 i;
   test_setup();
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());

   //Up
   m_bsp_discreteInputState.Up = BspApi_DiscreteState_Active;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   m_bsp_discreteInputState.Up = BspApi_DiscreteState_Inactive;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
}

static void test_down(CuTest* tc)
{
   uint16 i;
   test_setup();
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());

   //Up
   m_bsp_discreteInputState.Down = BspApi_DiscreteState_Active;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   m_bsp_discreteInputState.Down = BspApi_DiscreteState_Inactive;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
}

static void test_left(CuTest* tc)
{
   uint16 i;
   test_setup();
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());

   //Up
   m_bsp_discreteInputState.Left = BspApi_DiscreteState_Active;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   m_bsp_discreteInputState.Left = BspApi_DiscreteState_Inactive;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
}

static void test_right(CuTest* tc)
{
   uint16 i;
   test_setup();
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());

   //Up
   m_bsp_discreteInputState.Right = BspApi_DiscreteState_Active;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   m_bsp_discreteInputState.Right = BspApi_DiscreteState_Inactive;
   for (i=0;i<DEBOUNCE_LIMIT-1;i++)
   {
      SteeringWheelButtonReader_Run();
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Pressed, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
      CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
   }
   SteeringWheelButtonReader_Run();
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Back_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Down_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Enter_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Home_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Left_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Right_ButtonStatus());
   CuAssertUIntEquals(tc, ButtonStatus_Released, Rte_GetData_SteeringWheelButtonReader_SWS_PushButtonStatus_Up_ButtonStatus());
}

static void test_exit(CuTest* tc)
{

}



static void test_setup(void)
{
   Rte_Start();
   Rte_SetCallHandler_SteeringWheelButtonReader_BspApi_GetDiscreteInput(bspCallHandler_GetDiscreteInput);
   m_bsp_discreteInputState.Up = BspApi_DiscreteState_Inactive;
   m_bsp_discreteInputState.Down = BspApi_DiscreteState_Inactive;
   m_bsp_discreteInputState.Left = BspApi_DiscreteState_Inactive;
   m_bsp_discreteInputState.Right = BspApi_DiscreteState_Inactive;
   m_bsp_discreteInputState.Enter = BspApi_DiscreteState_Inactive;
   m_bsp_discreteInputState.Back = BspApi_DiscreteState_Inactive;
   m_bsp_discreteInputState.Home = BspApi_DiscreteState_Inactive;
}

static void bspCallHandler_GetDiscreteInput(BspApi_DiscreteId_T inputId, BspApi_DiscreteState_T *inputValue)
{
   BspApi_DiscreteState_T result = BspApi_DiscreteState_NotAvailable;
   switch(inputId)
   {
   case BSP_DISCRETE_INPUT_ID_SWS_LEFT:
      result = m_bsp_discreteInputState.Left;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_RIGHT:
      result = m_bsp_discreteInputState.Right;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_UP:
      result = m_bsp_discreteInputState.Up;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_DOWN:
      result = m_bsp_discreteInputState.Down;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_ENTER:
      result = m_bsp_discreteInputState.Enter;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_BACK:
      result = m_bsp_discreteInputState.Back;
      break;
   case BSP_DISCRETE_INPUT_ID_SWS_HOME:
      result = m_bsp_discreteInputState.Home;
      break;
   }
   if (inputValue != 0)
   {
      *inputValue = result;
   }
}

