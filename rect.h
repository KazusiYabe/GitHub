#pragma once
/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//RECT�̃w�b�_�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include "game.h"

//########## �}�N����` ##########


//########## �\���� ##########

//########## �O���̃O���[�o���ϐ� ##########


//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL RectCollCheck(RECT a, RECT b);						//�l�p�̈�̓����蔻����`�F�b�N����
extern RECT GetRect(int left, int top, int right, int bottom);	//RECT�^���ꎞ�I�ɓn��
extern void DrawRect(RECT r, unsigned int color, bool b);		//RECT�𗘗p���Ďl�p��`��