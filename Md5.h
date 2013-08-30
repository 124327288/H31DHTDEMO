#pragma once

#ifndef __MD5CLASS__
#define __MD5CLASS__

#include <stdio.h>
#if WIN32
	#include <io.h>
	#include <conio.h>
	#include <stdexcept>
#else
	#include "string.h"
#endif

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
#ifdef WIN32
/** ����ṹ���ڴ����Ϊ1�ֽ� */
#pragma pack(1)
#else 
#pragma pack(1,1,1)
#endif
/**  
* @struct ULongPackMD5
* @brief unsigned long���¶��� 
*/
typedef struct tagULongPackMD5
{
	/**  ʹ��ֵ */
	unsigned long value;
	tagULongPackMD5()
	{
		value = 0;
	};
}ULongPackMD5;
typedef unsigned long ULONG;
#pragma  pack()
/**
*  @class CMD5
*  @brief �ļ�MD5�����㷨��,֧��PPC�����µĴ�С�ֽ�������
*  @author  Miao
*  @version  1.0.0.0
*  @date  2010-07-05
*
*  ˵��ʹ�÷�����������Ҫ���������ļ���MD5ֵ�����ڼ���ļ��Ƿ�������;ʹ�÷�������
*  CMd5 themd5;
*  ����1:���ļ���ʽ
*  themd5.OpenFile("c://1.txt");
*  char md5str[32];
*  memset(md5str,0,sizeof(md5str));
*  memcpy(md5str,themd5.GetDigestKey(),32);
*  unsigned long a=themd5.GetMd5Number();
*  themd5.CloseFile();
*  ����1:�����ַ����ķ���
*  themd5.(char* str,int len);
*  memcpy(md5str,themd5.GetDigestKey(),32);
*  unsigned long a=themd5.GetMd5Number();
*/
class CMd5
{
public:
	/**  ���캯�� */
	CMd5();
	/**  �������� */
	~CMd5();
	/**  �����ļ���·�����м��� */
	bool OpenFile(char *filename=NULL);
	/**  ֱ�������ַ������м��� */
	void TargetStr(char* str,int len);
	/**  ȡ�÷��ص�MD5�ַ��� */
	char* GetDigestKey();
	/**  ȡ�ô��� */
	char* GetErr();
	/**  ȡ��MD5������������ */
	ULONG GetMd5Number();
	/**  �ر��ļ�ָ�� */
	bool CloseFile();

private:
	inline ULONG LRotate(ULONG Sdata,int nBit);
	inline ULONG F(ULONG x,ULONG y,ULONG z);
	inline ULONG G(ULONG x,ULONG y,ULONG z);
	inline ULONG H(ULONG x,ULONG y,ULONG z);
	inline ULONG I(ULONG x,ULONG y,ULONG z);
	inline void FF(ULONG &a,ULONG b,ULONG c,ULONG d,ULongPackMD5* Msg,int nBit,ULONG Cnt);
	inline void GG(ULONG &a,ULONG b,ULONG c,ULONG d,ULongPackMD5* Msg,int nBit,ULONG Cnt);
	inline void HH(ULONG &a,ULONG b,ULONG c,ULONG d,ULongPackMD5* Msg,int nBit,ULONG Cnt);
	inline void II(ULONG &a,ULONG b,ULONG c,ULONG d,ULongPackMD5* Msg,int nBit,ULONG Cnt);
private:
	bool Init();
	bool Read64Byte();
	void TransForm();
	bool CaculateFile();
	bool CaculateStr(char* str,int len);
	void SetErr(int nErr);
	void JustifytoStr();
protected:
	FILE* m_pFile;
	char Pointer[64];
	ULONG T[4];
	bool IsSuc;
	char fname[256];
	long long FileLen;
	char strErr[50];
	char Digest[33];
};
#endif