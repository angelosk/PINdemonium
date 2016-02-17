#pragma once

#include <stdio.h>
#include "WriteInterval.h"
#include "ProcInfo.h"
#include <ctime>
#include <direct.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
namespace W {
	#include <windows.h>
}

#define LOG_WRITE_TO_FILE 1 //if it is uncommented the result will be saved on file otherwise they'll be printed to stdout

class Config
{

public:
	static Config* getInstance();
	
	FILE* Config::getLogFile();

	//getter
	string getBasePath();
	string getCurrentDumpFilePath();
	string getCurrentDetectedListPath();
	string getNotWorkingPath();
	long double getDumpNumber();

	//utils
	void incrementDumpNumber();
	void Config::closeLogFile();
	void Config::closeReportFile();
	void writeOnReport(ADDRINT ip, WriteInterval wi);
	void Config::writeOnTimeLog(string s);
	void setWorking (int working);

	//files and paths
	static const string PIN_DIRECTORY_PATH_DEP;
	static const string PIN_DIRECTORY_PATH_OUTPUT;
	static const string LOG_FILENAME;
	static const string REPORT_FILENAME;
	static const string IDA_PATH;
	static const string IDAP_BAD_IMPORTS_CHECKER;
	static const string BAD_IMPORTS_LIST;
	static const string DETECTED_BAD_IMPORTS_LIST;
	static const string SCYLLA_DUMPER_PATH;
	static const string PIN_DIRECTORY_PATH_OUTPUT_NOT_WORKING;
	static const string DUMPER_SELECTOR_PATH;


	//--------------------------Command line Tuning Flags----------------------------
	static const bool  ATTACH_DEBUGGER;
	
	//Tunable from command line
	bool INTER_WRITESET_ANALYSIS_ENABLE; //Trigger the analysis inside a WriteSet in which WxorX is already broken if a Long JMP is encontered (MPress packer)
	UINT32 WRITEINTERVAL_MAX_NUMBER_JMP;

	//mode of operation
    bool UNPACKING_MODE;
    bool ANTIEVASION_MODE;
	bool ANTIEVASION_MODE_INS_PATCHING;
	bool ANTIEVASION_MODE_SREAD;
	bool ANTIEVASION_MODE_SWRITE;
	bool ADVANCED_IAT_FIX;
	bool POLYMORPHIC_CODE_PATCH;

	//--------------------------Command line Tuning Flags----------------------------

	static const string FILTER_WRITES_ENABLES;        //Which write instructions are filtered(possible values: 'stack teb')
	static const UINT32 TIMEOUT_TIMER_SECONDS;
	static const UINT32 TICK_DIVISOR; //this is used in order to lowe the ticks returnedd from GetTickCount and timeGetTime 
	static const UINT32 CC_DIVISOR; // this is used in order to lower the microseconds returned from the QueryPerformanceCounter 
	static const UINT32 KSYSTEM_TIME_DIVISOR; // this is used to lower the LONG lowpart returned from the timeGetTime in the struct _KSYSTEM_TIME inside kuser_shared_data
	static const UINT32 RDTSC_DIVISOR;

private:
	Config::Config();
	static Config* instance;
	FILE *log_file;
	FILE *report_file;
	string base_path;
	string not_working_path;
	string cur_dump_path;        //Path of the final (IAT fixed) Dump
	string cur_list_path;		 //Path of the list of the detected function
	long double dump_number;
	string getCurDateAndTime();
	int numberOfBadImports;
	int calculateNumberOfBadImports();
	int working;

};

