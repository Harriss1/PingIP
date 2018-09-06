#pragma once
#include <string>
#include <vector>
#include "MyPing.h"

//Here I store the functions that communicate with the Dialog.cpp main
//Additionally I include MyPing.h for example into here.
//My intention is prevent any commands within the Dlg.cpp, except for read(), and exec(), and output().

//For example a longer text with wrapping should get outputted via MyMFCUtil.h objects.
//Like, for example: I want to output 4 lines of ping results, and then one line of a personal message.
//For this I need a variable in Mymfcutil that adds text to itself.????

//My goal is to process the output variables of included classes only in this file, and to prevent handing the data
//over inside the main(); main is only supposed to display and read the stuff.

//I need a display tool. And I need a save the data to a file tool. (Example: Ping only each hour.)
//okay, I need a container to store the data that are supposed to get displayed.
//and then I need a function that outputs this data as MFC readable CString.
//and later on I need a function that outputs this data for a table in MFC with rows and collumns.

//Ich könnte versuchen ein einfaches Datei öffnen und schließen und lesen über MySource and Mymfcutil zu implementieren.

//I have to use additional include directories to include a new header plus .cpp file like Myping.h.

class MySource //:public Debug, MyMFCUtil
{
public:
	MySource();
	~MySource();

//My functions for the MFC App:

	//void pingInput(std::string ipAdress);
	void pingInput(CString ipAdress); //It's very likely that I have multiple input types, and to convert it.
	void pingBtn() {
		addToDebugLog("At the start of pingBtn()");
		pingExec();
		pingStoreRaw();
	}
	CString pingOutput(); //this is for the textfield in the MFC dialog, maybe multiline
		//pingOutput is the place where I could put in debug messages at the moment, later on I want a sepearte debug msg window
private:
	void pingExec();
	void pingStoreRaw() {}
	void addToDebugLog(std::string msg) {
		CString str(msg.c_str());		
		m_debugLog += str + _T("\r\n");
	}

//for MyPing:
	CString m_debugLog=_T("### Debug Log: ###\r\n");
	std::vector<CString> m_pingResults{ _T("Pingresultplaceholder1"),_T("Pingresultplaceholder2") };
	CString m_ipAdressFromMFC=_T("0");
	const char* m_ipAdressForMyPing = "google.com";
	bool m_showDebugLog=true;
};


/*
test123TestPingSourceImplementation
123_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream



test123TestPingSourceImplementation
123_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream




test345TestPingSourceImplementation
345_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
debugMsg from: "ImplementMyPing class": in runPing.
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream

test123TestPingSourceImplementation
123_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
debugMsg from: "ImplementMyPing class": in runPing.
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream


test434TestPingSourceImplementation
434_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
debugMsg from: "ImplementMyPing class": in runPing.
debugMsg from: "ImplementMyPing class": after io.run_one()
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream


test123TestPingSourceImplementation
123_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
debugMsg from: "ImplementMyPing class": in runPing.
debugMsg from: "ImplementMyPing class": after io.run_one()
in addToLog
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream



test245TestPingSourceImplementation
245_0_0_1
### Pingresults: ###
Pingresultplaceholder1
Pingresultplaceholder2
### Debug Log: ###
At the start of pingBtn()
debugMsg from: "ImplementMyPing class": in runPing.
debugMsg from: "ImplementMyPing class": after io.run_one()
in addToLog
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": MyPinger constructed.
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": testAccess working.
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": start timer
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": at the end of startSend()
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": in startReceive
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": in handleReceive
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": try to put all the info into msg:

debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": 32 bytes
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": from:216.58.207.46
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": icmp_seq=1
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": ttl=54
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": time elapsed: 19
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": in startReceive
debugMsg from: "ImplementMyPing class": debugMsg from: "class Mypinger": end of handleReceive
At the end of pingExec
In pingOutput()
added one pingresultelement to outputstream
added one pingresultelement to outputstream
*/
