/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2021
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//���Q�[���̃��C���\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "FPS.h"
#include "mouse.h"
#include "keyboard.h"
#include "gamepad.h"
#include "font.h"
#include "InputStr.h"
#include "image.h"
#include "audio.h"

//########## �O���[�o���ϐ� ##########

//�V�[���؂�ւ����Ŏg�p
int fadeTimeMill = 500;	//�s���~���b

//�t�F�[�h�A�E�g
int fadeOutCntInit = (fadeTimeMill / fadeTimeMill) * GAME_FPS;	//�t���[�����ɕϊ�
int fadeOutCnt = fadeOutCntInit;
int fadeOutCntMAX = 0;

//�t�F�[�h�C��
int fadeInCntInit = 0;
int fadeInCnt = fadeInCntInit;
int fadeInCntMAX = (fadeTimeMill / fadeTimeMill) * GAME_FPS;	//�t���[�����ɕϊ�

//########## �Q�[�������̊֐� ##########

//�^�C�g�����
VOID MY_TITLE(VOID)
{
	MY_TITLE_PROC();	//�^�C�g����ʂ̏���
	MY_TITLE_DRAW();	//�^�C�g����ʂ̕`��

	return;
}

//�^�C�g����ʂ̏���
VOID MY_TITLE_PROC(VOID)
{
	//����BGM���Ⴄ�Ƃ�
	if (NowPlayBGM.handle != TitleBGM.handle) { NowPlayBGM = TitleBGM; }

	//�t�F�[�h�C�����Ȃ���Đ�
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//�G���^�[�L�[�ŃV�[���J��
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE) 
	{
		GameScene = GAME_SCENE_PLAY;	//�v���C��ʂ�
		IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
		IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I

		return;
	}

	return;
}

//�^�C�g����ʂ̕`��
VOID MY_TITLE_DRAW(VOID)
{
	

	DrawString(0, 0, "�^�C�g�����", GetColor(255, 255, 255));
	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	//����BGM���Ⴄ�Ƃ�
	if (NowPlayBGM.handle != PlayBGM.handle) { NowPlayBGM = PlayBGM; }

	//�t�F�[�h�C�����Ȃ���Đ�
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//�G���^�[�L�[�ŃV�[���J��
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_END;		//�G���h��ʂ�
		IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
		IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I

		return;
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawString(0, 0, "�v���C���", GetColor(255, 255, 255));
	return;
}


//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	//����BGM���Ⴄ�Ƃ�
	if (NowPlayBGM.handle != EndClearBGM.handle) { NowPlayBGM = EndClearBGM; }

	//�t�F�[�h�C�����Ȃ���Đ�
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//�G���^�[�L�[�ŃV�[���J��
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_TITLE;	//�^�C�g����ʂ�
		IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
		IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I

		return;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{

	DrawString(0, 0, "�G���h���", GetColor(255, 255, 255));
	return;
}

//�؂�ւ����
VOID MY_CHANGE(VOID)
{
	MY_CHANGE_PROC();	//�؂�ւ���ʂ̏���
	MY_CHANGE_DRAW();	//�؂�ւ���ʂ̕`��
	return;
}

//�؂�ւ���ʂ̏���
VOID MY_CHANGE_PROC(VOID)
{
	//�t�F�[�h�C��
	if (IsFadeIn == TRUE)
	{
		if (fadeInCnt < fadeInCntMAX)
		{
			fadeInCnt++; //�J�E���g�A�b�v

			//�t�F�[�h�C�����Ȃ���Đ��i�~���b�j
			FadeInPlayAudio(&NowPlayBGM, fadeTimeMill);
		}
		else
		{
			//�t�F�[�h�C�����I������Ƃ�
			StopAudio(&NowPlayBGM);		//BGM��~
			fadeInCnt = fadeInCntInit;	//�J�E���^��������

			//�t�F�[�h�A�E�g������
			IsFadeIn = FALSE;
			IsFadeOut = TRUE;
		}
	}

	//�t�F�[�h�A�E�g
	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt > fadeOutCntMAX) {
			fadeOutCnt--;	//�J�E���g�_�E��

			//�t�F�[�h�A�E�g���Ȃ���Đ��i�~���b�j
			FadeOutPlayAudio(&NowPlayBGM, fadeTimeMill);

		}
		else
		{
			fadeOutCnt = fadeOutCntInit;	//�J�E���^��������

			IsFadeIn = FALSE;
			IsFadeOut = FALSE;
		}
	}

	//�؂�ւ������I��
	if (IsFadeIn == FALSE && IsFadeOut == FALSE)
	{
		//�t�F�[�h�A�E�g���I������Ƃ�
		StopAudio(&TitleBGM);					//BGM��~

		GameScene = NextScene;					//�Q�[���V�[����؂�ւ���
		OldGameScene = GameScene;				//�Q�[���V�[��(���O)���؂�ւ���
	}

	return;
}

//�؂�ւ���ʂ̕`��
VOID MY_CHANGE_DRAW(VOID)
{
	//��ʂ����񂾂񓧖��ɂ���(�t�F�[�h�C��)
	if (IsFadeIn == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeInCnt / fadeInCntMAX) * 255); }

	//��ʂ����񂾂񓧖��ɂ���(�t�F�[�h�A�E�g)
	if (IsFadeOut == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeOutCnt / fadeInCntMAX) * 255); }

	//��ʂ������l�p�Ńt�F�[�h�A�E�g
	if (IsFadeIn == TRUE || IsFadeOut == TRUE) { DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 255, 255), TRUE); }

	//�������I��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�ȑO�̉�ʂ�`��
	switch (OldGameScene)
	{
	case GAME_SCENE_TITLE:
		MY_TITLE_DRAW();	//�^�C�g�����
		break;
	case GAME_SCENE_PLAY:
		MY_PLAY_DRAW();		//�v���C���
		break;
	case GAME_SCENE_END:
		MY_END_DRAW();		//�G���h���
		break;
	}

	DrawString(0, 0, "�؂�ւ����", GetColor(255, 255, 255));
	return;
}