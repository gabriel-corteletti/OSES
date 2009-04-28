/*Instance 2 of task isr1*/

#include "embUnit.h"
#include "tpl_os.h"

/*test case:test the reaction of the system called with 
an activation of a task*/
static void test_isr1_instance2(void)
{
	SCHEDULING_CHECK_STEP(8);
	
}

/*create the test suite with all the test cases*/
TestRef InterruptsTest_seq4_isr1_instance2(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_isr1_instance2",test_isr1_instance2)
	};
	EMB_UNIT_TESTCALLER(InterruptsTest,"InterruptsTest_sequence4",NULL,NULL,fixtures);

	return (TestRef)&InterruptsTest;
}
