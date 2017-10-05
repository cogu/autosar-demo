#include <stdio.h>
#include "CuTest.h"


CuSuite* testsuite_BspServiceProxy(void);

void RunAllTests(void)
{
   CuString *output = CuStringNew();
   CuSuite* suite = CuSuiteNew();

   CuSuiteAddSuite(suite, testsuite_BspServiceProxy());
   CuSuiteRun(suite);
   CuSuiteSummary(suite, output);
   CuSuiteDetails(suite, output);
   printf("%s\n", output->buffer);
   CuSuiteDelete(suite);
   CuStringDelete(output);
}

int main(void)
{
   RunAllTests();
   return 0;
}
