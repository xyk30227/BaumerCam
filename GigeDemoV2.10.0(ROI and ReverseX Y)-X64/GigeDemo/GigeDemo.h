
// GigeDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGigeDemoApp:
// �йش����ʵ�֣������ GigeDemo.cpp
//

class CGigeDemoApp : public CWinApp
{
public:
	CGigeDemoApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
public:
	ULONG_PTR m_gdiplusToken;

	DECLARE_MESSAGE_MAP()
	
};

extern CGigeDemoApp theApp;