#include <windows.h>

typedef
	int
	WINAPI
	FUN_MessageBoxW(
	__in_opt HWND hWnd,
	__in_opt LPCWSTR lpText,
	__in_opt LPCWSTR lpCaption,
	__in UINT uType);

static FUN_MessageBoxW *OLD_MessageBoxW=MessageBoxW;  

int
	WINAPI
	NEW_MessageBoxW(
	__in_opt HWND hWnd,
	__in_opt LPCWSTR lpText,
	__in_opt LPCWSTR lpCaption,
	__in UINT uType)
{  

	//�޸��������������ԭ����  
	int ret=OLD_MessageBoxW(hWnd,L"����������޸�",L"[����]",uType);  
	return ret;  
}