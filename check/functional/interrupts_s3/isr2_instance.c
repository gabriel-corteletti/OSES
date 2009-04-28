/*Instance of interruption isr1*/

#include "embUnit.h"
#include "tpl_os.h"

DeclareTask(t2);

void tpl_send_it1(void);

/*test case:test the reaction of the system called with 
an activation of a isr*/
static void test_isr2_instance(void)
{
	StatusType result_inst;
	
	SCHEDULING_CHECK_STEP(2);
	
	tpl_send_it1();
		
	SCHEDULING_CHECK_INIT(3);
	result_inst = ActivateTask(t2);
	SCHEDULING_CHECK_AND_EQUAL_INT(3,E_OK , result_inst);
	
}

/*create the test suite with all the test cases*/
TestRef InterruptProcessingTest_seq3_isr2_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_isr2_instance",test_isr2_instance)
	};
	EMB_UNIT_TESTCALLER(InterruptProcessingTest,"InterruptProcessingTest_sequence3",NULL,NULL,fixtures);

	return (TestRef)&InterruptProcessingTest;
}
