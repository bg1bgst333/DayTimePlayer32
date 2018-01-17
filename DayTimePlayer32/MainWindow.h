// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <string>	// std::string
// 独自のヘッダ
#include "Static.h"	// CStatic
#include "Button.h"	// CButton
#include "MenuWindow.h"	// CMenuWindow

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// メインウィンドウクラスCMainWindow
class CMainWindow : public CMenuWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrCurrentFileName;	// 現在選択しているファイル名.(フルパス)
		tstring m_tstrCurrentFileNameTitle;	// 現在選択しているファイル名.(フルパスの中のファイル名部分だけ.)
		CStatic *m_pStatic;	// CStaticオブジェクトポインタm_pStatic.
		CButton *m_pButton;	// CButtonオブジェクトポインタm_pButton.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName);	// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "開く"を選択された時のハンドラ.
		virtual int OnPlay(WPARAM wParam, LPARAM lParam);	// "再生"ボタンが押された時のハンドラ.

};

#endif