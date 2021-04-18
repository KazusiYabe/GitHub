/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//�L�[�{�[�h�����̃w�b�_�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include"game.h"

//########## �}�N����` ##########

//�L�[�{�[�h�̎��
#define KEY_KIND_MAX		256

//########## �\���� ##########

//�L�[�{�[�h�\����
struct KEYBOARD
{
	char AllKeyState[KEY_KIND_MAX];			//���ׂẴL�[�̏�Ԃ�����
	char OldAllKeyState[KEY_KIND_MAX];		//���ׂẴL�[�̏��(���O)������
};

//########## �O���̃O���[�o���ϐ� ##########

//�L�[�{�[�h�̓��͂��擾
extern KEYBOARD keyboard;

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern VOID MY_ALL_KEYDOWN_UPDATE(VOID);					//�L�[�̓��͏�Ԃ��X�V����
extern BOOL MY_KEY_DOWN(int KEY_INPUT_);					//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
extern BOOL MY_KEY_UP(int KEY_INPUT_);						//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
extern BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int milliTime);	//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
extern BOOL MY_KEY_CLICK(int KEY_INPUT_);					//�L�[���N���b�N�������A�L�[�R�[�h�Ŕ��f����