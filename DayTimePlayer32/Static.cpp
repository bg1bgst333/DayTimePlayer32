// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Static.h"	// CStatic

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CStatic::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�N���X����"Static"�ȃJ�X�^���R���g���[�����쐬.
	return CCustomControl::Create(_T("Static"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Create�ŃX�^�e�B�b�N�R���g���[�����쐬.

}