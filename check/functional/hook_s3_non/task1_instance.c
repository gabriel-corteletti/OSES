/*Instance of task t1*/

#include "embUnit.h"
#include "tpl_os.h"
#include "config.h" /*Display information n the right way (printf on UNIX...)*/

DeclareAlarm(Alarm1);
DeclareEvent(Event1);

/*test case:test the reaction of the system called with 
an activation of a task*/
static void test_t1_instance(void)
{
	int result_inst_1, result_inst_2, result_inst_3;
	
	result_inst_1 = SetAbsAlarm(Alarm1, 16, 16);
	TEST_ASSERT_EQUAL_INT(E_OK , result_inst_1); 
	
	result_inst_2 = WaitEvent(Event1);
	TEST_ASSERT_EQUAL_INT(E_OK , result_inst_2); 
	
	result_inst_3 = SetAbsAlarm(Alarm1, 2, 2);
	TEST_ASSERT_EQUAL_INT(E_OS_STATE , result_inst_3);
	
	
}

/*create the test suite with all the test cases*/
TestRef HookTest_seq3_t1_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t1_instance",test_t1_instance)
	};
	EMB_UNIT_TESTCALLER(HookTest,"HookTest_sequence3",NULL,NULL,fixtures);

	return (TestRef)&HookTest;
}