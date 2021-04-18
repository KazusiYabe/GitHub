/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//�L�[�{�[�h�����̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "keyboard.h"
#include "FPS.h"

//########## �O���[�o���ϐ� ##########

//�L�[���͂��擾
KEYBOARD keyboard;

//########## �֐� ##########

/// <summary>
/// �L�[�̓��͏�Ԃ��X�V����֐�
/// </summary>
/// <returns></returns>
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//�ꎞ�I�Ɍ��݂̃L�[�̓��͏�Ԃ��i�[����
	char TempKey[KEY_KIND_MAX];

	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		keyboard.OldAllKeyState[i] = keyboard.AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < KEY_KIND_MAX; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			keyboard.AllKeyState[i]++;	//������Ă���
		}
		else
		{
			keyboard.AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

/// <summary>
/// �L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <returns>�����Ă�����TRUE</returns>
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (keyboard.AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

/// <summary>
/// �L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <returns>�����グ����TRUE</returns>
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (keyboard.OldAllKeyState[KEY_INPUT_] >= 1	//���O�͉����Ă���
		&& keyboard.AllKeyState[KEY_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�L�[�������グ�Ă���
	}
	else
	{
		return FALSE;	//�L�[�������グ�Ă��Ȃ�
	}
}

/// <summary>
/// �L�[���N���b�N�������A�L�[�R�[�h�Ŕ��f����
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <returns>�N���b�N������TRUE</returns>
BOOL MY_KEY_CLICK(int KEY_INPUT_)
{
	if (keyboard.OldAllKeyState[KEY_INPUT_] == 0		//���O�͉����Ă��Ȃ���
		&& keyboard.AllKeyState[KEY_INPUT_] >= 1)	//���͉����Ă���Ƃ�
	{
		return TRUE;	//�L�[���N���b�N�����i���������Ă��A�P��̂ݔ����j
	}
	else
	{
		return FALSE;	//�L�[���N���b�N���Ă��Ȃ����A���������Ă���
	}
}

/// <summary>
/// �L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
/// </summary>
/// <param name="KEY_INPUT_">KEY_INPUT_???</param>
/// <param name="milliTime">�L�[�����������Ă��鎞��(�~���b)</param>
/// <returns>���������Ă�����TRUE</returns>
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int milliTime)
{
	float MilliSec = 1000.0f;	//�P�b��1000�~���b

	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = (milliTime / MilliSec) * GAME_FPS;

	if (keyboard.AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}