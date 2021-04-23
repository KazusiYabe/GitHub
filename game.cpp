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
#define WAZA_SELECT_MAX	4

//########## �\���� ##########
struct CHARACTOR_DATA
{
	char Name[STR_MAX] = "";
	int HP = 0;			//�̗�
	int HPMAX = 0;		//�̗�(MAX)
	float ATK = 1.0;	//�U����
	int MP = 0;			//�l�o
	int MPMAX = 0;		//�l�o(MAX)
	AUDIO nakigoe;		//����
	BOOL IsPlayNakigoe = FALSE;	//�����o�������H
};//�����X�^�[�̃f�[�^

struct WAZA_RECORD
{
	int No = -1;
	char Name[STR_MAX] = "";
	int ATK = 0;
	int MP = -1;		//�g��MP�̗�
	int HealHP = -1;	//HP�񕜗�
	int HealMP = -1;	//MP�񕜗�
	DIVIMAGE effect;	//�G�t�F�N�g�̊G
	AUDIO SE;			//�Z�̉�
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
	wazaSelect0,
	wazaSelect1,
	wazaSelect2,
	wazaSelect3
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
CHARACTOR_DATA dragonData;
CHARACTOR_DATA slimeData;
CHARACTOR_DATA tekiData;

CHARACTOR_DATA playerData;

//�Z�e�[�u���f�[�^
WAZA_RECORD wazaTable[WAZA_MAX];
WAZA_RECORD TekiwazaTable[WAZA_MAX];

//�X�e�[�^�X�̕\���n
int statusHeight = 40;
int TekiHpBarMaxWidth = 650;
RECT TekiHpBar;
RECT TekiHpBarWaku;

int PlayerHpBarMaxWidth = 400;
RECT PlayerHpBar;
RECT PlayerHpBarWaku;

int PlayerMpBarMaxWidth = 400;
RECT PlayerMpBar;
RECT PlayerMpBarWaku;

//�R�}���h�n
int NowCommand = encounter;
int buttleCmd = attack;
int wazaSelectCmd = 0;		//�I�������Z�̏ꏊ
int wazaNo = 0;				//�I�������ZNo.

BOOL ProcCmdFlg = FALSE;	//�Z�̐������I������H
BOOL EffectEndFlg = FALSE;	//�G�t�F�N�g���I������H

BOOL IsNotEnoughMP = FALSE;		//MP�͑����H

int encFeadPer = 0;
BOOL encMoveFlg = FALSE;

int processCnt = 0;
int processCntMAX = GAME_FPS;

int damageCnt = 0;
int damageCntMAX = GAME_FPS * 1.5;
BOOL damageProcFlg = FALSE;	//�_���[�W�������s�������H

BOOL IsPlayerTurn = FALSE;	//�v���C���[�̃^�[�����H

//########## �֐��̃v���g�^�C�v�錾 ##########

VOID DrawPushEnter(VOID);		//PUSH ENTER��`��
VOID DrawPlayerStatus(VOID);	//�v���C���[�̃X�e�[�^�X��`��
WAZA_RECORD SetWazaRecord(int no, const char* Name, int ATK, int MP, int HealHP, int HealMP, DIVIMAGE effect, AUDIO se);	//�Z���R�[�h�ݒ�

//########## �Q�[�������̊֐� ##########

//�Z���R�[�h�ݒ�
WAZA_RECORD SetWazaRecord(int no, const char* Name, int ATK, int MP, int HealHP, int HealMP, DIVIMAGE effect, AUDIO se)
{
	WAZA_RECORD waza;
	waza.No = no;
	strcpyDx(waza.Name, Name);
	waza.ATK = ATK;
	waza.MP = MP;
	waza.HealHP = HealHP;
	waza.HealMP = HealMP;
	waza.effect = effect;
	waza.SE = se;

	return waza;	//�ݒ肵���Z������
}

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
	dragonData.ATK = 3.0;
	dragonData.MPMAX = 50;
	dragonData.MP = dragonData.MPMAX;
	dragonData.nakigoe = dragonSE;
	dragonData.IsPlayNakigoe = FALSE;

	//�X���C��
	strcpy_sDx(slimeData.Name, STR_MAX, "�n�}�~�[�X���C��");
	slimeData.HPMAX = 10;
	slimeData.HP = slimeData.HPMAX;
	slimeData.ATK = 1.0;
	slimeData.MPMAX = 5;
	slimeData.MP = slimeData.MPMAX;
	slimeData.nakigoe = slimeSE;
	slimeData.IsPlayNakigoe = FALSE;

	//�v���C���[
	strcpy_sDx(playerData.Name, STR_MAX, "�`���҃u���C�u");
	playerData.HPMAX = 20;
	playerData.HP = playerData.HPMAX;
	playerData.ATK = 1.0;
	playerData.MPMAX = 20;
	playerData.MP = playerData.MPMAX;
	playerData.nakigoe = playerSE;
	playerData.IsPlayNakigoe = FALSE;

	//����������������������������������������������������������������������������������������

//�G�̃f�[�^���Œ�
//�X���C���FslimeData
//�h���S���FdragonData
	tekiData = slimeData;

	//�G�̉摜��ݒ�
	//�X���C���FslimeImage
	//�h���S���FdragonImage
	tekiImage = slimeImage;

	//����������������������������������������������������������������������������������������

	//�v���C���[�̃^�[�����H
	IsPlayerTurn = TRUE;

	//�X�e�[�^�X�n
	TekiHpBar = GetRect(wakuImage.pos.x + 60, statusHeight + 60, wakuImage.pos.x + 60 + TekiHpBarMaxWidth, statusHeight + 60 + 60);
	TekiHpBarWaku = TekiHpBar;

	PlayerHpBar = GetRect(
		messageImage.pos.x + messageImage.pos.width + 20,
		600,
		messageImage.pos.x + messageImage.pos.width + 20 + PlayerHpBarMaxWidth,
		600 + statusHeight);
	PlayerHpBarWaku = PlayerHpBar;

	PlayerMpBar = GetRect(
		messageImage.pos.x + messageImage.pos.width + 20,
		650,
		messageImage.pos.x + messageImage.pos.width + 20 + PlayerMpBarMaxWidth,
		650 + statusHeight);
	PlayerMpBarWaku = PlayerMpBar;

	//�R�}���h�n
	NowCommand = encounter;
	buttleCmd = attack;
	wazaSelectCmd = 0;
	wazaNo = 0;

	//�G���J�E���g�n
	encFeadPer = 0;
	encMoveFlg = FALSE;

	//�Z��ݒ�
	wazaTable[0] = SetWazaRecord(0, "�q�b�J�L", 1, 0, 0, 0, effectImage[0], wazaSE[0]);
	wazaTable[1] = SetWazaRecord(1, "�L���c�P", 1, 0, 0, 0, effectImage[1], wazaSE[1]);
	wazaTable[2] = SetWazaRecord(2, "�n�T�~", 2, 0, 0, 0, effectImage[2], wazaSE[2]);
	wazaTable[3] = SetWazaRecord(3, "�X���b�V��", 3, 0, 0, 0, effectImage[3], wazaSE[3]);

	wazaTable[4] = SetWazaRecord(4, "�A�C�V�N��", 5, 10, 0, 0, effectImage[4], wazaSE[4]);
	wazaTable[5] = SetWazaRecord(5, "����", 5, 10, 0, 0, effectImage[5], wazaSE[5]);
	wazaTable[6] = SetWazaRecord(6, "�J�G���r�[�[��", 20, 20, 0, 0, effectImage[6], wazaSE[6]);
	wazaTable[7] = SetWazaRecord(7, "�g���v���\�[�h", 30, 30, 0, 0, effectImage[7], wazaSE[7]);

	wazaTable[8] = SetWazaRecord(8, "���₵�̕�", 0, 0, 5, 0, effectImage[8], wazaSE[8]);
	wazaTable[9] = SetWazaRecord(9, "�V�g�̗�", 0, 0, 0, 5, effectImage[9], wazaSE[9]);
	wazaTable[10] = SetWazaRecord(10, "�A�[�X�q�[��", 0, 20, 40, 10, effectImage[10], wazaSE[10]);
	wazaTable[11] = SetWazaRecord(11, "���Ȃ��", 0, 40, 60, 60, effectImage[11], wazaSE[11]);

	//�G�̋Z��ݒ�
	TekiwazaTable[0] = SetWazaRecord(0, "�X�v���b�V���A�^�b�N", 2, 0, 0, 0, effectImage[12], wazaSE[12]);
	TekiwazaTable[1] = SetWazaRecord(0, "�}�W�J���r�[��", 4, 0, 0, 0, effectImage[13], wazaSE[13]);
	TekiwazaTable[2] = SetWazaRecord(0, "�L���A�[", 0, 7, 7, 7, effectImage[14], wazaSE[14]);

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
		//�v���C���[�{�C�X
		if (playerData.IsPlayNakigoe == FALSE)
		{
			PlayAudio(playerData.nakigoe);
			playerData.IsPlayNakigoe = TRUE;
		}

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

	//�v���C���[�̃^�[���̂Ƃ�
	if (IsPlayerTurn == TRUE)
	{
		//�R�}���h�n�̏���
		switch (NowCommand)
		{
		case encounter:

			//�G�����Ɉړ�������
			if (encMoveFlg == TRUE)
			{
				if (tekiData.IsPlayNakigoe == FALSE)
				{
					PlayAudio(tekiData.nakigoe);
					tekiData.IsPlayNakigoe = TRUE;
				}
				if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
				{
					PlayAudio(selectSE);
					NowCommand = input;		//���̃R�}���h��
				}
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
				IsNotEnoughMP = FALSE;	//MP�͑����H
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
				if (wazaSelectCmd >= wazaSelect2) { wazaSelectCmd -= 2; }
			}

			if (MY_KEY_CLICK(KEY_INPUT_DOWN) == TRUE)
			{
				PlayAudio(selectSE);
				if (wazaSelectCmd <= wazaSelect1) { wazaSelectCmd += 2; }
			}

			if (MY_KEY_CLICK(KEY_INPUT_LEFT) == TRUE)
			{
				PlayAudio(selectSE);
				if (wazaSelectCmd == wazaSelect1 || wazaSelectCmd == wazaSelect3) { wazaSelectCmd--; }
			}

			if (MY_KEY_CLICK(KEY_INPUT_RIGHT) == TRUE)
			{
				PlayAudio(selectSE);
				if (wazaSelectCmd == wazaSelect0 || wazaSelectCmd == wazaSelect2) { wazaSelectCmd++; }
			}

			if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
			{
				wazaNo = (buttleCmd * WAZA_SELECT_MAX) + wazaSelectCmd;	//�ZNo������

				if (playerData.MP < wazaTable[wazaNo].MP)
				{
					IsNotEnoughMP = TRUE;	//MP������Ȃ��I
				}

				PlayAudio(selectSE);
				ProcCmdFlg = FALSE;		//�Z�̐���������
				EffectEndFlg = FALSE;	//�G�t�F�N�g�`�斢����
				NowCommand = process;	//���̃R�}���h��
				processCnt = 0;
			}

			break;

		case process:

			//MP������Ȃ��Ƃ��͑I��������
			if (IsNotEnoughMP == TRUE)
			{
				EffectEndFlg = FALSE;
				if (MY_KEY_CLICK(KEY_INPUT_RETURN) == TRUE)
				{
					PlayAudio(selectSE);
					NowCommand = waza;		//�O�̃R�}���h��
					IsNotEnoughMP = FALSE;
					break;
				}
			}

			//MP������Ă����
			if (IsNotEnoughMP == FALSE)
			{
				//�����Ŏ��̃R�}���h��
				if (ProcCmdFlg == FALSE)
				{
					if (processCnt < processCntMAX) { processCnt++; }
					else
					{
						//�Z��SE
						PlayAudio(wazaTable[wazaNo].SE);

						ProcCmdFlg = TRUE;		//�R�}���h�`��I��
						wazaTable[wazaNo].effect.IsDraw = TRUE;	//�G�t�F�N�g�`��
					}
				}
			}

			//�G�t�F�N�g�����������
			if (EffectEndFlg == TRUE)
			{
				damageProcFlg = FALSE;	//�_���[�W����
				damageCnt = 0;
				NowCommand = damage;	//���̃R�}���h��
			}

			break;
		case damage:

			if (damageProcFlg == FALSE)
			{
				if (buttleCmd == attack || buttleCmd == magic)
				{
					tekiData.HP -= (int)ceil(playerData.ATK * wazaTable[wazaNo].ATK);	//HP�����炷
					if (tekiData.HP < 0) { tekiData.HP = 0; }
					playerData.MP -= wazaTable[wazaNo].MP;	//MP�����炷
					if (playerData.MP < 0) { playerData.MP = 0; }
				}
				else if (buttleCmd == recovery)
				{
					playerData.HP += wazaTable[wazaNo].HealHP;	//HP�𑝂₷
					if (playerData.HP > playerData.HPMAX) { playerData.HP = playerData.HPMAX; }
					playerData.MP -= wazaTable[wazaNo].MP;	//MP�����炷
					if (playerData.MP < 0) { playerData.MP = 0; }
					playerData.MP += wazaTable[wazaNo].HealMP;	//MP�𑝂₷
					if (playerData.MP > playerData.MPMAX) { playerData.MP = playerData.MPMAX; }
				}
				damageProcFlg = TRUE;
			}

			//�����Ŏ��̃R�}���h��
			if (damageCnt < damageCntMAX) { damageCnt++; }
			else
			{
				//�G��HP��0�ȉ��ɂȂ����Ƃ�
				if (tekiData.HP <= 0)
				{
					GameScene = GAME_SCENE_END;		//�G���h��ʂ�
					IsSlimeWin = TRUE;				//�G�ɏ������I
					IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
					IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I
				}

				//������HP��0�ȉ��ɂȂ����Ƃ�
				if (playerData.HP <= 0)
				{
					GameScene = GAME_SCENE_END;		//�G���h��ʂ�
					IsSlimeWin = FALSE;				//�G�ɕ�����
					IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
					IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I
				}

				//�R�}���h����͂ɖ߂�
				NowCommand = input;

				//�v���C���[�̃^�[���G���h�I
				IsPlayerTurn = FALSE;
			}
			break;
		}
	}

	//�G�̃^�[���̂Ƃ�
	if (IsPlayerTurn == FALSE)
	{
		//�R�}���h�n�̏���
		switch (NowCommand)
		{

		case input:

			//�G�̗̑͂������ȉ��Ȃ��
			if (tekiData.HP < tekiData.HPMAX / 2)
			{
				buttleCmd = recovery;	//��
			}
			else
			{
				buttleCmd = GetRand(1);	//0��1�������_���őI��
				//0�Ȃ�attack
				//1�Ȃ�magic
			}

			NowCommand = waza;

			break;

		case waza:

			//�G�̋ZNo���o���Ă���
			wazaNo = buttleCmd;

			ProcCmdFlg = FALSE;		//�Z�̐���������
			EffectEndFlg = FALSE;	//�G�t�F�N�g�`�斢����
			NowCommand = process;	//���̃R�}���h��
			processCnt = 0;

			break;

		case process:

			//�����Ŏ��̃R�}���h��
			if (ProcCmdFlg == FALSE)
			{
				if (processCnt < processCntMAX) { processCnt++; }
				else
				{
					//�Z��SE
					PlayAudio(TekiwazaTable[wazaNo].SE);

					ProcCmdFlg = TRUE;		//�R�}���h�`��I��
					TekiwazaTable[wazaNo].effect.IsDraw = TRUE;	//�G�t�F�N�g�`��
				}
			}

			//�G�t�F�N�g�����������
			if (EffectEndFlg == TRUE)
			{
				damageProcFlg = FALSE;	//�_���[�W����
				damageCnt = 0;
				NowCommand = damage;	//���̃R�}���h��
			}

			break;
		case damage:

			if (damageProcFlg == FALSE)
			{
				if (buttleCmd == attack || buttleCmd == magic)
				{
					playerData.HP -= (int)ceil(tekiData.ATK * TekiwazaTable[wazaNo].ATK);	//HP�����炷
					if (playerData.HP < 0) { playerData.HP = 0; }

					//�G��MP�͌��炳�Ȃ��A�ɂ��Ă���
					//tekiData.MP -= TekiwazaTable[wazaNo].MP;	//MP�����炷
					//if (tekiData.MP < 0) { tekiData.MP = 0; }
				}
				else if (buttleCmd == recovery)
				{
					tekiData.HP += TekiwazaTable[wazaNo].HealHP;	//HP�𑝂₷
					if (tekiData.HP > tekiData.HPMAX) { tekiData.HP = tekiData.HPMAX; }
					tekiData.MP += TekiwazaTable[wazaNo].HealMP;	//MP�𑝂₷
					if (tekiData.MP > tekiData.MPMAX) { tekiData.MP = tekiData.MPMAX; }
				}
				damageProcFlg = TRUE;
			}

			//�����Ŏ��̃R�}���h��
			if (damageCnt < damageCntMAX) { damageCnt++; }
			else
			{
				//�G��HP��0�ȉ��ɂȂ����Ƃ�
				if (tekiData.HP <= 0)
				{
					GameScene = GAME_SCENE_END;		//�G���h��ʂ�
					IsSlimeWin = TRUE;				//�G�ɏ������I
					IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
					IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I
				}

				//������HP��0�ȉ��ɂȂ����Ƃ�
				if (playerData.HP <= 0)
				{
					GameScene = GAME_SCENE_END;		//�G���h��ʂ�
					IsSlimeWin = FALSE;				//�G�ɕ�����
					IsFadeIn = FALSE;				//�t�F�[�h�C���͂��Ȃ��I
					IsFadeOut = TRUE;				//�t�F�[�h�A�E�g�J�n�I
				}

				//�R�}���h����͂ɖ߂�
				NowCommand = input;

				//�o�g���R�}���h���A�^�b�N�ɂ���
				buttleCmd = attack;

				//�v���C���[�̃^�[���ɂ���
				IsPlayerTurn = TRUE;

			}
			break;
		}
	}

	return;
}

//�v���C���[�̃X�e�[�^�X��`��
VOID DrawPlayerStatus(VOID)
{
	//���b�Z�[�W�g�`��
	DrawImage(messageImage);
	//�v���C���[���O�`��
	DrawStringToHandle(messageImage.pos.x + 5, messageImage.pos.y + 10, playerData.Name, GetColor(255, 255, 255), fontPlayer.handle);

	//HP�ɂ���ăo�[���k�߂�
	PlayerHpBar.right = PlayerHpBar.left + ((float)playerData.HP / playerData.HPMAX) * PlayerHpBarMaxWidth;
	if (PlayerHpBar.right < PlayerHpBar.left) { PlayerHpBar.right = PlayerHpBar.left; }	//HP�o�[�𒴂��Ȃ��悤��

	//HP�o�[�̐F��ς���
	if (playerData.HP < playerData.HPMAX / 8) { DrawRect(PlayerHpBar, GetColor(204, 75, 49), TRUE); }
	else if (playerData.HP < playerData.HPMAX / 4) { DrawRect(PlayerHpBar, GetColor(204, 178, 49), TRUE); }
	else { DrawRect(PlayerHpBar, GetColor(49, 204, 49), TRUE); }
	DrawRect(PlayerHpBarWaku, GetColor(255, 255, 255), FALSE);
	//HP�̐��l��\��
	DrawFormatStringToHandle(PlayerHpBarWaku.left + 10, PlayerHpBarWaku.top, GetColor(255, 255, 255), fontCommand.handle, "HP�F%5d/%5d", playerData.HP, playerData.HPMAX);

	//MP�ɂ���ăo�[���k�߂�
	PlayerMpBar.right = PlayerMpBar.left + ((float)playerData.MP / playerData.MPMAX) * PlayerMpBarMaxWidth;
	if (PlayerMpBar.right < PlayerMpBar.left) { PlayerMpBar.right = PlayerMpBar.left; }	//Mp�o�[�𒴂��Ȃ��悤��

	//MP�o�[�̐F��ς���
	if (playerData.MP < playerData.MPMAX / 8) { DrawRect(PlayerMpBar, GetColor(204, 75, 49), TRUE); }
	else if (playerData.MP < playerData.MPMAX / 4) { DrawRect(PlayerMpBar, GetColor(204, 178, 49), TRUE); }
	else { DrawRect(PlayerMpBar, GetColor(0, 35, 212), TRUE); }
	DrawRect(PlayerMpBarWaku, GetColor(255, 255, 255), FALSE);
	//MP�̐��l��\��
	DrawFormatStringToHandle(PlayerMpBarWaku.left + 10, PlayerMpBarWaku.top, GetColor(255, 255, 255), fontCommand.handle, "MP�F%5d/%5d", playerData.MP, playerData.MPMAX);


	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{

	//����������������������������������������������������������������������������������������

//�v���C�w�i��`��i�ꏊ�͑I�ׂ�S�^�C�v�I�j
//���@�� �FplaykusaImage
//��ݼޮ݁FplaydanjonImage
//��@�� �FplaykawaImage
//�{�X�� �FplaybossImage
	DrawImage(playkawaImage);

	//����������������������������������������������������������������������������������������


	//�P�x��i�X�ƕύX����(�������̐F��)
	SetDrawBright(encFeadPer, encFeadPer, encFeadPer);

	DrawImage(tekiImage);		//�G��`��

	SetDrawBright(255, 255, 255);	//���̋P�x�ɂ͉e�������Ȃ�

	unsigned int selectColor = GetColor(245, 245, 245);
	unsigned int notselectColor = GetColor(102, 102, 102);

	unsigned int kougekiColor = notselectColor;
	unsigned int mahouColor = notselectColor;
	unsigned int kaihukuColor = notselectColor;

	unsigned int waza1Color = notselectColor;
	unsigned int waza2Color = notselectColor;
	unsigned int waza3Color = notselectColor;
	unsigned int waza4Color = notselectColor;

	char ProcText[STR_MAX];

	//�v���C���[�̃^�[���̂Ƃ�
	if (IsPlayerTurn == TRUE)
	{
		//�R�}���h�n�̏���
		switch (NowCommand)
		{
		case encounter:

			//�G���ړ������鏈��
			if (encMoveFlg == FALSE)
			{
				encFeadPer += 5;
				if (tekiImage.pos.x < GAME_WIDTH / 2 - tekiImage.pos.width / 2) { tekiImage.pos.x += 10; }
				else { encMoveFlg = TRUE; }
			}

			//�G������Ă���E�E�E
			if (encMoveFlg == TRUE)
			{
				DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��
				DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "�Ȃ�ƁI�����X�^�[�ɑ������Ă��܂����I�I", GetColor(255, 255, 255), fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 90, "�ǂ����키�����Ȃ��悤���E�E�E�I��", GetColor(255, 255, 255), fontCommand.handle);
			}

			break;
		case input:

			DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��
			if (buttleCmd == attack) { kougekiColor = selectColor; }
			else if (buttleCmd == magic) { mahouColor = selectColor; }
			else if (buttleCmd == recovery) { kaihukuColor = selectColor; }
			DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "�R�E�Q�L", kougekiColor, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 40, "�}�z�E", mahouColor, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 80, "�J�C�t�N", kaihukuColor, fontCommand.handle);

			break;

		case waza:

			DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

			//���͂̃R�}���h�͂��̂܂ܕ`�撆
			if (buttleCmd == attack) { kougekiColor = selectColor; }
			else if (buttleCmd == magic) { mahouColor = selectColor; }
			else if (buttleCmd == recovery) { kaihukuColor = selectColor; }
			DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, "�R�E�Q�L", kougekiColor, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 40, "�}�z�E", mahouColor, fontCommand.handle);
			DrawStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50 + 80, "�J�C�t�N", kaihukuColor, fontCommand.handle);

			if (wazaSelectCmd == 0) { waza1Color = selectColor; }
			else if (wazaSelectCmd == 1) { waza2Color = selectColor; }
			else if (wazaSelectCmd == 2) { waza3Color = selectColor; }
			else if (wazaSelectCmd == 3) { waza4Color = selectColor; }

			//�Z��`��
			if (buttleCmd == attack)
			{
				DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[0].Name, waza1Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[1].Name, waza2Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[2].Name, waza3Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[3].Name, waza4Color, fontCommand.handle);
			}
			else if (buttleCmd == magic)
			{
				DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[4].Name, waza1Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[5].Name, waza2Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[6].Name, waza3Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[7].Name, waza4Color, fontCommand.handle);
			}
			else if (buttleCmd == recovery)
			{
				DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50, wazaTable[8].Name, waza1Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50, wazaTable[9].Name, waza2Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 200, messageImage.pos.y + 50 + 50, wazaTable[10].Name, waza3Color, fontCommand.handle);
				DrawStringToHandle(messageImage.pos.x + 10 + 500, messageImage.pos.y + 50 + 50, wazaTable[11].Name, waza4Color, fontCommand.handle);
			}

			break;

		case process:

			if (IsNotEnoughMP == FALSE)
			{
				DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

				if (buttleCmd == attack)
				{
					sprintfDx(ProcText, "%s��%s�U�������I", playerData.Name, wazaTable[wazaNo].Name);
				}
				else if (buttleCmd == magic)
				{
					sprintfDx(ProcText, "%s��%s���������I", playerData.Name, wazaTable[wazaNo].Name);
				}
				else if (buttleCmd == recovery)
				{
					sprintfDx(ProcText, "%s��%s���F�����I", playerData.Name, wazaTable[wazaNo].Name);
				}

				//�G�t�F�N�g��`�悵�Ă��ǂ��Ƃ�
				if (ProcCmdFlg == TRUE)
				{
					//�G�t�F�N�g�̕`��
					DrawDivImage(&wazaTable[wazaNo].effect);

					if (wazaTable[wazaNo].effect.IsDraw == FALSE)
					{
						EffectEndFlg = TRUE;	//�G�t�F�N�g�`��I��
					}
					DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��
				}
			}
			else
			{
				DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��
				sprintfDx(ProcText, "MP������Ȃ�...�Z��I�ђ����˂�...");
			}
			DrawFormatStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, GetColor(255, 255, 255), fontCommand.handle, ProcText);

			break;
		case damage:

			DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

			if (buttleCmd == attack || buttleCmd == magic)
			{
				sprintfDx(ProcText, "%s��%3d�̃A�^�b�N�I�I", tekiData.Name, (int)ceil(playerData.ATK * wazaTable[wazaNo].ATK));
			}
			else if (buttleCmd == recovery)
			{
				sprintfDx(ProcText, "%s�� HP%3d / MP%3d �񕜂���", playerData.Name, wazaTable[wazaNo].HealHP, wazaTable[wazaNo].HealMP);
			}
			DrawFormatStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, GetColor(255, 255, 255), fontCommand.handle, ProcText);

			break;
		}
	}

	//�G�̃^�[���̂Ƃ�
	if (IsPlayerTurn == FALSE)
	{
		//�R�}���h�n�̏���
		switch (NowCommand)
		{

		case input:

			DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

			break;

		case waza:

			DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

			break;

		case process:

			if (IsNotEnoughMP == FALSE)
			{
				DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

				if (buttleCmd == attack)
				{
					sprintfDx(ProcText, "%s��%s�I", tekiData.Name, TekiwazaTable[wazaNo].Name);
				}
				else if (buttleCmd == magic)
				{
					sprintfDx(ProcText, "%s��%s�I", tekiData.Name, TekiwazaTable[wazaNo].Name);
				}
				else if (buttleCmd == recovery)
				{
					sprintfDx(ProcText, "%s��%s", tekiData.Name, TekiwazaTable[wazaNo].Name);
				}

				//�G�t�F�N�g��`�悵�Ă��ǂ��Ƃ�
				if (ProcCmdFlg == TRUE)
				{
					DrawDivImage(&TekiwazaTable[wazaNo].effect);
					if (TekiwazaTable[wazaNo].effect.IsDraw == FALSE)
					{
						EffectEndFlg = TRUE;	//�G�t�F�N�g�`��I��
					}
					DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��
				}
			}
			else
			{
				DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��
				sprintfDx(ProcText, "MP������Ȃ�...�Z��I�ђ����˂�...");
			}
			DrawFormatStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, GetColor(255, 255, 255), fontCommand.handle, ProcText);

			break;
		case damage:

			DrawPlayerStatus();	//�v���C���[�̃X�e�[�^�X�`��

			if (buttleCmd == attack || buttleCmd == magic)
			{
				sprintfDx(ProcText, "%s��%3d�̃A�^�b�N�I�I", playerData.Name, (int)ceil(tekiData.ATK * TekiwazaTable[wazaNo].ATK));
			}
			else if (buttleCmd == recovery)
			{
				sprintfDx(ProcText, "%s�� HP%3d / MP%3d �񕜂���", tekiData.Name, TekiwazaTable[wazaNo].HealHP, TekiwazaTable[wazaNo].HealMP );	
			}
			DrawFormatStringToHandle(messageImage.pos.x + 10, messageImage.pos.y + 50, GetColor(255, 255, 255), fontCommand.handle, ProcText);

			break;
		}
	}


	//�����X�^�[�̃X�e�[�^�X
	DrawImage(wakuImage);
	DrawStringToHandle(wakuImage.pos.x + 60, statusHeight, tekiData.Name, GetColor(255, 255, 255), fontMonster.handle);

	//HP�ɂ���ăo�[���k�߂�
	TekiHpBar.right = TekiHpBar.left + ((float)tekiData.HP / tekiData.HPMAX) * TekiHpBarMaxWidth;
	if (TekiHpBar.right < TekiHpBar.left) { TekiHpBar.right = TekiHpBar.left; }	//HP�o�[�𒴂��Ȃ��悤��

	//HP�o�[�̐F��ς���
	if (tekiData.HP < tekiData.HPMAX / 8) { DrawRect(TekiHpBar, GetColor(204, 75, 49), TRUE); }
	else if (tekiData.HP < tekiData.HPMAX / 4) { DrawRect(TekiHpBar, GetColor(204, 178, 49), TRUE); }
	else { DrawRect(TekiHpBar, GetColor(49, 204, 49), TRUE); }
	DrawRect(TekiHpBarWaku, GetColor(255, 255, 255), FALSE);
	//HP�̐��l��\��
	DrawFormatStringToHandle(wakuImage.pos.x + 80, statusHeight + 60, GetColor(255, 255, 255), fontMonster.handle, "HP�F%5d/%5d", tekiData.HP, tekiData.HPMAX);

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

		//�Q�[��������
		if (GameScene == GAME_SCENE_TITLE) { MY_TITLE_INIT(); }

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