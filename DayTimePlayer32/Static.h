// ��d�C���N���[�h�h�~
#ifndef __STATIC_H__
#define __STATIC_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl

// �X�^�e�B�b�N�R���g���[���N���XCStatic
class CStatic : public CCustomControl{

	// public�����o
	public:

		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		
};

#endif