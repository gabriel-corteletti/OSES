OIL_VERSION = "2.5";


IMPLEMENTATION trampoline {
	//Fix the default STACKSIZE of tasks
	TASK {
        UINT32 STACKSIZE = 256;
	};
};


CPU RM_scheduler {
    OS config {
        STATUS = EXTENDED;
        BUILD = TRUE {
            TRAMPOLINE_BASE_PATH = "../..";
            APP_NAME = "lab04_ex02_exe";
            APP_SRC = "lab04_ex02.cpp";
            CPPCOMPILER = "avr-g++";
            COMPILER = "avr-gcc";
            LINKER = "avr-gcc";
            ASSEMBLER = "avr-gcc";
            COPIER = "avr-objcopy";
            SYSTEM = PYTHON;
            LIBRARY = serial;
        };
        SYSTEM_CALL = TRUE;
    };
 
    APPMODE stdAppmode {};
  

    /************* ALARMS DEFINITION *************/

    ALARM alarmW {              //every 100ms
        COUNTER = SystemCounter;
        ACTION = ACTIVATETASK { TASK = TaskW; };
        AUTOSTART = TRUE { APPMODE = stdAppmode; ALARMTIME = 98; CYCLETIME = 98; };
    };

    ALARM alarmV {               //every 125ms
        COUNTER = SystemCounter;
        ACTION = ACTIVATETASK { TASK = TaskV; };
        AUTOSTART = TRUE { APPMODE = stdAppmode; ALARMTIME = 122; CYCLETIME = 122; };
    };


    /************* TASKS DEFINITION *************/

    TASK TaskW {
        PRIORITY = 2;
        AUTOSTART = TRUE { APPMODE = stdAppmode; };
        ACTIVATION = 1;
        SCHEDULE = FULL;
    };

    TASK TaskV {
        PRIORITY = 1;
        AUTOSTART = TRUE { APPMODE = stdAppmode; };
        ACTIVATION = 1;
        SCHEDULE = FULL;
    };
};