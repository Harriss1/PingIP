#include "stdafx.h"
#include "MyMFCUtil.h"


MyMFCUtil::MyMFCUtil()
{
}


MyMFCUtil::~MyMFCUtil()
{
}

void MyMFCUtil::testFile()
{
	SECURITY_ATTRIBUTES saPermissions;

	saPermissions.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPermissions.lpSecurityDescriptor = NULL;
	saPermissions.bInheritHandle = TRUE;

	CString m_memoSavePath = _T("Memos//");
	CString m_memoName = _T("Memo");
	CString m_strEdit; //user memo content
	CString m_strNameEdit; //user memo text
	CString m_loadedMemo = _T("none");

	if (CreateDirectory(m_memoSavePath + L"", &saPermissions) == TRUE)
		AfxMessageBox(L"The directory was created.");



}
