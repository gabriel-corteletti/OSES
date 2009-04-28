/*Instance1 of task t3*/

#include "embUnit.h"
#include "tpl_os.h"

DeclareTask(t3);

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_t3_instance1(void)
{
	StatusType result_inst;
	
	SCHEDULING_CHECK_INIT(9);
	result_inst = ChainTask(t3);
	SCHEDULING_CHECK_AND_EQUAL_INT(9,E_OK , result_inst);
	
}

/*create the test suite with all the test cases*/
TestRef TaskManagementTest_seq9_t3_instance1(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t3_instance1",test_t3_instance1)
	};
	EMB_UNIT_TESTCALLER(TaskManagementTest,"TaskManagementTest_sequence9",NULL,NULL,fixtures);
	
	return (TestRef)&TaskManagementTest;
}
