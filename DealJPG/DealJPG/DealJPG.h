
// DealJPG.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDealJPGApp:
// �йش����ʵ�֣������ DealJPG.cpp
//

class CDealJPGApp : public CWinApp
{
public:
	CDealJPGApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDealJPGApp theApp;