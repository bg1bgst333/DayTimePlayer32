// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// �����o�̏�����.
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clear�ŃN���A.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clear�ŃN���A.
	m_pStatic = NULL;	// m_pStatic��NULL�ŏ�����.
	m_pButton = NULL;	// m_pButton��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������.
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clear�ŃN���A.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clear�ŃN���A.
	if (m_pStatic != NULL){	// m_pStatic��NULL�łȂ����.
		DestroyWindow(m_pStatic->m_hWnd);	// DestroyWindow��m_pStatic->m_hWnd��j��.
		delete m_pStatic;	// delete��m_pStatic�����.
		m_pStatic = NULL;	// m_pStatic��NULL���Z�b�g.
	}
	if (m_pButton != NULL){	// m_pButton��NULL�łȂ����.
		DestroyWindow(m_pButton->m_hWnd);	// DestroyWindow��m_pStatic->m_hWnd��j��.
		delete m_pButton;	// delete��m_pButton�����.
		m_pButton = NULL;	// m_pButton��NULL���Z�b�g.
	}

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��IDR_MENU1���g��.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��o�[�W����.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[lpszMenuName���g��.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), lpszMenuName);	// ���j���[�����w�肷��.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ���j���[�o�[�̍쐬.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBar�I�u�W�F�N�gm_pMenuBar���쐬.

	// ���j���[�̃��[�h.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenu��IDR_MENU1�����[�h.

	// ���j���[�̃Z�b�g.
	m_pMenuBar->SetMenu(hwnd);	// SetMenu��hwnd�Ƀ��j���[���Z�b�g.

	// �X�^�e�B�b�N�R���g���[���I�u�W�F�N�g�̍쐬
	m_pStatic = new CStatic();	// CStatic�I�u�W�F�N�g�̍쐬.

	// �X�^�e�B�b�N�R���g���[���̃E�B���h�E�쐬.
	m_pStatic->Create(_T("---"), SS_SIMPLE, 0, 0, 640, 50, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pStatic->Create�ō쐬.

	// �{�^���R���g���[���I�u�W�F�N�g�̍쐬
	m_pButton = new CButton();	// CButton�I�u�W�F�N�g�̍쐬.

	// �{�^���R���g���[���̃E�B���h�E�쐬.
	m_pButton->Create(_T("�Đ�"), BS_PUSHBUTTON, 0, 50, 100, 50, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pButton->Create�ō쐬.

	// ���j���[�n���h���̒ǉ�.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandler��ID_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.

	// �{�^���n���h���̒ǉ�.
	AddCommandHandler(WM_APP + 2, BN_CLICKED, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnPlay);	// AddCommandHandler��WM_APP + 2�ɑ΂���n���h��CMainWindow::OnPlay��o�^.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// �q�E�B���h�E�I�u�W�F�N�g�̔j��.
	if (m_pStatic != NULL){	// m_pStatic��NULL�łȂ����.
		DestroyWindow(m_pStatic->m_hWnd);	// DestroyWindow��m_pStatic->m_hWnd��j��.
		delete m_pStatic;	// delete��m_pStatic�����.
		m_pStatic = NULL;	// m_pStatic��NULL���Z�b�g.
	}
	if (m_pButton != NULL){	// m_pButton��NULL�łȂ����.
		DestroyWindow(m_pButton->m_hWnd);	// DestroyWindow��m_pStatic->m_hWnd��j��.
		delete m_pButton;	// delete��m_pButton�����.
		m_pButton = NULL;	// m_pButton��NULL���Z�b�g.
	}

	// �e�E�B���h�E��OnDestroy���Ă�.
	CMenuWindow::OnDestroy();	// CMenuWindow::OnDestroy���Ă�.

}

// "�J��"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(NULL, _T("wav"), _T("�����t�@�C��(*.wav)|*.wav|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.
		
		// �I�����ꂽ�t�@�C������\��.
		m_tstrCurrentFileName = selDlg.m_tstrPath;	// m_tstrCurrentFileName��selDlg.m_tstrPath���Z�b�g.
		TCHAR tszTitle[_MAX_PATH] = {0};	// �t�@�C�����̃^�C�g��(�t�@�C���������̂�.)tszTitle��{0}�ŏ�����.
		GetFileTitle(selDlg.m_tstrPath.c_str(), tszTitle, _MAX_PATH);	// GetFileTitle�Ń^�C�g�����擾.
		m_tstrCurrentFileNameTitle = tszTitle;	// m_tstrCurrentFileNameTitle��tszTitle���Z�b�g.
		m_pStatic->SetText(m_tstrCurrentFileNameTitle.c_str());	// m_pStatic->SetText��m_tstrCurrentFileNameTitle���Z�b�g.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

		// ���������̂�0��Ԃ�.
		return 0;	// 0��Ԃ�.

	}
	else{	// �L�����Z���̏ꍇ.

		// ���̃^�C�g����\��.
		m_pStatic->SetText(m_tstrCurrentFileNameTitle.c_str());	// m_pStatic->SetText��m_tstrCurrentFileNameTitle���Z�b�g.

	}

	// �������Ă��Ȃ��̂�-1.
	return -1;	// return��-1��Ԃ�.

}

// "�Đ�"�{�^���������ꂽ���̃n���h��.
int CMainWindow::OnPlay(WPARAM wParam, LPARAM lParam){

	// �I�����ꂽ�����t�@�C�����Đ�.
	PlaySound(m_tstrCurrentFileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);	// PlaySound��m_tstrCurrentFileName���Đ�.

	// ���������̂�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}