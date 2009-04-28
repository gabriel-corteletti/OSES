/*Instance of task t5*/

#include "embUnit.h"
#include "tpl_os.h"

DeclareMessage(rm_newislessorequal);

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_t5_instance2(void)
{
	StatusType result_inst_1, result_inst_2;
	StatusType received_char;
	
	SCHEDULING_CHECK_INIT(31);
	result_inst_1 = ReceiveMessage(rm_newislessorequal, &received_char);
	SCHEDULING_CHECK_AND_EQUAL_INT_FIRST(31,E_OK, result_inst_1);
	SCHEDULING_CHECK_AND_EQUAL_INT(31,1, (int)received_char);
	
	SCHEDULING_CHECK_INIT(32);
	result_inst_2 = TerminateTask();
	SCHEDULING_CHECK_AND_EQUAL_INT(32,E_OK, result_inst_2);
}

/*create the test suite with all the test cases*/
TestRef COMInternalTest_seq5_t5_instance2(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t5_instance2",test_t5_instance2)
	};
	EMB_UNIT_TESTCALLER(COMInternalTest,"COMInternalTest_sequence5",NULL,NULL,fixtures);
	
	return (TestRef)&COMInternalTest;
}
