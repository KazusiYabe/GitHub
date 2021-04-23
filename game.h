/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//�Q�[���̃��C���w�b�_�t�@�C��

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
//�G���[�}��
#define _CRT_SECURE_NO_WARNINGS

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "math.h"
#include "time.h"

//########## �}�N����` ##########
#define PATH_MAX			255		//�p�X�̒���
#define STR_MAX				255		//�����̒���
#define DEBUG_MODE			FALSE	//�f�o�b�O���[�h

#define GAME_WINDOW_MODE	TRUE	//�E�B���h�E���[�h
#define GAME_WIDTH			1280	//�Q�[���̕�	�i16�j
#define GAME_HEIGHT			720		//�Q�[���̍���	�i 9�j
#define WINDOW_WIDTH		GAME_WIDTH		//�E�B���h�E�̕�
#define WINDOW_HEIGHT		GAME_HEIGHT		//�E�B���h�E�̍���
#define GAME_COLOR			32		//�Q�[���̐F�r�b�g
#define GAME_WINDOWBAR_KIND 0		//�E�B���h�E�o�[�̎��
#define GAME_WINDOW_NAME	"HAMAMI-SlimeQuest-"	//�E�B���h�E�̃^�C�g��
#define GAME_ICON_ID		333		//�E�B���h�E�A�C�R����ID

#define WAZA_EFFECT_MAX	15		//�Z�̃G�t�F�N�g�̐�

//########## �񋓌^ ##########
enum GAME_SCENE {
	GAME_SCENE_TITLE,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_CHANGE
};	//�Q�[���̃V�[��

//########## �O���̃O���[�o���ϐ� ##########
//�Q�[���֘A
extern GAME_SCENE OldGameScene;			//�Q�[���̃V�[�����Ǘ�(�ȑO)
extern GAME_SCENE GameScene;			//�Q�[���̃V�[�����Ǘ�
extern GAME_SCENE NextScene;			//�؂�ւ���V�[�����Ǘ�

//��ʐ؂�ւ�
extern BOOL IsFadeOut;	//�t�F�[�h�A�E�g
extern BOOL IsFadeIn;	//�t�F�[�h�C��

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern VOID MY_TITLE_INIT(VOID);	//�Q�[���^�C�g��������

extern VOID MY_TITLE(VOID);				//�^�C�g�����
extern VOID MY_TITLE_PROC(VOID);		//�^�C�g����ʂ̏���
extern VOID MY_TITLE_DRAW(VOID);		//�^�C�g����ʂ̕`��

extern VOID MY_PLAY(VOID);				//�v���C���
extern VOID MY_PLAY_PROC(VOID);			//�v���C��ʂ̏���
extern VOID MY_PLAY_DRAW(VOID);			//�v���C��ʂ̕`��

extern VOID MY_END(VOID);				//�G���h���
extern VOID MY_END_PROC(VOID);			//�G���h��ʂ̏���
extern VOID MY_END_DRAW(VOID);			//�G���h��ʂ̕`��

extern VOID MY_CHANGE(VOID);			//�؂�ւ����
extern VOID MY_CHANGE_PROC(VOID);		//�؂�ւ���ʂ̏���
extern VOID MY_CHANGE_DRAW(VOID);		//�؂�ւ���ʂ̕`��

extern int GetRangeRand(int min, int max);	//�C�ӂ͈̔͂ŗ������擾����
extern float DegToRad(int deg);				//�x���@����ʓx�@�ɕϊ�
extern int RadToDeg(float rad);				//�ʓx�@����x���@�ɕϊ�