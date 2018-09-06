#pragma once


class PingSource
{
private:
	//for the test function to input a CString from the user;
	CString m_userCStringInput = _T(" ");

	//stores the IP as four integer values
	struct ipAsInteger {
		int part1;
		int part2;
		int part3;
		int part4;
	};

	ipAsInteger m_ipAsFourInt{ 127,0,0,1 };

	//output the IP as CSTring to test if it gets converted correctly
	//idea: nutze tiefstriche statt Kommas damit du siehst dass die Umwandlung funktioniert
	CString m_ipCStrAfterIntConversion = _T("untouched");

	//Test function to convert a CString into a vector
	//problem is, that I also want a way to say that the input was invalid
	void convertCStringToStruct(CString input);
	void convertStructToCString(ipAsInteger input);


public:
	PingSource();
	~PingSource();
	int m_testInt = 1;
	CString m_testCstring;


	//functions
	//Interface Function to input a CString
	void inputCString(CString input);
	//Test: Ausgeben des verarbeiteten Test Cstrings:
	CString outputCString();

	


};

