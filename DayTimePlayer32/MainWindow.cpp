// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// メンバの初期化.
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clearでクリア.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clearでクリア.
	m_pStatic = NULL;	// m_pStaticをNULLで初期化.
	m_pButton = NULL;	// m_pButtonをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理.
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clearでクリア.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clearでクリア.
	if (m_pStatic != NULL){	// m_pStaticがNULLでなければ.
		DestroyWindow(m_pStatic->m_hWnd);	// DestroyWindowでm_pStatic->m_hWndを破棄.
		delete m_pStatic;	// deleteでm_pStaticを解放.
		m_pStatic = NULL;	// m_pStaticにNULLをセット.
	}
	if (m_pButton != NULL){	// m_pButtonがNULLでなければ.
		DestroyWindow(m_pButton->m_hWnd);	// DestroyWindowでm_pStatic->m_hWndを破棄.
		delete m_pButton;	// deleteでm_pButtonを解放.
		m_pButton = NULL;	// m_pButtonにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはIDR_MENU1を使う.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューlpszMenuNameを使う.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), lpszMenuName);	// メニュー名を指定する.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// メニューバーの作成.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBarオブジェクトm_pMenuBarを作成.

	// メニューのロード.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenuでIDR_MENU1をロード.

	// メニューのセット.
	m_pMenuBar->SetMenu(hwnd);	// SetMenuでhwndにメニューをセット.

	// スタティックコントロールオブジェクトの作成
	m_pStatic = new CStatic();	// CStaticオブジェクトの作成.

	// スタティックコントロールのウィンドウ作成.
	m_pStatic->Create(_T("---"), SS_SIMPLE, 0, 0, 640, 50, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pStatic->Createで作成.

	// ボタンコントロールオブジェクトの作成
	m_pButton = new CButton();	// CButtonオブジェクトの作成.

	// ボタンコントロールのウィンドウ作成.
	m_pButton->Create(_T("再生"), BS_PUSHBUTTON, 0, 50, 100, 50, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pButton->Createで作成.

	// メニューハンドラの追加.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandlerでID_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.

	// ボタンハンドラの追加.
	AddCommandHandler(WM_APP + 2, BN_CLICKED, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnPlay);	// AddCommandHandlerでWM_APP + 2に対するハンドラCMainWindow::OnPlayを登録.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// 子ウィンドウオブジェクトの破棄.
	if (m_pStatic != NULL){	// m_pStaticがNULLでなければ.
		DestroyWindow(m_pStatic->m_hWnd);	// DestroyWindowでm_pStatic->m_hWndを破棄.
		delete m_pStatic;	// deleteでm_pStaticを解放.
		m_pStatic = NULL;	// m_pStaticにNULLをセット.
	}
	if (m_pButton != NULL){	// m_pButtonがNULLでなければ.
		DestroyWindow(m_pButton->m_hWnd);	// DestroyWindowでm_pStatic->m_hWndを破棄.
		delete m_pButton;	// deleteでm_pButtonを解放.
		m_pButton = NULL;	// m_pButtonにNULLをセット.
	}

	// 親ウィンドウのOnDestroyを呼ぶ.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroyを呼ぶ.

}

// "開く"を選択された時のハンドラ.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "開く"ファイルの選択.
	CFileDialog selDlg(NULL, _T("wav"), _T("音声ファイル(*.wav)|*.wav|すべてのファイル(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialogで"開く"ファイルダイアログを表示.
		
		// 選択されたファイル名を表示.
		m_tstrCurrentFileName = selDlg.m_tstrPath;	// m_tstrCurrentFileNameにselDlg.m_tstrPathをセット.
		TCHAR tszTitle[_MAX_PATH] = {0};	// ファイル名のタイトル(ファイル名部分のみ.)tszTitleを{0}で初期化.
		GetFileTitle(selDlg.m_tstrPath.c_str(), tszTitle, _MAX_PATH);	// GetFileTitleでタイトルを取得.
		m_tstrCurrentFileNameTitle = tszTitle;	// m_tstrCurrentFileNameTitleにtszTitleをセット.
		m_pStatic->SetText(m_tstrCurrentFileNameTitle.c_str());	// m_pStatic->SetTextでm_tstrCurrentFileNameTitleをセット.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

		// 処理したので0を返す.
		return 0;	// 0を返す.

	}
	else{	// キャンセルの場合.

		// 元のタイトルを表示.
		m_pStatic->SetText(m_tstrCurrentFileNameTitle.c_str());	// m_pStatic->SetTextでm_tstrCurrentFileNameTitleをセット.

	}

	// 処理していないので-1.
	return -1;	// returnで-1を返す.

}

// "再生"ボタンが押された時のハンドラ.
int CMainWindow::OnPlay(WPARAM wParam, LPARAM lParam){

	// 選択された音声ファイルを再生.
	PlaySound(m_tstrCurrentFileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);	// PlaySoundでm_tstrCurrentFileNameを再生.

	// 処理したので0を返す.
	return 0;	// 0を返す.

}