/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//�Q�[���p�b�h�����̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "FPS.h"
#include "gamepad.h"

//########## �O���[�o���ϐ� ##########

//�Q�[���p�b�h�̃f�[�^���Ǘ�
int padConnectNum = 0;			//�p�b�h�̐ڑ���
GAMEPAD gamepad[PAD_MAX];		//GAMEPAD�f�[�^���Ǘ�

//�f�o�b�O�p
DEBUG_GAMEPAD debug[PAD_MAX];	//�Q�[���p�b�h�̓���f�o�b�O�p

//########## �֐� ##########

/// <summary>
/// �p�b�h�̏�������������
/// </summary>
/// <returns></returns>
VOID MY_PAD_INIT(VOID)
{
	//�p�b�h�̐ڑ������擾
	padConnectNum = GetJoypadNum();

	//�p�b�h���͍ő�S�܂Łi�T�ȏ�͏������Ȃ��j
	if (DX_INPUT_PAD4 < padConnectNum) { padConnectNum = DX_INPUT_PAD4; }

	//�p�b�h�̐��ɉ����ď������s��
	for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
	{
		//�U�����Đڑ��e�X�g(�U���t���łȂ��p�b�h�́A���R�U�����Ȃ��E�E�E)
		//StartJoypadVibration(cnt, PAD_TEST_POWER, PAD_TEST_MSEC);

		//�p�b�h�̃A�i���O�X�e�B�b�N�̖����͈͂�ݒ肷��
		SetJoypadDeadZone(cnt, PAD_DEADZONE);

		//���͏���������
		gamepad[cnt].InputState = -1;
		gamepad[cnt].NewAnalogX = 0;
		gamepad[cnt].NewAnalogY = 0;
		gamepad[cnt].OldAnalogX = 0;
		gamepad[cnt].OldAnalogY = 0;

		//�{�^������������
		for (int i = PADBTN_DOWN; i <= PADBTN_12; i++)
		{
			gamepad[cnt].AllButtonState[i] = 0;
			gamepad[cnt].OldButtonKeyState[i] = 0;
		}
	}

	if (DEBUG_MODE == TRUE)	//�f�o�b�O���[�h�Ȃ�
	{
		//�f�o�b�O�̂Ƃ��̉~�̐F��ݒ肷��
		debug[DX_INPUT_PAD1].Color = GetColor(255, 0, 0);
		debug[DX_INPUT_PAD2].Color = GetColor(0, 255, 0);
		debug[DX_INPUT_PAD3].Color = GetColor(0, 0, 255);
		debug[DX_INPUT_PAD4].Color = GetColor(255, 255, 0);
	}

	return;
}

/// <summary>
/// �p�b�h�̓��͏����X�V����
/// </summary>
/// <returns></returns>
VOID MY_PAD_UPDATE(VOID)
{
	//�p�b�h�̐��ɉ����ď������s��
	for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
	{
		//�O��̃A�i���O���o�[�̌X�����ۑ�
		gamepad[cnt].OldAnalogX = gamepad[cnt].NewAnalogX;
		gamepad[cnt].OldAnalogY = gamepad[cnt].NewAnalogY;

		//�O��̃{�^�����͂�ۑ�
		for (int i = PADBTN_DOWN; i <= PADBTN_12; i++)
		{
			gamepad[cnt].OldButtonKeyState[i] = gamepad[cnt].AllButtonState[i];
		}

		//�A�i���O���o�[�̌X������擾
		GetJoypadAnalogInput(&(gamepad[cnt].NewAnalogX), &(gamepad[cnt].NewAnalogY), cnt);

		//�p�b�h�̏�Ԃ����
		gamepad[cnt].InputState = GetJoypadInputState(cnt);

		//���{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_DOWN) == PAD_INPUT_DOWN) { gamepad[cnt].AllButtonState[PADBTN_DOWN]++; }		//�����Ă���
		if ((gamepad[cnt].InputState & MOUSE_INPUT_LEFT) != PAD_INPUT_DOWN) { gamepad[cnt].AllButtonState[PADBTN_DOWN] = 0; }	//�����Ă��Ȃ�

		//���{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_LEFT) == PAD_INPUT_LEFT) { gamepad[cnt].AllButtonState[PADBTN_LEFT]++; }		//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_LEFT) != PAD_INPUT_LEFT) { gamepad[cnt].AllButtonState[PADBTN_LEFT] = 0; }	//�����Ă��Ȃ�

		//�E�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_RIGHT) == PAD_INPUT_RIGHT) { gamepad[cnt].AllButtonState[PADBTN_RIGHT]++; }	//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_RIGHT) != PAD_INPUT_RIGHT) { gamepad[cnt].AllButtonState[PADBTN_RIGHT] = 0; }	//�����Ă��Ȃ�

		//��{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_UP) == PAD_INPUT_UP) { gamepad[cnt].AllButtonState[PADBTN_UP]++; }			//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_UP) != PAD_INPUT_UP) { gamepad[cnt].AllButtonState[PADBTN_UP] = 0; }			//�����Ă��Ȃ�

		//1�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_1) == PAD_INPUT_1) { gamepad[cnt].AllButtonState[PADBTN_1]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_1) != PAD_INPUT_1) { gamepad[cnt].AllButtonState[PADBTN_1] = 0; }				//�����Ă��Ȃ�

		//2�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_2) == PAD_INPUT_2) { gamepad[cnt].AllButtonState[PADBTN_2]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_2) != PAD_INPUT_2) { gamepad[cnt].AllButtonState[PADBTN_2] = 0; }				//�����Ă��Ȃ�

		//3�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_3) == PAD_INPUT_3) { gamepad[cnt].AllButtonState[PADBTN_3]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_3) != PAD_INPUT_3) { gamepad[cnt].AllButtonState[PADBTN_3] = 0; }				//�����Ă��Ȃ�

		//4�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_4) == PAD_INPUT_4) { gamepad[cnt].AllButtonState[PADBTN_4]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_4) != PAD_INPUT_4) { gamepad[cnt].AllButtonState[PADBTN_4] = 0; }				//�����Ă��Ȃ�

		//5�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_5) == PAD_INPUT_5) { gamepad[cnt].AllButtonState[PADBTN_5]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_5) != PAD_INPUT_5) { gamepad[cnt].AllButtonState[PADBTN_5] = 0; }				//�����Ă��Ȃ�

		//6�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_6) == PAD_INPUT_6) { gamepad[cnt].AllButtonState[PADBTN_6]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_6) != PAD_INPUT_6) { gamepad[cnt].AllButtonState[PADBTN_6] = 0; }				//�����Ă��Ȃ�

		//7�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_7) == PAD_INPUT_7) { gamepad[cnt].AllButtonState[PADBTN_7]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_7) != PAD_INPUT_7) { gamepad[cnt].AllButtonState[PADBTN_7] = 0; }				//�����Ă��Ȃ�

		//8�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_8) == PAD_INPUT_8) { gamepad[cnt].AllButtonState[PADBTN_8]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_8) != PAD_INPUT_8) { gamepad[cnt].AllButtonState[PADBTN_8] = 0; }				//�����Ă��Ȃ�

		//9�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_9) == PAD_INPUT_9) { gamepad[cnt].AllButtonState[PADBTN_9]++; }				//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_9) != PAD_INPUT_9) { gamepad[cnt].AllButtonState[PADBTN_9] = 0; }				//�����Ă��Ȃ�

		//10�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_10) == PAD_INPUT_10) { gamepad[cnt].AllButtonState[PADBTN_10]++; }			//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_10) != PAD_INPUT_10) { gamepad[cnt].AllButtonState[PADBTN_10] = 0; }			//�����Ă��Ȃ�

		//11�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_11) == PAD_INPUT_11) { gamepad[cnt].AllButtonState[PADBTN_11]++; }			//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_11) != PAD_INPUT_11) { gamepad[cnt].AllButtonState[PADBTN_11] = 0; }			//�����Ă��Ȃ�

		//12�{�^���������Ă��邩�`�F�b�N
		if ((gamepad[cnt].InputState & PAD_INPUT_12) == PAD_INPUT_12) { gamepad[cnt].AllButtonState[PADBTN_12]++; }			//�����Ă���
		if ((gamepad[cnt].InputState & PAD_INPUT_12) != PAD_INPUT_12) { gamepad[cnt].AllButtonState[PADBTN_12] = 0; }			//�����Ă��Ȃ�

		if (DEBUG_MODE == TRUE)	//�f�o�b�O���[�h�Ȃ�
		{
			//���l�𔽉f���Ĉړ�������
			debug[cnt].ptLeft.x += gamepad[cnt].NewAnalogX / 100;
			debug[cnt].ptLeft.y += gamepad[cnt].NewAnalogY / 100;

			//����ɖ߂�
			if (MY_PAD_CLICK(cnt, PADBTN_3) == TRUE)
			{
				debug[cnt].ptLeft.x = 0;
				debug[cnt].ptLeft.y = 0;
			}
		}

	}

	return;
}

/// <summary>
/// �{�^���������Ă��邩�A�p�b�h�R�[�h�Ŕ��f����
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <returns>�����Ă�����TRUE</returns>
BOOL MY_PAD_DOWN(int DX_INPUT_PAD, PAD_BUTTON PADBTN_)
{
	
	//�p�b�h�R�[�h�̃{�^���������Ă��鎞
	if (gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] != 0)
	{
		return TRUE;	//�{�^���������Ă���
	}
	else
	{
		return FALSE;	//�{�^���������Ă��Ȃ�
	}
}

/// <summary>
/// �p�b�h�������グ�����A�p�b�h�R�[�h���f����
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <returns>�����グ����TRUE</returns>
BOOL MY_PAD_UP(int DX_INPUT_PAD, PAD_BUTTON PADBTN_)
{
	if (gamepad[DX_INPUT_PAD].OldButtonKeyState[PADBTN_] >= 1	//���O�͉����Ă���
		&& gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�{�^���������グ�Ă���
	}
	else
	{
		return FALSE;	//�{�^���������グ�Ă��Ȃ�
	}
}

/// <summary>
/// �p�b�h�����������Ă��邩�A�p�b�h�R�[�h���f����
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <param name="DownSecond">�p�b�h�����������Ă��鎞��(�b)</param>
/// <returns>���������Ă�����TRUE</returns>
BOOL MY_PADDOWN_KEEP(int DX_INPUT_PAD, PAD_BUTTON PADBTN_, int milliTime)
{
	float MilliSec = 1000.0f;	//�P�b��1000�~���b

	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = (milliTime / MilliSec) * GAME_FPS;

	if (gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

/// <summary>
/// �p�b�h���N���b�N�������A�p�b�h�R�[�h�Ŕ��f����
/// </summary>
/// <param name="cnt">DX_INPUT_PAD?</param>
/// <param name="PADBTN_">PADBTN_???</param>
/// <returns>�N���b�N������TRUE</returns>
BOOL MY_PAD_CLICK(int DX_INPUT_PAD, PAD_BUTTON PADBTN_)
{
	if (gamepad[DX_INPUT_PAD].OldButtonKeyState[PADBTN_] == 0		//���O�͉����Ă��Ȃ���
		&& gamepad[DX_INPUT_PAD].AllButtonState[PADBTN_] >= 1)	//���͉����Ă���Ƃ�
	{
		return TRUE;	//�p�b�h���N���b�N�����i���������Ă��A�P��̂ݔ����j
	}
	else
	{
		return FALSE;	//�p�b�h���N���b�N���Ă��Ȃ����A���������Ă���
	}
}

/// <summary>
/// �p�b�h�̏���`�悷��
/// </summary>
/// <returns></returns>
VOID MY_PAD_DRAW(VOID)
{
	//�p�b�h�̐��ɉ����ď������s��
	for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
	{
		if (DEBUG_MODE == TRUE)	//�f�o�b�O���[�h�Ȃ�
		{
			//�~��`��
			DrawCircle(debug[cnt].ptLeft.x, debug[cnt].ptLeft.y, debug[cnt].RoundLeft, debug[cnt].Color, TRUE);
		}
	}

	if (DEBUG_MODE == TRUE)	//�f�o�b�O���[�h�Ȃ�
	{
		//�������`��
		if (padConnectNum <= 0)
		{
			DrawFormatString(0, GAME_HEIGHT - 180, GetColor(255, 255, 255), "�Q�[���p�b�h���ڑ�");
		}
		else
		{
			DrawFormatString(0, GAME_HEIGHT - 180, GetColor(255, 255, 255), "�Q�[���p�b�h�ڑ���:%1d", padConnectNum);
		}

		//�p�b�h�̐��ɉ����ď������s��
		for (int cnt = DX_INPUT_PAD1; cnt <= padConnectNum; cnt++)
		{
			//�p�b�h�̏���`��
			DrawFormatString(0, GAME_HEIGHT - (160 - cnt * 20), GetColor(255, 255, 255),
				"[AX:%5d][AY:%5d][U:%3d][R:%3d][D:%3d][L:%3d][1:%3d][2:%3d][3:%3d][4:%3d][5:%3d][6:%3d][7:%3d][8:%3d][9:%3d][10:%3d][11:%3d][12:%3d]",
				gamepad[cnt].NewAnalogX,
				gamepad[cnt].NewAnalogY,
				gamepad[cnt].AllButtonState[PADBTN_UP],
				gamepad[cnt].AllButtonState[PADBTN_RIGHT],
				gamepad[cnt].AllButtonState[PADBTN_DOWN],
				gamepad[cnt].AllButtonState[PADBTN_LEFT],
				gamepad[cnt].AllButtonState[PADBTN_1],
				gamepad[cnt].AllButtonState[PADBTN_2],
				gamepad[cnt].AllButtonState[PADBTN_3],
				gamepad[cnt].AllButtonState[PADBTN_4],
				gamepad[cnt].AllButtonState[PADBTN_5],
				gamepad[cnt].AllButtonState[PADBTN_6],
				gamepad[cnt].AllButtonState[PADBTN_7],
				gamepad[cnt].AllButtonState[PADBTN_8],
				gamepad[cnt].AllButtonState[PADBTN_9],
				gamepad[cnt].AllButtonState[PADBTN_10],
				gamepad[cnt].AllButtonState[PADBTN_11],
				gamepad[cnt].AllButtonState[PADBTN_12]
			);

		}

	}

	return;
}