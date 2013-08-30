// H31DHTDlg.h : ͷ�ļ�
//

#pragma once
#include "ThreadWrapper.h"
#include <wininet.h>
#include "afxwin.h"
#include "math.h"
#define MAXBLOCKSIZE 1024
#define WM_MYUPDATEDATA WM_USER+100 
#define  MAX_LOACL_IP_NUM 10000

// CH31DHTDlg �Ի���
class CH31DHTDlg : public CDialog
{
// ����
public:
	CH31DHTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_H31DHT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	int GetPongIPList(unsigned char* id,const struct sockaddr* fromaddr);
	int AddShowLog(char *log);
	int AddShowHashLog(char *log);
private:
	/**  ���ݴ����߳� */
	CThreadWrapper m_dataThread;
	/**  �Ƿ����̶߳��� */
	bool m_bDataThread; 
	/**  ���������ӵľ�� */
	int m_soListen;	
	/**  ���߳̾�� */
	HANDLE m_hMainThread;
	/**  ����� */
	int m_iErrorNo;	

	char buf[4096];

	/**  
	* ��Ҫ�����߳� 
	* @param lpParam ������ָ��.
	* @return ����DWORD����
	*/
	static DWORD WINAPI DataMgrThread(LPVOID lpParameter);

	int ManageDHTProcess();
	void Tr_Sha1_To_Hex (char *out, const unsigned char *sha1);

	int ReadDHTFile();
	int SaveDHTFile();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnUpdateMyData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString m_myID;
	CString m_showLog;
	CEdit m_showLogCtrl;
	int m_port;
	CEdit m_hashListCtrl;
	CString m_hashList;
	CString m_showID;

public:
	afx_msg void OnBnClickedButtonGetid();
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedStop();
};
