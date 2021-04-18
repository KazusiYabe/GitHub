/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//�L�[�������͏����̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "font.h"
#include "InputStr.h"

//########## �O���[�o���ϐ� ##########

//�L�[�������͂̃f�[�^���Ǘ�
INPUTSTR inputstr;

//���͒��̃T���v���t�H���g
FONT sampleInputStrFont;

//########## �֐� ##########

/// <summary>
/// �L�[���̓n���h�������
/// </summary>
/// <returns></returns>
VOID MY_INPUT_STR_CREATE(VOID)
{
	//�L�[���͒��łȂ����
	if (inputstr.CanInputStr == FALSE)
	{
		// �L�[���̓n���h�������
		inputstr.handle = MakeKeyInput(
			inputstr.StrMax,				//���͍ő啶����H
			inputstr.CancelValidFlag,		//ESC�ŃL�����Z���ł���悤�ɂ���H
			inputstr.SingleCharOnlyFlag,	//���p���͂̂�OK�ɂ���H
			inputstr.NumCharOnlyFlag		//�������͂̂�OK�ɂ���H
		);

		//���̓o�b�t�@������
		for (int i = 0; i < INPUTSTR_MAX; i++) { inputstr.StrBuf[i] = '\0'; }

		//�`��p�T���v�������񐶐�
		for (int i = 0; i < INPUTSTR_MAX - 1; i++) { strcat(&inputstr.drawSampleString[i], "a"); }
		inputstr.drawSampleString[INPUTSTR_MAX - 1] = '\0';

		//�쐬�����L�[���̓n���h����L���ɂ���(�L�[���͊J�n)
		SetActiveKeyInput(inputstr.handle);

		//�L�[�������͊J�n
		inputstr.CanInputStr = TRUE;

		//�T���v���̃t�H���g���쐬����
		MY_FONT_SET(&sampleInputStrFont, "�l�r �S�V�b�N", 30, 1, DX_FONTTYPE_ANTIALIASING);
		sampleInputStrFont.handle = CreateFontToHandle(sampleInputStrFont.Name, sampleInputStrFont.Size, sampleInputStrFont.Thinck, sampleInputStrFont.Type);
	}

	return;
}

/// <summary>
/// �L�[���͂̓��͏����X�V����
/// </summary>
/// <param name="old">�ȑO�̃Q�[���V�[��</param>
/// <param name="now">���݂̃Q�[���V�[��</param>
/// <returns></returns>
VOID MY_INPUT_STR_UPDATE(GAME_SCENE old, GAME_SCENE now)
{
	//�V�[����؂�ւ���Ƃ�
	if (old != now)
	{
		//�L�[�������̓n���h�������폜
		MY_INPUT_STR_DELETE();
	}

	return;
}

/// <summary>
/// �L�[���͂��s��
/// </summary>
/// <returns></returns>
VOID MY_INPUT_STR_PROC(VOID)
{
	//�L�[���͒��ł����
	if (inputstr.CanInputStr == TRUE)
	{
		//���͂�����������
		if (CheckKeyInput(inputstr.handle) > 0)
		{
			//���͂��ꂽ��������擾����
			GetKeyInputString(inputstr.StrBuf, inputstr.handle);

			//�L�[���̓n���h���폜
			MY_INPUT_STR_DELETE();

			//���͂ł��Ȃ�����
			inputstr.CanInputStr = FALSE;
		}
	}

	return;
}

/// <summary>
/// �L�[���͒��̕������`�悷��
/// </summary>
/// <param name="x">�������`�悷��X�J�n�ʒu</param>
/// <param name="y">�������`�悷��Y�J�n�ʒu</param>
/// <param name="font">�`�悷��t�H���g</param>
/// <param name="c">�`�悷�镶���F</param>
/// <returns></returns>
VOID MY_INPUT_STR_DRAW(int x, int y, FONT font, unsigned int c)
{
	//�L�[�������͂��ł���Ƃ�
	if (inputstr.CanInputStr == TRUE)
	{
		//���̘͂g����`�悷��
		int fontWidth = GetDrawStringWidthToHandle(inputstr.drawSampleString, strlen(inputstr.drawSampleString), font.handle);	//�����擾
		int fontHeight = GetFontSizeToHandle(font.handle);							//�������擾
		DrawBox(x - 1, y - 1, x + fontWidth + 1, y + fontHeight + 1, GetColor(255, 255, 255), FALSE);

		//���͕������`�悷��
		FONT oldFont;	//�ȑO�̃t�H���g

		//�f�t�H���g�t�H���g�̏����擾
		GetFontStateToHandle(oldFont.Name, &oldFont.Size, &oldFont.Thinck, GetDefaultFontHandle(), &oldFont.Type);

		//�`�悷��t�H���g���Z�b�g����
		MY_FONT_DRAWSET(font);

		//���͒��̕�����̐F��ς���
		SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, c);

		//���͒��̕�����`��
		DrawKeyInputString(x, y, inputstr.handle);

		//�`�悷��ȑO�̃t�H���g���Z�b�g����
		MY_FONT_DRAWSET(oldFont);
	}

	return;
}

/// <summary>
/// �L�[���̓n���h�����폜����
/// </summary>
/// <returns></returns>
VOID MY_INPUT_STR_DELETE(VOID)
{
	//�L�[���̓n���h�����폜����
	DeleteKeyInput(inputstr.handle);

	//���͂ł��Ȃ�����
	inputstr.CanInputStr = FALSE;

	//�T���v���̃t�H���g���폜����
	DeleteFontToHandle(sampleInputStrFont.handle);

	return;
}
