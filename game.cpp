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

#define PUSH_ENTER "-PUSH  ENTER-"

//########## �O���[�o���ϐ� ##########

//�V�[���؂�ւ����Ŏg�p
int fadeTimeMill = 2000;	//�s���~���b
int fadeTimeMax = (fadeTimeMill / 1000) * GAME_FPS;	//�t���[�����ɕϊ�

//�t�F�[�h�A�E�g
int fadeOutCntInit = 0;
int fadeOutCnt = fadeOutCntInit;
int fadeOutCntMAX = fadeTimeMax;

//�t�F�[�h�C��
int fadeInCntInit = fadeTimeMax;
int fadeInCnt = fadeInCntInit;
int fadeInCntMAX = 0;

//�X���C���ɏ��������H
BOOL IsSlimeWin = FALSE;

//�^�C�g���p�_�ŃJ�E���^
int titlePushCnt = 0;
int titlePushCntMAX = 60;
int titlePushPlus = 1;

//########## �֐��̃v���g�^�C�v�錾 ##########

VOID MY_TITLE_INIT(VOID);	//�Q�[���^�C�g��������
VOID DrawPushEnter(VOID);	//PUSH ENTER��`��

//########## �Q�[�������̊֐� ##########

//�Q�[���^�C�g��������
VOID MY_TITLE_INIT(VOID)
{
	fadeOutCntInit = 0;
	fadeOutCnt = fadeOutCntInit;
	fadeOutCntMAX = fadeTimeMax;

	fadeInCntInit = fadeTimeMax;
	fadeInCnt = fadeInCntInit;
	fadeInCntMAX = 0;

	titlePushCnt = 0;
	titlePushCntMAX = 60;
	titlePushPlus = 1;

	IsSlimeWin = FALSE;

	return;
}

//PUSH ENTER��`��
VOID DrawPushEnter(VOID)
{
	//�_�ł��镶����`��
	if (titlePushCnt >= 0 && titlePushCnt < titlePushCntMAX) { titlePushCnt += titlePushPlus; }
	else { titlePushPlus = -titlePushPlus;  titlePushCnt += titlePushPlus; }	//�������]

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)titlePushCnt / titlePushCntMAX) * 255);
	int witdh = GetDrawStringWidthToHandle(PUSH_ENTER, strlenDx(PUSH_ENTER), fontTitlePush.handle);
	DrawStringToHandle(GAME_WIDTH / 2 - witdh / 2, GAME_HEIGHT / 4 * 3, PUSH_ENTER, GetColor(255, 255, 255), fontTitlePush.handle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	return;
}

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
		IsSlimeWin = FALSE;	//�X���C�����s������

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
	//�^�C�g���w�i��`��
	DrawImage(titleBackImage);

	//���S��`��
	DrawImage(titleLogo);

	//PushEnter��`��
	DrawPushEnter();

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
	//�v���C�w�i��`��i�ꏊ�͑I�ׂ�S�^�C�v�I�j
	//���@�� �FplaykusaImage
	//��ݼޮ݁FplaydanjonImage
	//��@�� �FplaykawaImage
	//�{�X�� �FplaybossImage
	DrawImage(playkusaImage);

	//�X���C����`��
	DrawImage(slimeImage);

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
	if (IsSlimeWin == TRUE)
	{
		//����BGM���Ⴄ�Ƃ�
		if (NowPlayBGM.handle != EndClearBGM.handle) { NowPlayBGM = EndClearBGM; }
	}
	else
	{
		//����BGM���Ⴄ�Ƃ�
		if (NowPlayBGM.handle != EndOverBGM.handle) { NowPlayBGM = EndOverBGM; }
	}

	//�t�F�[�h�C�����Ȃ���Đ�
	FadeInPlayAudio(&NowPlayBGM, 1000);

	//�G���^�[�L�[�ŃV�[���J��
	if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_TITLE;	//�^�C�g����ʂ�
		IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
		IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I

		//�Q�[��������
		MY_TITLE_INIT();

		return;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	if (IsSlimeWin == TRUE)
	{
		//�w�i��`��
		DrawImage(endClearImage);

		//���S��`��
		DrawImage(endClearLogo);
	}
	else
	{
		//�w�i��`��
		DrawImage(endOverImage);

		//���S��`��
		DrawImage(endOverLogo);
	}

	//PushEnter��`��
	DrawPushEnter();

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
		if (fadeInCnt > fadeInCntMAX)
		{
			fadeInCnt--;

			//�t�F�[�h�C�����Ȃ���Đ��i�~���b�j
			FadeInPlayAudio(&NowPlayBGM, fadeTimeMill);
		}
		else
		{
			fadeInCnt = fadeInCntInit;	//�J�E���^��������

			//�t�F�[�h�A�E�g������
			IsFadeIn = FALSE;
			IsFadeOut = TRUE;
		}
	}

	//�t�F�[�h�A�E�g
	if (IsFadeOut == TRUE)
	{
		if (fadeOutCnt < fadeOutCntMAX) {
			fadeOutCnt++;

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
		StopAudio(&NowPlayBGM);					//BGM��~

		GameScene = NextScene;					//�Q�[���V�[����؂�ւ���
		OldGameScene = GameScene;				//�Q�[���V�[��(���O)���؂�ւ���
	}

	return;
}

//�؂�ւ���ʂ̕`��
VOID MY_CHANGE_DRAW(VOID)
{
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

	//��ʂ����񂾂񓧖��ɂ���(�t�F�[�h�C��)
	if (IsFadeIn == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeInCnt / fadeTimeMax) * 255); }

	//��ʂ����񂾂񓧖��ɂ���(�t�F�[�h�A�E�g)
	if (IsFadeOut == TRUE) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, ((float)fadeOutCnt / fadeTimeMax) * 255); }

	//��ʂ������l�p�Ńt�F�[�h�A�E�g
	if (IsFadeIn == TRUE || IsFadeOut == TRUE) { DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE); }

	//�������I��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(0, 0, "�؂�ւ����", GetColor(255, 255, 255));
	return;
}