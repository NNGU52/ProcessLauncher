
// ProcessLauncher.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CProcessLauncherApp:
// О реализации данного класса см. ProcessLauncher.cpp
//

class CProcessLauncherApp : public CWinApp
{
public:
	CProcessLauncherApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CProcessLauncherApp theApp;