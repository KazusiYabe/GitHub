/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//�t�H���g�����̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "font.h"

//########## �O���[�o���ϐ� ##########

//�t�H���g�f�[�^���Ǘ�
FONT fontdef;			//�f�t�H���g�̃t�H���g
FONT fontTitlePush;		//�^�C�g���̃t�H���g

//########## �֐� ##########

/// <summary>
/// �t�H���g�̓Ǎ�
/// </summary>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL MY_FONT_LOAD(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_TANUKI_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_TANUKI_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_JIYU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�f�t�H���g�t�H���g�̏���������
	MY_FONT_SET(
		&fontdef,			//�ݒ肷��t�H���g
		DEF_FONT_NAME,		//�t�H���g�̖��O���R�s�[
		DEF_FONT_SIZE,		//�t�H���g�̃T�C�Y
		DEF_FONT_THINCK,	//�t�H���g�̑���
		DEF_FONT_TYPE		//�t�H���g�̃^�C�v
	);

	//�f�t�H���g�t�H���g��S�̂ɔ��f
	MY_FONT_DRAWSET(fontdef);

	//�f�t�H���g�t�H���g�̃n���h���쐬
	fontdef.handle = CreateFontToHandle(
		fontdef.Name,	//�t�H���g����ݒ�
		fontdef.Size, 	//�t�H���g�̃T�C�Y��ݒ�
		fontdef.Thinck, //�t�H���g�̑�����ݒ�
		fontdef.Type	//�t�H���g�̃^�C�v��ݒ�
	);

	//��������������������������������������������������������������������������������������������������������������

	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_DELTA_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_DELTA_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�t�H���g���쐬
	MY_FONT_SET(&fontTitlePush, FONT_DELTA_NAME, 80, 1, DEF_FONT_TYPE);
	fontTitlePush.handle = CreateFontToHandle(
		fontTitlePush.Name,		//�t�H���g����ݒ�
		fontTitlePush.Size, 	//�t�H���g�̃T�C�Y��ݒ�
		fontTitlePush.Thinck,	//�t�H���g�̑�����ݒ�
		fontTitlePush.Type		//�t�H���g�̃^�C�v��ݒ�
	);


	return TRUE;
}

/// <summary>
/// �����̃t�H���g�\���̂֐ݒ肷��
/// </summary>
/// <param name="f">�ݒ肷��t�H���g�\����</param>
/// <param name="name">�t�H���g��</param>
/// <param name="size">�t�H���g�̃T�C�Y</param>
/// <param name="thinck">�t�H���g�̑���</param>
/// <param name="type">�t�H���g�̃^�C�v</param>
/// <returns></returns>
VOID MY_FONT_SET(FONT* f, const char* name, int size, int thinck, int type)
{
	strcpy_sDx(f->Name, STR_MAX, name);	//�t�H���g�̖��O���R�s�[
	f->Size = size;						//�t�H���g�̃T�C�Y
	f->Thinck = thinck;					//�t�H���g�̑���
	f->Type = type;						//�t�H���g�̃^�C�v
	return;
}

/// <summary>
/// �t�H���g����ʑS�̂ɔ��f������
/// </summary>
/// <param name="f">�ݒ肷��t�H���g�\����</param>
/// <returns></returns>
VOID MY_FONT_DRAWSET(FONT f)
{
	ChangeFont(f.Name);				//�t�H���g����ݒ�
	SetFontSize(f.Size);			//�t�H���g�̃T�C�Y��ݒ�
	SetFontThickness(f.Thinck);		//�t�H���g�̑�����ݒ�
	ChangeFontType(f.Type);			//�t�H���g�̃^�C�v��ݒ�

	return;
}

/// <summary>
/// �t�H���g�̍폜
/// </summary>
/// <returns></returns>
VOID MY_FONT_DELETE(VOID)
{
	//�f�t�H���g�t�H���g�폜
	DeleteFontToHandle(fontdef.handle);
	DeleteFontToHandle(fontTitlePush.handle);

	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_TANUKI_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_DELTA_NAME, FR_PRIVATE, NULL);

	return;
}