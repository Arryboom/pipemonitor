// injectdll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../detours/include/detours.h"
#include <windows.h>

static int (WINAPI* OLD_MessageBoxW)(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType)=MessageBoxW;  
int WINAPI NEW_MessageBoxW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType)  
{  

	//�޸��������������ԭ����  
	int ret=OLD_MessageBoxW(hWnd,L"����������޸�",L"[����]",uType);  
	return ret;  
}  

VOID Hook()  
{  
	//DetourRestoreAfterWith();  
	DetourTransactionBegin();  
	DetourUpdateThread(GetCurrentThread());  

	//�������������ε���DetourAttach������HOOK�������  
	DetourAttach(&(PVOID&)OLD_MessageBoxW,NEW_MessageBoxW);  

	DetourTransactionCommit();  
}  

VOID UnHook()  
{  
	DetourTransactionBegin();  
	DetourUpdateThread(GetCurrentThread());  

	//�������������ε���DetourDetach,���������������HOOK  
	DetourDetach(&(PVOID&)OLD_MessageBoxW,NEW_MessageBoxW);  

	DetourTransactionCommit();  

}  

unsigned __stdcall threadproc(void*)
{
	::MessageBoxW(NULL,L"inject",L"success",MB_OK);
	Hook();  
	MessageBoxW(0,L"������Ϣ��",L"����",0);  
	UnHook();  
	return 0;
}