#include "stdafx.h"
#include "MySource.h"
#include <vector>
//git change 1?
//v7 update 17:49, 06.09.2018
//v7 from browserchange 17:53, 06.09.2018


MySource::MySource()
{
}


MySource::~MySource()
{
}

CString MySource::pingOutput()
{
	CString output=_T("### Pingresults: ###\r\n");
	addToDebugLog("In pingOutput() ihr bitches");
	
	for (const auto &element : m_pingResults) {
		output += element + _T("\r\n");
		addToDebugLog("added one pingresultelement to outputstream");
	}


	if (m_showDebugLog) output += m_debugLog;
	return output;
}

void MySource::pingExec()
{
	const char* ip;
	if (m_ipAdressFromMFC == _T("0")) ip = m_ipAdressForMyPing;
	else ip = "unfinished code"; //add in IPconversion function outside of pingExec

	//start the pingtool here
	ImplementMyPing myping(ip);
	myping.runPing();
	
	//std::vector<std::string> myping.getLog();

	for (const auto &element : myping.getLog()) {
		addToDebugLog(element);
	}

	addToDebugLog("At the end of pingExec");
}
