/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//FPS�����̃w�b�_�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include"game.h"

//########## �}�N����` ##########
#define GAME_FPS			60		//FPS�̐��l	
#define GAME_VSYNC_OFF		TRUE	//�����������Ȃ��FTRUE / ����FFALSE

//########## �\���� ##########

//FPS�\����
struct FPS
{
	BOOL IsInitFlg = FALSE;			//�ŏ��̑���J�n�������擾����t���O
	LONGLONG StartTime = 0;			//����J�n����
	LONGLONG NowTime = 0;			//���݂̎���
	LONGLONG OldTime = 0;			//�ȑO�̎���
	float DeltaTime = 0.000001f;	//�o�ߎ���
	int Count = 1;					//�J�E���^(1�`GAME_FPS)
	float DrawValue = 0.0f;			//�v�Z����
	int SampleRate = GAME_FPS;		//���ς����T���v����
};

//########## �O���̃O���[�o���ϐ� ##########

//FPS�֘A
extern FPS fps;	//FPS���f�[�^���Ǘ�

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern VOID MY_FPS_UPDATE(VOID);		//FPS�l���v���A�X�V����
extern VOID MY_FPS_DRAW(VOID);			//FPS�l��`�悷��
extern VOID MY_FPS_WAIT(VOID);			//FPS�l���v�����A�҂�