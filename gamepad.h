/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//�Q�[���p�b�h�����̃w�b�_�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include"game.h"

//########## �}�N����` ##########

//�Q�[���p�b�h
#define PAD_MAX		(4+1)	//�ő�ڑ���(0�Ԗڂ̓_�~�[)
#define PAD_BUTTON_MAX 16	//�{�^���̐�

#define PAD_TEST_POWER	100//�ڑ��e�X�g�U���p���[(0�`1000)
#define PAD_TEST_MSEC	500	//�ڑ��e�X�g�U������(�~���b)

#define PAD_DEADZONE 0.10f	//�W���C�p�b�h�̓��͕����̖����͈͂�ݒ�(�f�t�H���g��0.35/0.0�`1.0�̊�)

//########## �񋓌^ ##########
enum PAD_BUTTON
{
	PADBTN_DOWN,
	PADBTN_LEFT,
	PADBTN_RIGHT,
	PADBTN_UP,
	PADBTN_1,
	PADBTN_2,
	PADBTN_3,
	PADBTN_4,
	PADBTN_5,
	PADBTN_6,
	PADBTN_7,
	PADBTN_8,
	PADBTN_9,
	PADBTN_10,
	PADBTN_11,
	PADBTN_12,
};	//�p�b�h�̃{�^���̎��

//########## �\���� ##########

//�Q�[���p�b�h�\����
struct GAMEPAD
{
	int InputState = -1;	//�ڑ����

	int NewAnalogX = 0;		//�A�i���O���o�[�̌X���X�ʒu(�X�V)
	int NewAnalogY = 0;		//�A�i���O���o�[�̌X���Y�ʒu(�X�V)
	int OldAnalogX = 0;		//�A�i���O���o�[�̌X���X�ʒu(���O)
	int OldAnalogY = 0;		//�A�i���O���o�[�̌X���Y�ʒu(���O)

	int AllButtonState[PAD_BUTTON_MAX];			//���ׂẴ{�^���̏��
	int OldButtonKeyState[PAD_BUTTON_MAX];		//���ׂẴ{�^���̏��(���O)
};

//�Q�[���p�b�h����m�F�p
struct DEBUG_GAMEPAD
{
	int RoundLeft = 20;		//���a
	POINT ptLeft = { 0,0 };	//�ʒu
	unsigned int Color;		//�F
};

//########## �O���̃O���[�o���ϐ� ##########

//�p�b�h�֘A
extern int padConnectNum ;			//�p�b�h�̐ڑ���
extern GAMEPAD gamepad[PAD_MAX];	//GAMEPAD�f�[�^���Ǘ�

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B
extern VOID MY_PAD_INIT(VOID);													//�p�b�h�̏�������������
extern VOID MY_PAD_UPDATE(VOID);												//�p�b�h�̓��͏����X�V����
extern BOOL MY_PAD_DOWN(int DX_INPUT_PAD, PAD_BUTTON PAD_);						//�{�^���������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����
extern BOOL MY_PAD_UP(int DX_INPUT_PAD, PAD_BUTTON PAD_);						//�{�^���������グ�����A�}�E�X�R�[�h�Ŕ��f����
extern BOOL MY_PADDOWN_KEEP(int DX_INPUT_PAD, PAD_BUTTON PAD_, int milliTime);	//�{�^�������������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����
extern BOOL MY_PAD_CLICK(int DX_INPUT_PAD, PAD_BUTTON PAD_);					//�}�E�X���N���b�N�������A�}�E�X�R�[�h�Ŕ��f����
extern VOID MY_PAD_DRAW(VOID);													//�p�b�h�̏���`�悷��