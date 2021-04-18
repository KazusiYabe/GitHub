/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//�t�H���g�����̃w�b�_�t�@�C��
//�����ӁI�I�t�H���_�\���͈ȉ��̒ʂ�ł��B�t�H���_��t�@�C���̏��������Ă�������
//���[�g�f�B���N�g��
// |-FONT
//    |-TanukiMagic.ttf
//    |-Jiyucho.ttf

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include "game.h"

//########## �}�N����` ##########

//�t�H���g�n
#define FONT_TANUKI_PATH		TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANUKI_NAME		TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

#define FONT_JIYU_PATH			TEXT(".\\FONT\\Jiyucho.ttf")		//�t�H���g�̏ꏊ
#define FONT_JIYU_NAME			TEXT("���䂤���傤�t�H���g")		//�t�H���g�̖��O

#define DEF_FONT_NAME	FONT_JIYU_NAME				//�f�t�H���g�̃t�H���g��
#define DEF_FONT_SIZE	20							//�f�t�H���g�̃T�C�Y
#define DEF_FONT_THINCK	1							//�f�t�H���g�̑���
#define DEF_FONT_TYPE	 DX_FONTTYPE_ANTIALIASING	//�f�t�H���g�̃^�C�v

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

//########## �\���� ##########

//�t�H���g�\����
struct FONT
{
	int handle;		//�t�H���g�n���h��
	int Size;		//�t�H���g�̃T�C�Y
	int Thinck;		//�t�H���g�̑���
	int Type = DX_FONTTYPE_ANTIALIASING;	//�t�H���g�̃^�C�v
	char Name[STR_MAX] = FONT_TANUKI_NAME;	//�t�H���g�̖��O
};

//########## �O���̃O���[�o���ϐ� ##########

//�t�H���g�֘A
extern FONT fontdef;		//�f�t�H���g�̃t�H���g
extern FONT fontSample;		//�T���v���̃t�H���g

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL MY_FONT_LOAD(VOID);		//�t�H���g�̓Ǎ�
extern VOID MY_FONT_SET(FONT* f, const char* name, int size, int thinck, int type);	//�t�H���g�ɐݒ肷��
extern VOID MY_FONT_DRAWSET(FONT f);	//�t�H���g��S�̂ɔ��f������
extern VOID MY_FONT_DELETE(VOID);		//�t�H���g�̍폜