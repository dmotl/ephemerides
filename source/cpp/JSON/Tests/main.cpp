/*!
*  \file      main.cpp
*  \author    David Motl
*  \date      2022-09-18
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#include <QtCore/QCoreApplication>
#include "gtest/gtest.h"

static _CRT_REPORT_HOOK gs_prevHook = NULL;

//
// Callback procedure from the CRT reporting function
// The function is a filter that filters out all memory leaks 
// which are not marked by the source file (with the cpp, c or h extension)
//
static int reportingHook(int reportType, char* userMessage, int* retVal)
{
	// This function is called several times for each memory leak.
	// Each time a part of the error message is supplied.
	// This holds number of subsequent detail messages after
	// a leak was reported
	const int numFollowupDebugMsgParts = 3;
	static bool processMessage = false;
	static int debugMsgPartsCount = 0;
	if (processMessage) {
		// check if the memory leak reporting ends
		if (strncmp(userMessage, "Object dump complete.\n", 10) == 0) {
			_CrtSetReportHook(gs_prevHook);
			processMessage = false;
		}
		else {
			// something from our own code?
			if (strstr(userMessage, ".cpp") || strstr(userMessage, ".c") || strstr(userMessage, ".h")) {
				debugMsgPartsCount = 0;
			}
			else {
				if (debugMsgPartsCount++ >= numFollowupDebugMsgParts)
					return 1;  // ignore it
			}
		}
	}
	else {
		// check if the memory leak reporting starts
		if (strncmp(userMessage, "Detected memory leaks!\n", 10) == 0) {
			processMessage = true;
			debugMsgPartsCount = numFollowupDebugMsgParts;
		}
	}

	// give it back to _CrtDbgReport() to be printed to the console
	return 0;
}

//
// Install the CRT report filter
//
static void setFilterDebugHook(void)
{
	gs_prevHook = _CrtSetReportHook(reportingHook);
}

int main(int argc, char* argv[])
{
    // Initialize windows memory leak detector
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    setFilterDebugHook();

    QCoreApplication a(argc, argv);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
