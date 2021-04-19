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
#include "rect.h"

#define PUSH_ENTER "-PUSH  ENTER-"
#define WAZA_MAX	12

#define PLAYER_NAME		"�`���҃u���C�u"

//########## �\���� ##########
struct MONSTER_DATA
{
	char Name[STR_MAX] = "";
	int HP = 0;			//�̗�
	int HPMAX = 0;		//�̗�(MAX)
	int ATK = 0;		//�U��
	int MP = 0;			//�l�o
};//�����X�^�[�̃f�[�^

struct WAZA_RECORD
{
	int No = -1;
	char Name[STR_MAX] = "";
	int ATK = 0;
	int MP = -1;
};	//�Z���R�[�h�p

enum COMMAND
{
	encounter,	//����
	input,		//����
	waza,		//�Z
	process,	//����
	damage		//�_���[�W��H�炤
};

enum BUTTLECOMMAND
{
	attack,
	magic,
	recovery
};

enum WAZACOMMAND
{
	wazaCmd0,
	wazaCmd1,
	wazaCmd2,
	wazaCmd3
};


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

//�����X�^�[�f�[�^
MONSTER_DATA dragonData;
MONSTER_DATA slimeData;
MONSTER_DATA tekiData;

//�Z�e�[�u���f�[�^
WAZA_RECORD wazaTable[WAZA_MAX]{
	{0,"�q�b�J�L",1,0},
	{1,"�L���c�P",1,0},
	{2,"�J�~�c�L",2,0},
	{3,"�X���b�V��",3,0},
	{4,"�A�C�V�N��",5,10},
	{5,"����",5,10},
	{6,"�J�G���r�[�[��",20,20},
	{7,"�g���v���\�[�h",30,30},
	{8,"��HP��",-5,3},
	{9,"��MP��",0,-5},
	{10,"-----",1,0},
	{11,"-----",1,0}
};

//�X�e�[�^�X�̕\���n
int statusHeight = 40;
int HpBarMaxWidth = 650;
RECT HpBar;
RECT HpBarWaku;

//�R�}���h�n
int NowCommand = encounter;
int buttleCmd = attack;
int wazaCmd = 0;

//########## �֐��̃v���g�^�C�v�錾 ##########

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

	//����������������������������������������������������������������������������������������
	//�����X�^�[�̃f�[�^������������

	//�h���S��
	strcpy_sDx(dragonData.Name, STR_MAX, "�ΐ_���O���K���S��");
	dragonData.HPMAX = 100;
	dragonData.HP = dragonData.HPMAX;
	dragonData.ATK = 10;
	dragonData.MP = 50;

	//�X���C��
	strcpy_sDx(slimeData.Name, STR_MAX, "�n�}�~�[�X���C��");
	slimeData.HPMAX = 20;
	slimeData.HP = slimeData.HPMAX;
	slimeData.ATK = 2;
	slimeData.MP = 10;

	//�X�e�[�^�X�n
	HpBar = GetRect(wakuImage.pos.x + 60, statusHeight + 60, wakuImage.pos.x + 60 + HpBarMaxWidth, statusHeight + 60 + 60);
	HpBarWaku = HpBar;

	//�R�}���h�n
	NowCommand = encounter;
	buttleCmd = attack;
	wazaCmd = 0;

	GameScene = GAME_SCENE_TITLE;	//�Q�[���V�[���̓^�C�g����ʂ���

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

	////�G���^�[�L�[�ŃV�[���J��
	//if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
	//{
	//	GameScene = GAME_SCENE_END;		//�G���h��ʂ�
	//	IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
	//	IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I

	//	return;
	//}

	//�R�}���h�n�̏���
	switch (NowCommand)
	{
	case encounter:
		if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = input;//���̃R�}���h��
		}
		break;
	case input:
		if (MY_KEY_CLICK(KEY_INPUT_UP) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd > attack) { buttleCmd--; }
			else { buttleCmd = attack; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_DOWN) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd < recovery) { buttleCmd++; }
			else { buttleCmd = recovery; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_LEFT) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd > attack) { buttleCmd--; }
			else { buttleCmd = attack; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RIGHT) == TRUE)
		{
			PlayAudio(selectSE);
			if (buttleCmd < recovery) { buttleCmd++; }
			else { buttleCmd = recovery; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = waza;	//���̃R�}���h��
		}

		break;

	case waza:

		if (MY_KEY_CLICK(KEY_INPUT_BACK) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = input;	//�O�̃R�}���h��
		}

		if (MY_KEY_CLICK(KEY_INPUT_UP) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaCmd >= wazaCmd2) { wazaCmd -= 2; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_DOWN) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaCmd <= wazaCmd1) { wazaCmd += 2; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_LEFT) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaCmd == wazaCmd1 || wazaCmd == wazaCmd3) { wazaCmd--; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RIGHT) == TRUE)
		{
			PlayAudio(selectSE);
			if (wazaCmd == wazaCmd0 || wazaCmd == wazaCmd2) { wazaCmd++; }
		}

		if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
		{
			PlayAudio(selectSE);
			NowCommand = process;	//���̃R�}���h��
		}

		break;

	case process:
		if (MY_KEY_CLICK(KEY_INPUT_SPACE) == TRUE) { NowCommand++; }	//���̃R�}���h��
		break;
	case damage:
		if (MY_KEY_CLICK(KEY_INPUT_SPACE) == TRUE) { NowCommand = input; }
		break;
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
	DrawImage(playbossImage);

	//�X���C����`��
	//�h���S���FdragonImage
	//�X���C���FslimeImage
	DrawImage(dragonImage);

	//�X���C���̃f�[�^���Œ�
	tekiData = slimeData;

	//�����X�^�[�̃X�e�[�^�X
	DrawImage(wakuImage);
	DrawStringToHandle(wakuImage.pos.x + 60, statusHeight, tekiData.Name, GetColor(255, 255, 255), fontMonster.handle);

	//HP�ɂ���ăo�[���k�߂�
	HpBar.right = HpBar.left + ((float)tekiData.HP / tekiData.HPMAX) * HpBarMaxWidth;

	//HP�o�[�̐F��ς���
	if (tekiData.HP < tekiData.HPMAX / 8) { DrawRect(HpBar, GetColor(204, 75, 49), TRUE); }
	else if (tekiData.HP < tekiData.HPMAX / 4) { DrawRect(HpBar, GetColor(204, 178, 49), TRUE); }
	else { DrawRect(HpBar, GetColor(49, 204, 49), TRUE); }
	DrawRect(HpBarWaku, GetColor(255, 255, 255), FALSE);
	//HP�̐��l��\��
	DrawFormatStringToHandle(wakuImage.pos.x + 80, statusHeight + 60, GetColor(255, 255, 255), fontMonster.handle, "HP�F%5d/%5d", tekiData.HP, tekiData.HPMAX);

	//���b�Z�[�W�g�`��
	DrawImage(messageImage);
	//�v���C���[���O�`��
	DrawStringToHandle(messageImage.pos.x + 5, messageImage.pos.y + 10, PLAYER_NAME, GetColor(255, 255, 255), fontPlayer.handle);

	unsigned int selectColor = GetColor(245, 245, 245);
	unsigned int notselectColor = GetColor(102, 102, 102);

	unsigned int kougekiColor = notselectColor;
	unsigned int mahouColor = notselectColor;
	unsigned int kaihukuColor = notselectColor;

	unsigned int waza1Color = notselectColor;
	unsigned int waza2Color = notselectColor;
	unsigned int waza3Color = notselectColor;
	unsigned int waza4Color = notselectColor;

	//�R�}���h�n�̏���
	switch (NowCommand)
	{
	case encounter:
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "�Ȃ�ƁI�����X�^�[�ɑ������Ă��܂����I�I", GetColor(255, 255, 255), fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 90, "�ǂ����키�����Ȃ��悤���E�E�E�I��", GetColor(255, 255, 255), fontCommand.handle);
		break;
	case input:

		if (buttleCmd == attack) { kougekiColor = selectColor; }
		else if (buttleCmd == magic) { mahouColor = selectColor; }
		else if (buttleCmd == recovery) { kaihukuColor = selectColor; }
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "�R�E�Q�L", kougekiColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 40, "�}�z�E", mahouColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 80, "�J�C�t�N", kaihukuColor, fontCommand.handle);

		break;

	case waza:

		//���͂̃R�}���h�͂��̂܂ܕ`�撆
		if (buttleCmd == attack) { kougekiColor = selectColor; }
		else if (buttleCmd == magic) { mahouColor = selectColor; }
		else if (buttleCmd == recovery) { kaihukuColor = selectColor; }
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "�R�E�Q�L", kougekiColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 40, "�}�z�E", mahouColor, fontCommand.handle);
		DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 80, "�J�C�t�N", kaihukuColor, fontCommand.handle);

		if (wazaCmd == 0) { waza1Color = selectColor; }
		else if (wazaCmd == 1) { waza2Color = selectColor; }
		else if (wazaCmd == 2) { waza3Color = selectColor; }
		else if (wazaCmd == 3) { waza4Color = selectColor; }

		//�Z��`��
		if (buttleCmd == attack)
		{
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[0].Name, waza1Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[1].Name, waza2Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[2].Name, waza3Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[3].Name, waza4Color, fontCommand.handle);
		}
		if (buttleCmd == magic)
		{
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[4].Name, waza1Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[5].Name, waza2Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[6].Name, waza3Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[7].Name, waza4Color, fontCommand.handle);
		}
		if (buttleCmd == recovery)
		{
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[8].Name, waza1Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[9].Name, waza2Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[10].Name, waza3Color, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[11].Name, waza4Color, fontCommand.handle);
		}


		break;

	case process:


		break;
	case damage:


		break;
	}

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