/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//�}�E�X�����̃w�b�_�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include"game.h"

//########## �}�N����` ##########

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129		//0x0000�`0x0080�܂�

//########## �\���� ##########

//int�^��POINT�\����
struct iPOINT
{
	int x = -1;	//���W��������
	int y = -1;	//���W��������
};

//�}�E�X�\����
struct MOUSE
{
	int InputValue = 0;	//GetMouseInput�̒l������
	int WheelValue = 0;	//�}�E�X�z�C�[���̉�]��(���̓v���X�l / ��O�̓}�C�i�X�l)
	iPOINT Point;						//�}�E�X�̍��W������
	iPOINT OldPoint;					//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE];	//�}�E�X�̃{�^������(���O)������
	int Button[MOUSE_BUTTON_CODE];		//�}�E�X�̃{�^�����͂�����
};

//########## �O���̃O���[�o���ϐ� ##########

//�}�E�X���͂��擾
extern MOUSE mouse;

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern VOID MY_MOUSE_UPDATE(VOID);								//�}�E�X�̓��͏����X�V����
extern BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_);					//�{�^���������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����
extern BOOL MY_MOUSE_UP(int MOUSE_INPUT_);						//�{�^���������グ�����A�}�E�X�R�[�h�Ŕ��f����
extern BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int milliTime);	//�{�^�������������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����
extern BOOL MY_MOUSE_CLICK(int MOUSE_INPUT_);					//�}�E�X���N���b�N�������A�}�E�X�R�[�h�Ŕ��f����
extern VOID MY_MOUSE_DRAW(VOID);								//�}�E�X�̏���`�悷��