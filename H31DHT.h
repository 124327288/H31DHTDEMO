// H31DHT.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CH31DHTApp:
// �йش����ʵ�֣������ H31DHT.cpp
//

class CH31DHTApp : public CWinApp
{
public:
	CH31DHTApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CH31DHTApp theApp;