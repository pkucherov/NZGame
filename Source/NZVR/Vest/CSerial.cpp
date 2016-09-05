// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "NZVR.h"
#include "CSerial.h"

CSerial::CSerial()
{
#if PLATFORM_WINDOWS
	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));
	m_hIDComDev = NULL;
	m_bOpened = false;
#endif
}

CSerial::~CSerial()
{
#if PLATFORM_WINDOWS
	Close();
#endif
}

void CSerial::EnumSerialPorts(std::queue<int> &com_num)
{
#if PLATFORM_WINDOWS
	//   �õ��豸��Ϣ��   
	while (!com_num.empty())
	{
		com_num.pop();
	}
	HDEVINFO   hDevInfo = SetupDiGetClassDevs(
		(LPGUID)&GUID_DEVCLASS_PORTS,
		NULL,
		0,
		DIGCF_PRESENT/*   |   DIGCF_ALLCLASSES*/);

	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error!   SetupDiGetClassDevs()   return   %d"), GetLastError());

		SetupDiDestroyDeviceInfoList(hDevInfo);
		UE_LOG(LogTemp, Warning, TEXT("has erro"));
	}

	TCHAR   szBuf[MAX_PATH];
	SP_DEVINFO_DATA   spDevInfoData = { sizeof(SP_DEVINFO_DATA) };

	//   ��ʼ�о��豸   
	unsigned long i = 0;
	for (i = 1; SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
	{

		//   �õ��豸�ͺ�   
		if (SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&spDevInfoData,
			(0x0000000C),
			NULL,
			(PBYTE)szBuf,
			MAX_PATH,
			NULL))
		{
			// 			UE_LOG(LogTemp, Warning, TEXT("%03d   :   FriendName   =   %s"), i, szBuf);

			FString mes(szBuf);
			int j = mes.Find("com", ESearchCase::IgnoreCase, ESearchDir::FromStart, -1) + 3;
			int num = mes.Len() - j - 1;
			mes = mes.Mid(j, num);

			if (num > 3)////�������⴮�ڣ������ã�Ӧ��ע�͵�
			{
				j = mes.Find("->", ESearchCase::IgnoreCase, ESearchDir::FromStart, -1);
				mes = mes.Mid(0, j);
			}
			com_num.push(FCString::Atoi(*mes));
			// 			UE_LOG(LogTemp, Warning, TEXT("%03d   :   FriendName   =   %d"), i, FCString::Atoi(*mes));

		}
	}
	i--;

#endif
}

bool CSerial::Open(int nPort, int nBaud)
{
#if PLATFORM_WINDOWS
	if (m_bOpened) return(true);

	TCHAR szPort[15];
	TCHAR szComParams[50];
	DCB dcb;

	wsprintf(szPort, _T("\\\\.\\COM%d"), nPort);
	m_hIDComDev = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	if (m_hIDComDev == NULL) return(false);

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
	memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));

	COMMTIMEOUTS CommTimeOuts;
	//CommTimeOuts.ReadIntervalTimeout = 10;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 5000;
	SetCommTimeouts(m_hIDComDev, &CommTimeOuts);

	wsprintf(szComParams, _T("COM%d:%d,n,8,1"), nPort, nBaud);

	m_OverlappedRead.hEvent = CreateEvent(NULL, true, false, NULL);
	m_OverlappedWrite.hEvent = CreateEvent(NULL, true, false, NULL);

	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hIDComDev, &dcb);

	dcb.fBinary = true;
	dcb.fParity = false;

	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	unsigned char ucSet;
	ucSet = (unsigned char)((FC_RTSCTS & FC_DTRDSR) != 0);
	ucSet = (unsigned char)((FC_RTSCTS & FC_RTSCTS) != 0);
	ucSet = (unsigned char)((FC_RTSCTS & FC_XONXOFF) != 0);
	if (!SetCommState(m_hIDComDev, &dcb) ||
		!SetupComm(m_hIDComDev, 10000, 10000) ||
		m_OverlappedRead.hEvent == NULL ||
		m_OverlappedWrite.hEvent == NULL) {
		DWORD dwError = GetLastError();
		if (m_OverlappedRead.hEvent != NULL) CloseHandle(m_OverlappedRead.hEvent);
		if (m_OverlappedWrite.hEvent != NULL) CloseHandle(m_OverlappedWrite.hEvent);
		CloseHandle(m_hIDComDev);
		return(false);
	}

	m_bOpened = true;
	Sleep(50);
	return(m_bOpened);
#endif

	return false;
}

void CSerial::SetDTR()
{
#if PLATFORM_WINDOWS
	COMMCONFIG _config;
	DWORD size = sizeof(_config);
	if (!GetCommConfig(m_hIDComDev, &_config, &size))
	{
		return;
	}
	_config.dcb.fDtrControl = 1;
	_config.dcb.fRtsControl = 1;
	if (!SetCommConfig(m_hIDComDev, &_config, sizeof(_config))) {
		return;
	}
#endif
}

bool CSerial::Close(void)
{
#if PLATFORM_WINDOWS
	if (!m_bOpened || m_hIDComDev == NULL) return(true);

	if (m_OverlappedRead.hEvent != NULL) CloseHandle(m_OverlappedRead.hEvent);
	if (m_OverlappedWrite.hEvent != NULL) CloseHandle(m_OverlappedWrite.hEvent);
	CloseHandle(m_hIDComDev);
	m_bOpened = false;
	m_hIDComDev = NULL;

	return(true);
#endif

	return true;
}

bool CSerial::WriteCommByte(unsigned char ucByte)
{
#if PLATFORM_WINDOWS
	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile(m_hIDComDev, &ucByte, 1, &dwBytesWritten, &m_OverlappedWrite);
	if (!bWriteStat && (GetLastError() == ERROR_IO_PENDING)) {
		if (WaitForSingleObject(m_OverlappedWrite.hEvent, 1000)) dwBytesWritten = 0;
		else {
			GetOverlappedResult(m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, false);
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}

	return(true);
#endif

	return false;
}

int CSerial::SendData(const char *buffer, int size)
{
#if PLATFORM_WINDOWS
	if (!m_bOpened || m_hIDComDev == NULL) return(0);

	DWORD dwBytesWritten = 0;
	int i;
	for (i = 0; i < size; i++) {
		WriteCommByte(buffer[i]);
		dwBytesWritten++;
	}

	return((int)dwBytesWritten);
#endif
	return 0;
}

bool CSerial::SendData_Hex(unsigned char *buffer, int size)
{
#if PLATFORM_WINDOWS
	if (!m_bOpened || m_hIDComDev == NULL) return(0);

	BOOL bWriteStat;
	DWORD dwBytesWritten;

	bWriteStat = WriteFile(m_hIDComDev, buffer, size, &dwBytesWritten, &m_OverlappedWrite);
	if (!bWriteStat && (GetLastError() == ERROR_IO_PENDING)) {
		if (WaitForSingleObject(m_OverlappedWrite.hEvent, 1000)) dwBytesWritten = 0;
		else {
			GetOverlappedResult(m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, false);
			m_OverlappedWrite.Offset += dwBytesWritten;
		}
	}

	return(true);
#endif
	return false;
}

int CSerial::ReadDataWaiting(void)
{
#if PLATFORM_WINDOWS
	if (!m_bOpened || m_hIDComDev == NULL) return(0);

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);

	return((int)ComStat.cbInQue);
#endif
	return 0;
}

int CSerial::ReadData(unsigned char *buffer, int limit)
{
#if PLATFORM_WINDOWS
	if (!m_bOpened || m_hIDComDev == NULL) return(0);

	BOOL bReadStatus;
	DWORD dwBytesRead; /*dwErrorFlags, nTotalRead;*/
	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);
	dwBytesRead = (DWORD)ComStat.cbInQue;
	dwBytesRead = ((DWORD)limit) < (dwBytesRead) ? ((DWORD)limit) : (dwBytesRead);

	bReadStatus = ReadFile(m_hIDComDev, buffer,
		dwBytesRead, &dwBytesRead,
		&m_OverlappedRead);
	if (!bReadStatus)// / ���ReadFile��������false
	{
		if (GetLastError() == ERROR_IO_PENDING)
			//GetLastError()��������ERROR_IO_PENDING,�����������ڽ��ж����� 
		{
			DWORD a_a = WaitForSingleObject(m_OverlappedRead.hEvent, INFINITE);
			// 			ʹ��WaitForSingleObject�����ȴ���ֱ�� INFINITE ���������   �� 2000 ��ʱ�Ѵﵽ2����
			// 			�����ڶ�����������Ϻ󣬵�hEvent�¼����Ϊ���ź�

			switch (a_a)
			{
			case WAIT_FAILED:
				// 				UE_LOG(LogTemp, Warning, TEXT("[���߳�] �ȴ�ʧ��"));
				return(0);
			case 0:
				// 				UE_LOG(LogTemp, Warning, TEXT("[���߳�] �յ��˳��¼�"));
				// 				return(0);
			case 1:
				bReadStatus = GetOverlappedResult(m_hIDComDev, &m_OverlappedRead, &dwBytesRead, false);
				if (!bReadStatus)
				{
					// 					UE_LOG(LogTemp, Warning, TEXT("[���߳�] GetOverlappedResultʧ��!"));
					return(0);
				}
			}
		}
	}
	// 	PurgeComm(m_hIDComDev, PURGE_TXABORT |
	// 		PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	return dwBytesRead;
#endif
	return 0;

}