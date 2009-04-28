/*Instance 3 of posttask*/

#include "embUnit.h"
#include "tpl_os.h"

void tpl_send_it1(void);

/*test case:test the reaction of the system called with 
an activation of a isr*/
static void test_posttask_instance3(void)
{
	
	SCHEDULING_CHECK_STEP(3);

	tpl_send_it1();
	SuspendAllInterrupts();
	tpl_send_it1();
	ResumeAllInterrupts();
	
}

/*create the test suite with all the test cases*/
TestRef HookTest_seq4_posttask_instance3(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_posttask_instance3",test_posttask_instance3)
	};
	EMB_UNIT_TESTCALLER(HookTest,"HookTest_sequence4",NULL,NULL,fixtures);

	return (TestRef)&HookTest;
}
