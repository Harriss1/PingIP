#pragma once
#ifndef MYPING_H
#define MYPING_H
#include <string>
#include <boost/asio/io_context.hpp>
#include <vector>
//#include <stdafx.h>

//debug class for utility while I build the class
//I would preffer a way to print 
/*
class WriteOrPrint {
protected:
	void print(std::string printMsg) {
		std::cout << printMsg << "\n";
	}
};
*/
class Debug //: public WriteOrPrint
{
public: //should be protected if it was for other classes lol

	void printMsg(std::string debugMsg) {
		if (m_enableDebugMessage) {
			m_debugMsgLog.push_back("debugMsg from: \"" + m_debugName + "\": " + debugMsg);
		//	std::cout << "debugMsg from \"" << m_debugName << "\": " << debugMsg << "\n";
		}
	}
	void writeMsg(std::string debugMsg) {
		if (m_enableDebugFilewrite) {}
		//	std::cout << "here it should write to a logfile\n";
	}
	void msg(std::string debugMsg) {
		printMsg(debugMsg);
		writeMsg(debugMsg);
	}
	std::vector<std::string> getLog() {
		return m_debugMsgLog;
	}
	
	void addToLog(std::vector<std::string> addMsgs){
		int size=addMsgs.size();
		//std::cout << "size=" << size << "\n";
		m_debugMsgLog.push_back("in addToLog");
		for (const auto &element : addMsgs) {
			msg(element);
		}
	}

	void readLog(int readOnlyTheLast = 0) {
		int size=m_debugMsgLog.size();
	//	std::cout << "readlog, size:" << size << "\n";
		for (int logIndex = size; logIndex > 0; logIndex--) {
			//std::cout << "in for loop\n";
		//	std::cout << m_debugMsgLog.at(logIndex-1) << "\n";
		}
	}

public:
	Debug(bool enableDebugMessage=(false), bool enableDebugFilewrite=(false), std::string debugName=("MyPing"))
		: m_enableDebugMessage(enableDebugMessage),
		m_enableDebugFilewrite(enableDebugFilewrite),
		m_debugName(debugName)
	{

	}
private:
	std::vector<std::string> m_debugMsgLog;

	std::string m_debugName;
	bool m_enableDebugMessage;
	bool m_enableDebugFilewrite;
};
//the pinger function


class ImplementMyPing : public Debug {
private:
	const char* m_ipAdress;
public:
	ImplementMyPing(const char* ipAdress)
		: m_ipAdress(ipAdress), Debug(true, false, "ImplementMyPing class")
	{
	}

	std::string runPing();
	
};



#endif // MYPING_H

