/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//FPS�����̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "FPS.h"

//########## �O���[�o���ϐ� ##########

//FPS�̃f�[�^���Ǘ�
FPS fps;

//########## �֐� ##########

/// <summary>
/// FPS�l���v�����A�l���X�V����֐�
/// </summary>
/// <returns></returns>
VOID MY_FPS_UPDATE(VOID)
{
	//��ԍŏ��̏����̂Ƃ������A����J�n�������擾����
	if (fps.IsInitFlg == FALSE)
	{
		//����J�n�������}�C�N���b�P�ʂŎ擾
		fps.StartTime = GetNowHiPerformanceCount();

		fps.IsInitFlg = TRUE;	//�t���O�𗧂ĂĂ���
	}

	//���݂̎������}�C�N���b�P�ʂŎ擾
	fps.NowTime = GetNowHiPerformanceCount();

	// �O��擾�������Ԃ���̌o�ߎ��Ԃ�b�ɕϊ����ăZ�b�g
	fps.DeltaTime = (fps.NowTime - fps.OldTime) / 1000000.0f;

	// ����擾�������Ԃ�ۑ�
	fps.OldTime = fps.NowTime;

	//1�t���[���ځ`FPS�ݒ�l�܂ł́A�J�E���g�A�b�v
	if (fps.Count < fps.SampleRate)
	{
		//�J�E���^�𑝂₷
		fps.Count++;
	}
	else
	{
		//FPS�ݒ�l�t���[���ڂȂ畽�ς��v�Z

		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		fps.DrawValue = 1000000.0f / ((fps.NowTime - fps.StartTime) / (float)fps.SampleRate);

		//����J�n�������}�C�N���b�P�ʂŎ擾
		fps.StartTime = GetNowHiPerformanceCount();

		//�J�E���^������
		fps.Count = 1;
	}

	return;
}

/// <summary>
/// FPS�l��`�悷��֐�
/// </summary>
/// <returns></returns>
VOID MY_FPS_DRAW(VOID)
{
	if (DEBUG_MODE == TRUE)	//�f�o�b�O���[�h�Ȃ�
	{
		//�������`��
		DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", fps.DrawValue);
	}

	return;
}

/// <summary>
/// FPS�l���v�����A�҂֐�
/// </summary>
/// <returns></returns>
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = fps.NowTime - fps.StartTime;					//����J�n�������猻�݂̂�����������(�}�C�N���b)
	int waitTime = 1000000.0f / GAME_FPS * fps.Count - resultTime;	//�҂ׂ�����(�}�C�N���b)

	waitTime /= 1000.0f;		//�}�C�N���b���~���b�ɕϊ�

	if (waitTime > 0)			//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//���������珈����҂�(ProcessMessage�֐��͗��Ŏ��s�����)
	}
	return;
}