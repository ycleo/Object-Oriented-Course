﻿
// Event.h: PROJECT_NAME 應用程式的主要標頭檔
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主要符號


// CEventApp:
// 查看 Event.cpp 以了解此類別的實作
//

class CEventApp : public CWinApp
{
public:
	CEventApp();

// 覆寫
public:
	virtual BOOL InitInstance();

// 程式碼實作

	DECLARE_MESSAGE_MAP()
};

extern CEventApp theApp;
