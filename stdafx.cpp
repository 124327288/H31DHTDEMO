// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// H31DHT.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


void _dout(const char *format, ...)
{
	char debugStr[1024];	
	memset(debugStr, 0, sizeof(debugStr));
	va_list vaList;
	va_start(vaList, format);
	int length = 0;
	length = vsnprintf(debugStr, sizeof(debugStr) - 1, format, vaList);
	va_end(vaList);
	if (length != 0) 
	{
		OutputDebugString(debugStr);
	}
}