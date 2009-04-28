/*Instance of task t1*/

#include "embUnit.h"
#include "tpl_os.h"
#include "tpl_os_kernel.h" /*for INVALID_TASK*/

DeclareTask(t1);
DeclareTask(t2);
DeclareEvent(Event1);

void tpl_send_it1(void);

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_t1_instance(void)
{
	StatusType result_inst_1,result_inst_2, result_inst_3, result_inst_4, result_inst_6, result_inst_8, result_inst_10, result_inst_11, result_inst_12;
	EventMaskType result_inst_5, result_inst_7, result_inst_9; 

	EnableAllInterrupts();
	
	SCHEDULING_CHECK_INIT(1);
	result_inst_1 = SetEvent(INVALID_TASK,Event1);	
	SCHEDULING_CHECK_AND_EQUAL_INT(1,E_OS_ID, result_inst_1);
	
	SCHEDULING_CHECK_INIT(2);
	result_inst_2 = SetEvent(t1,Event1);	
	SCHEDULING_CHECK_AND_EQUAL_INT(2,E_OS_ACCESS, result_inst_2);
	
	SCHEDULING_CHECK_INIT(3);
	result_inst_3 = SetEvent(t2,Event1);	
	SCHEDULING_CHECK_AND_EQUAL_INT(3,E_OS_STATE, result_inst_3);
	
	SCHEDULING_CHECK_INIT(4);
	result_inst_4 = ClearEvent(Event1);	
	SCHEDULING_CHECK_AND_EQUAL_INT(4,E_OS_ACCESS, result_inst_4);
	
	tpl_send_it1();
	
	SCHEDULING_CHECK_INIT(7);
	result_inst_6 = GetEvent(INVALID_TASK,&result_inst_5);
	SCHEDULING_CHECK_AND_EQUAL_INT(7,E_OS_ID, result_inst_6);

	SCHEDULING_CHECK_INIT(8);
	result_inst_8 = GetEvent(t1,&result_inst_7);	
	SCHEDULING_CHECK_AND_EQUAL_INT(8,E_OS_ACCESS, result_inst_8);	
	
	SCHEDULING_CHECK_INIT(9);
	result_inst_10 = GetEvent(t2,&result_inst_9);
	SCHEDULING_CHECK_AND_EQUAL_INT(9,E_OS_STATE, result_inst_10);	
	
	SCHEDULING_CHECK_INIT(10);
	result_inst_11 = WaitEvent(Event1);
	SCHEDULING_CHECK_AND_EQUAL_INT(10,E_OS_ACCESS, result_inst_11);

	SCHEDULING_CHECK_INIT(11);
	result_inst_12 = ChainTask(t2);
	SCHEDULING_CHECK_AND_EQUAL_INT(11,E_OK, result_inst_12);

}

/*create the test suite with all the test cases*/
TestRef EventMechanismTest_seq1_t1_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t1_instance",test_t1_instance)
	};
	EMB_UNIT_TESTCALLER(EventMechanismTest,"EventMechanismTest_sequence1",NULL,NULL,fixtures);
	
	return (TestRef)&EventMechanismTest;
}
