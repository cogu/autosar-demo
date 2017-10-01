//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "MockRte.h"
#include "Rte_SteeringWheelButtonReader.h"
#include "CuTest.h"



//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static void test_init(CuTest* tc);

//////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL VARIABLES
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
CuSuite* testsuite_SteeringWheelButtonReader(void)
{
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, test_init);

   return suite;

}

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static void test_init(CuTest* tc)
{
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

