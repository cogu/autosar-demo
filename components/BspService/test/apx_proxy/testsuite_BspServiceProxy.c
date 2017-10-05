//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "MockRte.h"
#include "Rte_BspService.h"
#include "CuTest.h"
#include "bsp_defs.h"
#include "ApxNode_BspServiceProxy.h"


//////////////////////////////////////////////////////////////////////////////
// CONSTANTS AND DATA TYPES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////////////
static void setup(CuTest *tc);
static void test_buttons(CuTest *tc);
static void test_output_leds(CuTest *tc);


//////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LOCAL VARIABLES
//////////////////////////////////////////////////////////////////////////////
static uint8_t *m_inPortDataBuf;
static uint8_t *m_outPortDataBuf;
//////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
CuSuite* testsuite_BspServiceProxy(void)
{
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, test_buttons);
   SUITE_ADD_TEST(suite, test_output_leds);
   return suite;

}

//////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
static void setup(CuTest *tc)
{
   ApxNode_Init_BspServiceProxy();
   BspService_Init();
   apx_nodeData_t *nodeData = ApxNode_GetNodeData_BspServiceProxy();
   CuAssertPtrNotNull(tc, nodeData);
   CuAssertIntEquals(tc, NUM_BSP_DISCRETE_INPUTS, nodeData->inPortDataLen);
   CuAssertIntEquals(tc, NUM_BSP_DISCRETE_OUTPUTS, nodeData->outPortDataLen);
   m_inPortDataBuf = nodeData->inPortDataBuf;
   m_outPortDataBuf = nodeData->outPortDataBuf;

}

static void test_buttons(CuTest *tc)
{
   uint8_t i;
   setup(tc);
   for (i=0; i < NUM_BSP_DISCRETE_INPUTS; i++)
   {
      BspApi_DiscreteState_T state;
      m_inPortDataBuf[i] = 0;
      BspService_GetDiscreteInput(i, &state);
      CuAssertUIntEquals(tc, 0, state);
      m_inPortDataBuf[i] = 1;
      BspService_GetDiscreteInput(i, &state);
   }
}

static void test_output_leds(CuTest *tc)
{
   uint8_t i;
   setup(tc);
   for (i=0; i < NUM_BSP_DISCRETE_OUTPUTS; i++)
   {
      BspService_SetDiscreteOutput(i, BspApi_DiscreteState_Inactive);
      CuAssertUIntEquals(tc, m_outPortDataBuf[i], BspApi_DiscreteState_Inactive);
      BspService_SetDiscreteOutput(i, BspApi_DiscreteState_Active);
      CuAssertUIntEquals(tc, m_outPortDataBuf[i], BspApi_DiscreteState_Active);
   }
}

