/** @file ThreadWrapper.h
 *  @brief �̷߳�װ�ඨ��
 */
#pragma once

/** ���޵ȴ� */
#define WAIT_FOREVER	INFINITE

/** �̴߳�������ʼ */
#define THDMBASEERR              600

/** �̶߳����Ѿ����� */
#define THD_OBJ_CREATED			(THDMBASEERR+1)
/** �߳����ƴ��� */
#define THD_NAME_ERROR			(THDMBASEERR+2)
/** �̴߳���ʧ�� */
#define THD_CREATE_FAILED		(THDMBASEERR+3)
/** �߳��������ȼ�ʧ�� */
#define THD_PRI_FAILED			(THDMBASEERR+4)

/** �̺߳������� */
typedef unsigned long (WINAPI *ThreadFunc)(void *);

/**	@class CThreadWrapper
 *	@brief �̷߳�װ��
 *	@author miao
 *	@version 1.0.0.0
 *	@date 2011-10-09
 *
 *	��װ�˶��̵߳�ʹ��,��Ҫ�� CreateThread() ���������˷�װ��ʹ�÷����������̶߳����Ȼ��ʹ��
 *	 Start() ���������̣߳��߳̽�����ʱ����� Close() �ͷ��߳̾���� Start() ����������ȼ�
 *	priorityһ������ΪTHREAD_PRIORITY_NORMAL��
 *
 */
class CThreadWrapper
{
public:
	/**
	 * ����
	 */
	CThreadWrapper();	
	/**
	 * ����
	 */
	virtual ~CThreadWrapper();	

protected:
	/** �߳�ID */
	unsigned long m_threadID;
	/** �߳��� */
	char m_threadNameString[128];
	/** �߳�Handle */
	HANDLE m_hThreadHandle;	
	/** �߳����ȼ� -15~15,normal 0 */
	int m_nPriority;
	/** ջ��С */
	int m_nStackSize;	
	/** �Ƿ����� */
	bool m_bStarted;	
	/** �������� */	 
	int m_iError; 

public:
	/**
	 * �����߳� 
	 * @param func �̺߳���
	 * @param name ����Windows��ʹ��
	 * @param priority �߳����ȼ�
	 * @param stackSize ջ��С
	 * @param param �̺߳������
	 * @return �Ƿ񴴽������ɹ�
	 */	
	bool Start(ThreadFunc func,char* pName, int priority,int stackSize,void *param);
	/**
	 * �ر�
	 * @param waitTime �ȴ��߳̽���ʱ�䣬Ĭ��һ��
	 * @param bForceClose �ȴ��̳߳�ʱ���̻߳�û���˳����Ƿ�ǿ�ƽ����߳�
	 * @return �Ƿ�رճɹ�
	 */	
	bool Close(unsigned long waitTime=1000,bool bForceClose=false); 
	/**
	 * �ж��߳��Ƿ����
	 * @return �Ƿ����
	 */	
	bool IsExist(); 
	/**
	 * ��ȡ����
	 * @return ���ش���
	 */		
	int GetError(); 
};


