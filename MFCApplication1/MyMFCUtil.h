#pragma once
//#include "stdafx.h"
//#include "MyPing.h"
//#include <vector>

class MyMFCUtil //:public CDialogEx
{
public:
	MyMFCUtil();
	~MyMFCUtil();

	void testFile();
};

//static constructor
/*
struct CommandMap{
std::string toolButtonName,
std::string toolExecCommand,
std::string toolUserInput,
std::string toolOutup};

std::vector<CommandMap> map;
map.push_back(1,2,3,4);


MyMFCUtil(std::vector<CommandMap> map);


std::string ipAdress;
ping.input();
ping.exec();
ping.output();
function pointer into the inititalisation of MyMFCUtil?
MyMFCUtil ping(*fktPtrMyPingTool);
*/
