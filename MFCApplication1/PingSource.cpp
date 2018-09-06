#include "stdafx.h"
#include "PingSource.h"
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <cstring>
#include <vector>

//#include "boostPing.cpp"
/*
#include <boost/asio.hpp>
#include <boost/bind.hpp>


#include "icmp_header.hpp"
#include "ipv4_header.hpp"
*/




PingSource::PingSource()
{
	m_testInt = 2;
	m_testCstring= _T("TestPingSourceImplementation");
	//quick memo: how to format INT into CSTRING
	/*
	CString a;
	a.Format(_T("%d"), m_dealerTotal);
	*/
}


PingSource::~PingSource()
{
}

void PingSource::inputCString(CString input)
{
	m_userCStringInput = input;
}

CString PingSource::outputCString()
{
	CString verarbeiteMich = m_userCStringInput;


	convertCStringToStruct(m_userCStringInput);

	convertStructToCString(m_ipAsFourInt);
	//return verarbeiteMich;

	return	m_ipCStrAfterIntConversion;

}

void PingSource::convertCStringToStruct(CString input)
{
	//the basic version does only convert the first 3 numbers
	//	m_ipAsFourInt;

	int number=0;

	//////////////////

	for (int i = 0; i <= 2; i++) {
		number += (boost::lexical_cast<int>(input[i]))*pow(10,2-i);
		//number += 5;
	}
	m_ipAsFourInt.part1 = number;
	/*
	while (*++input)
	{
	try
	{
	args.push_back(lexical_cast<short>(*argv));
	}
	catch (const bad_lexical_cast &)
	{
	args.push_back(0);
	}
	}*/
}
void PingSource::convertStructToCString(ipAsInteger input)
{
	m_ipCStrAfterIntConversion = _T("");
	CString a;
	a.Format(_T("%d"), input.part1);
	m_ipCStrAfterIntConversion += a + _T("_");

	a.Format(_T("%d"), input.part2);
	m_ipCStrAfterIntConversion += a + _T("_");

	a.Format(_T("%d"), input.part3);
	m_ipCStrAfterIntConversion += a + _T("_");

	a.Format(_T("%d"), input.part4);
	m_ipCStrAfterIntConversion += a;
	//quick memo: how to format INT into CSTRING
	/*
	CString a;
	a.Format(_T("%d"), m_dealerTotal);
	*/

}


