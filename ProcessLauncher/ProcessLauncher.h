
// ProcessLauncher.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CProcessLauncherApp:
// � ���������� ������� ������ ��. ProcessLauncher.cpp
//

class CProcessLauncherApp : public CWinApp
{
public:
	CProcessLauncherApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CProcessLauncherApp theApp;