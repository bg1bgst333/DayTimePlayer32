// ヘッダのインクルード
// 独自のヘッダ
#include "Static.h"	// CStatic

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CStatic::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウクラス名が"Static"なカスタムコントロールを作成.
	return CCustomControl::Create(_T("Static"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Createでスタティックコントロールを作成.

}