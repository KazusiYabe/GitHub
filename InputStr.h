/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//�L�[�������͏����̃w�b�_�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include"game.h"

//########## �}�N����` ##########

//�L�[�������͌n
#define INPUTSTR_MAX	33	//���p��32�����܂�(�S�p��16�����܂�)

//########## �\���� ##########

//�L�[�������͍\����
struct INPUTSTR
{
	int StrMax = INPUTSTR_MAX - 1;		//���͕����ő吔(-1�̓k��������)
	BOOL CancelValidFlag = FALSE;		//���͒���ESC�ŃL�����Z���ł��邩�H TRUE�ŃL�����Z���ł���
	BOOL SingleCharOnlyFlag = FALSE;	//���p�����݂̂̓��͂����邩�H�@�@�@TRUE�Ŕ��p�����̂�
	BOOL NumCharOnlyFlag = FALSE;		//���l�����݂̂̓��͂̓��͂����邩�HTRUE�Ő��l�����̂�
	int handle = -1;					//�L�[���̓n���h��
	char StrBuf[INPUTSTR_MAX];			//���͂��������񂪓���
	BOOL CanInputStr = FALSE;			//���ݓ��͂ł��邩�H
	char drawSampleString[INPUTSTR_MAX];	//���̓T���v��������i���͘g�`��p�j
};

//########## �O���̃O���[�o���ϐ� ##########

//�L�[�������͊֘A
extern INPUTSTR inputstr;			//�L�[�������͊Ǘ�
extern FONT sampleInputStrFont;		//���͒��̃T���v���t�H���g

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern VOID MY_INPUT_STR_CREATE(VOID);			//�L�[�������̓n���h�������
extern VOID MY_INPUT_STR_UPDATE(GAME_SCENE old, GAME_SCENE now);		//�L�[���͂̓��͏����X�V����
extern VOID MY_INPUT_STR_PROC(VOID);			//�L�[�������͂��s��
extern VOID MY_INPUT_STR_DRAW(int x, int y, FONT font, unsigned int c);	//�L�[���͒��̕������`�悷��
extern VOID MY_INPUT_STR_DELETE(VOID);			//�L�[�������̓n���h�����폜����