#include <string>
#include <Windows.h>

#include <QtWidgets>

#include "config.h"

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
		if (strncmp(userMessage,"Object dump complete.\n", 10) == 0) {
			_CrtSetReportHook(gs_prevHook);
			processMessage = false;
		} else {
			// something from our own code?
			if (strstr(userMessage, ".cpp") || strstr(userMessage, ".c") || strstr(userMessage, ".h")) {
				debugMsgPartsCount = 0;
			} else {
				if (debugMsgPartsCount++ >= numFollowupDebugMsgParts)
					return TRUE;  // ignore it
			}
		}
	} else {
		// check if the memory leak reporting starts
		if (strncmp(userMessage,"Detected memory leaks!\n", 10) == 0) {
			processMessage = true;
			debugMsgPartsCount = numFollowupDebugMsgParts;
		}
	}
	
	// give it back to _CrtDbgReport() to be printed to the console
	return FALSE;
}

//
// Install the CRT report filter
//
static void setFilterDebugHook(void)
{
	gs_prevHook = _CrtSetReportHook(reportingHook);
}

#include "CMainWindow.h"


//
// Main function
//
int main(int argc, char *argv[]) 
{
	int exitCode = 0;

	// Initialize windows memory leak detector
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	setFilterDebugHook();

	QApplication a(argc, argv);

	// Set default encoding to utf-8
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	// Taskbar icon
    //qApp->setWindowIcon(QIcon(":/TimaMainQt/Resources/application.svg"));

	// Version
    qApp->setApplicationName(QLatin1String(APPLICATION_NAME));
	qApp->setApplicationVersion(QLatin1String(VERSION_STRING));

	CMainWindow mainWin;
	mainWin.show();
	exitCode = a.exec();

	return exitCode;
}