
// JluNewCamera.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJluNewCameraApp:
// �йش����ʵ�֣������ JluNewCamera.cpp
//

class CJluNewCameraApp : public CWinApp
{
public:
	CJluNewCameraApp();

// ��д
public:
	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJluNewCameraApp theApp;