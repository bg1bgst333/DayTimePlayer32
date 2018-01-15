// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// �����o�̏�����.
	m_hStatic = NULL;	// m_hStatic��NULL�ŏ�����.
	m_hButton = NULL;	// m_hButton��NULL�ŏ�����.
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clear�ŃN���A.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clear�ŃN���A.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������.
	if (m_hStatic != NULL){	// m_hStatic��NULL�łȂ���.
		DestroyWindow(m_hStatic);	// DestroyWindow��m_hStatic��j��.
		m_hStatic = NULL;	// m_hStaic��NULL���Z�b�g.
	}
	if (m_hButton != NULL){	// m_hButton��NULL�łȂ���.
		DestroyWindow(m_hButton);	// DestroyWindow��m_hButton��j��.
		m_hButton = NULL;	// m_hButton��NULL���Z�b�g.
	}
	m_tstrCurrentFileName.clear();	// m_tstrCurrentFileName.clear�ŃN���A.
	m_tstrCurrentFileNameTitle.clear();	// m_tstrCurrentFileName.clear�ŃN���A.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��IDR_MENU1���g��.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �X�^�e�B�b�N�R���g���[���̍쐬
	m_hStatic = CreateWindow(_T("Static"), _T("---"), WS_CHILD | WS_VISIBLE | SS_SIMPLE, 0, 0, 640, 50, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance, NULL);	// CreateWindow�ŃX�^�e�B�b�N�R���g���[��m_hStatic���쐬.(�E�B���h�E�N���X����"Static".)

	// �{�^���R���g���[���̍쐬
	m_hButton = CreateWindow(_T("Button"), _T("�Đ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 50, 100, 50, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance, NULL);	// CreateWindow�Ń{�^���R���g���[��m_hButton���쐬.(�E�B���h�E�N���X����"Button".)

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// �I�����b�Z�[�W�̑��M.
	PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

}

// �R�}���h������������.
BOOL CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// �R�}���h�̏���.
	switch (LOWORD(wParam)){	// LOWORD(wParam)�Ń��\�[�XID���킩��̂�, ���̒l���Ƃɏ�����U�蕪����.

		// "�J��(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPEN�u���b�N
			{

				// "�J��"�t�@�C���̑I��.
				// �\���́E�z��̏�����.
				OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.
				TCHAR tszPath[_MAX_PATH] = {0};	// �t�@�C���p�XtszPath��{0}�ŏ�����.
				// �p�����[�^�̃Z�b�g.
				ofn.lStructSize = sizeof(OPENFILENAME);	// sizeof��OPENFILENAME�\���̂̃T�C�Y���Z�b�g.
				ofn.hwndOwner = m_hWnd;	// m_hWnd���Z�b�g.
				ofn.lpstrFilter = _T("�����t�@�C��(*.wav)\0*.wav\0���ׂẴt�@�C��(*.*)\0*.*\0\0");	// �����t�@�C���Ƃ��ׂẴt�@�C���̃t�B���^���Z�b�g.
				ofn.lpstrFile = tszPath;	// tszPath���Z�b�g.
				ofn.nMaxFile = _MAX_PATH;	// _MAX_PATH���Z�b�g.
				ofn.Flags = OFN_FILEMUSTEXIST;	// �t�@�C�������݂��Ȃ��Ɣ������Ȃ�.
				// "�J��"�t�@�C���_�C�A���O�̕\��.
				BOOL bRet = GetOpenFileName(&ofn);	// GetOpenFileName�Ńt�@�C���_�C�A���O��\����, �I�����ꂽ�t�@�C�������擾����.(�߂�l��bRet�Ɋi�[.)
				if (bRet){	// ����ɑI�����ꂽ.
					
					// �I�����ꂽ�t�@�C������\��.
					m_tstrCurrentFileName = tszPath;	// m_tstrCurrentFileName��tszPath���Z�b�g.
					TCHAR tszTitle[_MAX_PATH] = {0};	// �t�@�C�����̃^�C�g��(�t�@�C���������̂�.)tszTitle��{0}�ŏ�����.
					GetFileTitle(tszPath, tszTitle, _MAX_PATH);	// GetFileTitle�Ń^�C�g�����擾.
					m_tstrCurrentFileNameTitle = tszTitle;	// m_tstrCurrentFileNameTitle��tszTitle���Z�b�g.
					SetWindowText(m_hStatic, m_tstrCurrentFileNameTitle.c_str());	// SetWindowText��m_hStatic��m_tstrCurrentFileNameTitle���Z�b�g.
					InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

				}
				else{	// �L�����Z���̏ꍇ.

					// ���̃^�C�g����\��.
					SetWindowText(m_hStatic, m_tstrCurrentFileNameTitle.c_str());	// SetWindowText��m_hStatic��m_tstrCurrentFileNameTitle���Z�b�g.

				}

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// "�Đ�"�{�^��
		case WM_APP + 2:

			// WM_APP + 2�u���b�N
			{

				// �I�����ꂽ�����t�@�C�����Đ�.
				PlaySound(m_tstrCurrentFileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);	// PlaySound��m_tstrCurrentFileName���Đ�.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ����ȊO.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

	}

	// TRUE.
	return TRUE;	// TRUE��Ԃ�.

}