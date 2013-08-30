/** @file ThreadWrapper.cpp
 *  @brief �̷߳�װ��ʵ��
 */
#include "stdafx.h"
#include "ThreadWrapper.h"

#if WIN32
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#endif

//////////////////////////////////////////////////////////////////////
// Constructor/Destructor
//////////////////////////////////////////////////////////////////////

CThreadWrapper::CThreadWrapper()
{
	// ��ʼ��
	m_hThreadHandle=NULL;
	m_nPriority=100;
	m_nStackSize=1000;
	m_bStarted=false;
	m_threadID=0;
	memset(m_threadNameString,0,sizeof(m_threadNameString));
	m_iError=0;
}

CThreadWrapper::~CThreadWrapper()
{
	// �ر�
	Close();
}

//////////////////////////////////////////////////////////////////////////
// public

bool CThreadWrapper::Start(ThreadFunc func,char* pName, int priority,int stackSize,void *param)
{
	// �Ƿ��Ѿ�����
	if(m_bStarted)
	{
		_dout(_T("ThreadWrapper the thread already started!\n"));
		m_iError=THD_OBJ_CREATED;
		return false;
	}	
	// �߳��� 
	if (pName==NULL || (strcmp(pName,"")==0))
	{
		_dout(_T("ThreadWrapper input function name error!\n"));
		m_iError=THD_NAME_ERROR;
		return false;
	}

	sprintf_s(m_threadNameString,"%s",pName);

	// ���ȼ���Ч���ж�
	if((priority < THREAD_PRIORITY_IDLE) || (priority > THREAD_PRIORITY_TIME_CRITICAL)) 
	{ 
		priority = THREAD_PRIORITY_NORMAL;
	}
	m_nPriority = priority;
	// ջ��С
	if((stackSize <= 0) || (stackSize > 100000000)) 
	{ 
		stackSize = 1000;
	}
	m_nStackSize=stackSize;
	
	// �����߳�
	m_hThreadHandle = CreateThread(0,   // Security Attributes,
		stackSize,						// Stack Size,
		func,							// Starting Address.
		param,							// Parmeters
		0,								// Creation Flags,
		&m_threadID);					// Thread ID (Can not be null on 95/98)

	if (m_hThreadHandle == 0)
	{
		_dout(_T("ThreadWrapper %s starting thread error,err(%d, %d)!\n"),m_threadNameString,GetLastError(), GetLastError());
		m_iError=THD_CREATE_FAILED;
		return false;
	}
	// �������ȼ�
	if(!SetThreadPriority(m_hThreadHandle,m_nPriority))	
	{
		_dout(_T("ThreadWrapper %s set thread priority error,err(%d, %d)!\n"),m_threadNameString,GetLastError(), GetLastError());
		m_iError=THD_PRI_FAILED;
	}
	// ��ȡ�߳����ȼ�
	m_nPriority=GetThreadPriority(m_hThreadHandle);	
	m_bStarted=true;	
	return true;
}

bool CThreadWrapper::IsExist()
{
	// ���ؽ��
	bool bRet=false;
	// �˳�code
	unsigned long exitCode;
	if(m_bStarted)
	{
		if(GetExitCodeThread(m_hThreadHandle,&exitCode)==TRUE)
		{
			// ���̻���
			if(STILL_ACTIVE==exitCode)
			{
				bRet=true;
			}
		}
	}
	return bRet;
}

bool CThreadWrapper::Close(unsigned long  waitTime,bool bForceClose)
{
	if(m_bStarted)
	{
		// �ͷ��߳̾��
		if(m_hThreadHandle!=NULL) 
		{
			_dout(_T("ThreadWrapper %s wait thread quit,wait time(%d).\n"), m_threadNameString,waitTime);
			int nRes = ::WaitForSingleObject(m_hThreadHandle, waitTime);
			// �ȴ���ʱ�䣬�߳�û���˳�������bForceClose�����Ƿ�ǿ���˳�
			if (nRes != WAIT_OBJECT_0) {
				_dout(_T("ThreadWrapper %s wait quit timeout,(err=%d).\n"), m_threadNameString,GetLastError());
				if(bForceClose) 
				{
					// �����߳�
					if(TerminateThread(m_hThreadHandle,0)==FALSE)
					{
						_dout(_T("ThreadWrapper %s terminate thread failed,(err=%d).\n"), m_threadNameString,GetLastError());
					}
				}
			}
			if(m_hThreadHandle!=NULL) 
			{
				CloseHandle(m_hThreadHandle);
				m_hThreadHandle=NULL;
			}
		}
		m_bStarted=false;
	}
	return true;
}

int CThreadWrapper::GetError()
{
	return m_iError;
}





