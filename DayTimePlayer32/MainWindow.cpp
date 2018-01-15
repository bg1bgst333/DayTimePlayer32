// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// メンバの初期化.
	m_hStatic = NULL;	// m_hStaticをNULLで初期化.
	m_hButton = NULL;	// m_hButtonをNULLで初期化.
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clearでクリア.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clearでクリア.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理.
	if (m_hStatic != NULL){	// m_hStaticがNULLでない時.
		DestroyWindow(m_hStatic);	// DestroyWindowでm_hStaticを破棄.
		m_hStatic = NULL;	// m_hStaicにNULLをセット.
	}
	if (m_hButton != NULL){	// m_hButtonがNULLでない時.
		DestroyWindow(m_hButton);	// DestroyWindowでm_hButtonを破棄.
		m_hButton = NULL;	// m_hButtonにNULLをセット.
	}
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clearでクリア.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clearでクリア.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはIDR_MENU1を使う.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClassで登録.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// スタティックコントロールの作成
	m_hStatic = CreateWindow(_T("Static"), _T("---"), WS_CHILD | WS_VISIBLE | SS_SIMPLE, 0, 0, 640, 50, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance, NULL);	// CreateWindowでスタティックコントロールm_hStaticを作成.(ウィンドウクラス名は"Static".)

	// ボタンコントロールの作成
	m_hButton = CreateWindow(_T("Button"), _T("再生"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 50, 100, 50, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance, NULL);	// CreateWindowでボタンコントロールm_hButtonを作成.(ウィンドウクラス名は"Button".)

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// 終了メッセージの送信.
	PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

}

// コマンドが発生した時.
BOOL CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// コマンドの処理.
	switch (LOWORD(wParam)){	// LOWORD(wParam)でリソースIDがわかるので, その値ごとに処理を振り分ける.

		// "開く(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPENブロック
			{

				// "開く"ファイルの選択.
				// 構造体・配列の初期化.
				OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.
				TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
				// パラメータのセット.
				ofn.lStructSize = sizeof(OPENFILENAME);	// sizeofでOPENFILENAME構造体のサイズをセット.
				ofn.hwndOwner = m_hWnd;	// m_hWndをセット.
				ofn.lpstrFilter = _T("音声ファイル(*.wav)\0*.wav\0すべてのファイル(*.*)\0*.*\0\0");	// 音声ファイルとすべてのファイルのフィルタをセット.
				ofn.lpstrFile = tszPath;	// tszPathをセット.
				ofn.nMaxFile = _MAX_PATH;	// _MAX_PATHをセット.
				ofn.Flags = OFN_FILEMUSTEXIST;	// ファイルが存在しないと抜けられない.
				// "開く"ファイルダイアログの表示.
				BOOL bRet = GetOpenFileName(&ofn);	// GetOpenFileNameでファイルダイアログを表示し, 選択されたファイル名を取得する.(戻り値をbRetに格納.)
				if (bRet){	// 正常に選択された.
					
					// 選択されたファイル名を表示.
					m_tstrCurrentFileName = tszPath;	// m_tstrCurrentFileNameにtszPathをセット.
					TCHAR tszTitle[_MAX_PATH] = {0};	// ファイル名のタイトル(ファイル名部分のみ.)tszTitleを{0}で初期化.
					GetFileTitle(tszPath, tszTitle, _MAX_PATH);	// GetFileTitleでタイトルを取得.
					m_tstrCurrentFileNameTitle = tszTitle;	// m_tstrCurrentFileNameTitleにtszTitleをセット.
					SetWindowText(m_hStatic, m_tstrCurrentFileNameTitle.c_str());	// SetWindowTextでm_hStaticにm_tstrCurrentFileNameTitleをセット.
					InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで更新.

				}
				else{	// キャンセルの場合.

					// 元のタイトルを表示.
					SetWindowText(m_hStatic, m_tstrCurrentFileNameTitle.c_str());	// SetWindowTextでm_hStaticにm_tstrCurrentFileNameTitleをセット.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// "再生"ボタン
		case WM_APP + 2:

			// WM_APP + 2ブロック
			{

				// 選択された音声ファイルを再生.
				PlaySound(m_tstrCurrentFileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);	// PlaySoundでm_tstrCurrentFileNameを再生.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// それ以外.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// TRUE.
	return TRUE;	// TRUEを返す.

}