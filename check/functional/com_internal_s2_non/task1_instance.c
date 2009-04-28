/*Instance of task t1*/

#include "embUnit.h"
#include "tpl_os.h"
#include "tpl_com_definitions.h"  /*for E_COM_X*/

DeclareMessage(sm);
DeclareTask(t2);

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_t1_instance(void)
{
	StatusType result_inst_1, result_inst_2, result_inst_3, result_inst_4, result_inst_5, result_inst_6, result_inst_7, result_inst_8, result_inst_9, result_inst_10, result_inst_11, result_inst_12, result_inst_13;
	
	SCHEDULING_CHECK_INIT(1);
	result_inst_1 = GetMessageStatus(sm);	
	SCHEDULING_CHECK_AND_EQUAL_INT(1,E_COM_NOMSG, result_inst_1);
	
	SCHEDULING_CHECK_INIT(2);
	result_inst_2 = SendMessage(SEND_MESSAGE_COUNT, "5");	
	SCHEDULING_CHECK_AND_EQUAL_INT(5,E_COM_ID, result_inst_2);
	
	SCHEDULING_CHECK_INIT(6);
	result_inst_3 = GetMessageStatus(sm);	
	SCHEDULING_CHECK_AND_EQUAL_INT(6,E_COM_NOMSG, result_inst_3);
	
	SCHEDULING_CHECK_INIT(7);
	result_inst_4 = SendMessage(sm, "1");	
	SCHEDULING_CHECK_AND_EQUAL_INT(7,E_OK, result_inst_4);
	
	SCHEDULING_CHECK_INIT(8);
	result_inst_5 = GetMessageStatus(sm);	
	SCHEDULING_CHECK_AND_EQUAL_INT(8,E_OK, result_inst_5);
	
	SCHEDULING_CHECK_INIT(9);
	result_inst_6 = SendMessage(sm, "2");	
	SCHEDULING_CHECK_AND_EQUAL_INT(9,E_OK, result_inst_6);
	
	SCHEDULING_CHECK_INIT(10);
	result_inst_7 = GetMessageStatus(sm);	
	SCHEDULING_CHECK_AND_EQUAL_INT(10,E_OK, result_inst_7);
	
	SCHEDULING_CHECK_INIT(11);
	result_inst_8 = SendMessage(sm, "3");	
	SCHEDULING_CHECK_AND_EQUAL_INT(11,E_OK, result_inst_8);
	
	SCHEDULING_CHECK_INIT(12);
	result_inst_9 = GetMessageStatus(sm);	
	SCHEDULING_CHECK_AND_EQUAL_INT(12,E_OK, result_inst_9);
	
	SCHEDULING_CHECK_INIT(13);
	result_inst_10 = SendMessage(sm, "4");	
	SCHEDULING_CHECK_AND_EQUAL_INT(13,E_OK, result_inst_10);
	
	SCHEDULING_CHECK_INIT(14);
	result_inst_11 = GetMessageStatus(sm);	
	SCHEDULING_CHECK_AND_EQUAL_INT(14,E_COM_LIMIT, result_inst_11);
	
	SCHEDULING_CHECK_INIT(15);
	result_inst_12 = ActivateTask(t2);	
	SCHEDULING_CHECK_AND_EQUAL_INT(15,E_OK, result_inst_12);
	
	SCHEDULING_CHECK_INIT(16);
	result_inst_13 = Schedule();	
	SCHEDULING_CHECK_AND_EQUAL_INT(39,E_OK, result_inst_13);
	
}

/*create the test suite with all the test cases*/
TestRef COMInternalTest_seq2_t1_instance(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t1_instance",test_t1_instance)
	};
	EMB_UNIT_TESTCALLER(COMInternalTest,"COMInternalTest_sequence2",NULL,NULL,fixtures);
	
	return (TestRef)&COMInternalTest;
}
