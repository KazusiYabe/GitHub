/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2021
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//########## �h�L�������g�R�����g�̏����� ##########
/*
* ������H���C���e���Z���X�Ƀh�L�������g�R�����g��\�������邱�Ƃ��ł���
* (�z���g��C#�ł悭�g���񂾂��ǂ�...)
* (�Z�p�I�ɂ́AXML�Ƃ������������g�p���Ă��܂�)(HTML�Ǝ��Ă邩���H)
* ������///������ƁAVisual Studio�������⊮���Ă����
* �@�@�@�@���ɁA�֐����������Ă���A�֐����̏��///�������ƁA�ƂĂ��y�B
*
* �^�O		����
* <summary>	���\�b�h�̐������L�q����
* <param>	�����̐������L�q����
* <returns>	�߂�l�̐������L�q����
*
*/

//�����C���\�[�X�t�@�C��
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

//�Q�[���֘A
GAME_SCENE OldGameScene;		//�Q�[���̃V�[�����Ǘ�(�ȑO)
GAME_SCENE GameScene;			//�Q�[���̃V�[�����Ǘ�
GAME_SCENE NextScene;			//�؂�ւ���V�[�����Ǘ�

//��ʐ؂�ւ�
BOOL IsFadeOut = FALSE;	//�t�F�[�h�A�E�g
BOOL IsFadeIn = FALSE;	//�t�F�[�h�C��

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txt���o�͂��Ȃ�
	ChangeWindowMode(GAME_WINDOW_MODE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�E�B���h�E�̉𑜓x��ݒ�
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			//�E�B���h�E�̑傫����ݒ�
	SetWindowIconID(GAME_ICON_ID);						//�A�C�R���t�@�C����Ǎ�
	SetMainWindowText(GAME_WINDOW_NAME);				//�E�B���h�E�̃^�C�g���̕���
	SetWindowStyleMode(GAME_WINDOWBAR_KIND);			//�^�C�g���o�[�̎�ނ̓f�t�H���g�ɂ���
	SetBackgroundColor(0, 0, 0);						//�f�t�H���g�̔w�i�̐F
	SetWaitVSyncFlag(GAME_VSYNC_OFF);					//���������̐ݒ�
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	//�c�w���C�u��������������
	if (DxLib_Init() == -1) { return -1; }

	//Draw�n�֐��͗���ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//�p�b�h�̓��͂�������
	MY_PAD_INIT();

	//�t�H���g�̓Ǎ�
	if (MY_FONT_LOAD() == FALSE) { return -1; DxLib_End(); }

	//�摜�̓ǂݍ���
	if (MY_IMAGE_LOAD() == FALSE) { return -1; DxLib_End(); }

	//���y�̓ǂݍ���
	if (MY_AUDIO_LOAD() == FALSE) { return -1; DxLib_End(); }

	//�Q�[���̏�����
	GameScene = GAME_SCENE_TITLE;	//�Q�[���V�[���̓^�C�g����ʂ���

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		//�����Ă���L�[��Ԃ��擾
		MY_ALL_KEYDOWN_UPDATE();

		//�}�E�X�̏�Ԃ��擾
		MY_MOUSE_UPDATE();

		//�p�b�h�̓��͏����X�V����
		MY_PAD_UPDATE();

		//FPS�̍X�V����
		MY_FPS_UPDATE();

		//�ȑO�̃V�[�����擾
		if (GameScene != GAME_SCENE_CHANGE)	//�V�[���؂�ւ��ȊO�Ȃ�
		{
			OldGameScene = GameScene;
		}

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_TITLE:
			MY_TITLE();		//�^�C�g�����
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();		//�v���C���
			break;
		case GAME_SCENE_END:
			MY_END();		//�G���h���
			break;
		case GAME_SCENE_CHANGE:
			MY_CHANGE();	//�؂�ւ����
			break;
		}

		//�V�[���؂�ւ�
		if (OldGameScene != GameScene)
		{
			if (GameScene != GAME_SCENE_CHANGE)	//�V�[���؂�ւ��ȊO�Ȃ�
			{
				NextScene = GameScene;			//���̃V�[����ۑ�
				GameScene = GAME_SCENE_CHANGE;	//��ʐ؂�ւ��ɑJ��
			}
		}

		//�L�[���͂̍X�V����
		MY_INPUT_STR_UPDATE(OldGameScene, GameScene);

		//���݂̃}�E�X�̏���`��
		MY_MOUSE_DRAW();

		//���݂̃p�b�h�̏���`�悷��
		MY_PAD_DRAW();

		//���݂�FPS�l��`��
		MY_FPS_DRAW();

		//����ʂ��ĕ`��
		ScreenFlip();

		//FPS����������Ƃ��́A������҂�
		MY_FPS_WAIT();
	}

	MY_IMAGE_DELETE();	//�摜�̍폜
	MY_AUDIO_DELETE();	//���y�̍폜
	MY_FONT_DELETE();	//�t�H���g�̍폜

	//�c�w���C�u�����g�p�̏I������
	DxLib_End();

	return 0;
}

//########## ���ʂŗ��p����֐� ##########

//�C�ӂ͈̔͂ŗ������擾����
int GetRangeRand(int min, int max)
{
	//�����̎���쐬
	static BOOL IsSeed = FALSE;	//static:�֐��̏������I�����Ă��l��ێ�
	if (IsSeed == FALSE) { srand((unsigned int)time(NULL)); IsSeed = TRUE; }	//�����̎�𐶐�

	//�������������l�̕� = ��������������l - ���������������l
	//rand() % ( �������������l�̕� + 1 ) + ���������������l
	return rand() % (max - min + 1) + min;
}

//�x���@����ʓx�@�ɕϊ�
float DegToRad(int deg)
{
	//�p�x * �~���� / 180
	return deg * DX_PI / 180;
}

//�ʓx�@����x���@�ɕϊ�
int RadToDeg(float rad)
{
	//���W�A�� * 180 / �~����
	return rad * 180.0f / DX_PI;
}
