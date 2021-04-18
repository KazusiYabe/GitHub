/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//�摜�̃w�b�_�t�@�C��
//�����ӁI�I�t�H���_�\���͈ȉ��̒ʂ�ł��B�t�H���_��t�@�C���̏��������Ă�������
//���[�g�f�B���N�g��
// |-IMAGE
//    |-sample.png

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include "game.h"

//########## �}�N����` ##########

//�摜�n
#define IMAGE_SAMPLE_PATH		TEXT(".\\IMAGE\\dragon.png")	//�T���v���̃p�X

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�����摜�n
#define IMAGE_DIV_CHARA_MAX			(4*3)		//�n���h���̍ő吔(�L�����ȂǁA4�����{3�A�j��)
#define IMAGE_DIV_CHARA2_MAX		(8*3)		//�n���h���̍ő吔(�L�����ȂǁA8�����{3�A�j��)
#define IMAGE_DIV_MAP_MAX			(32*32)		//�n���h���̍ő吔(�}�b�v�ȂǁA32�~32)

#define IMAGE_DIV_MAX				256			//�n���h���̍ő吔(�C��)

#define IMAGE_SAMPLE_DIV_PATH		TEXT(".\\IMAGE\\EFFECT\\hikkaku.png")	//�T���v���̃p�X

//########## �\���� ##########

//�ʒu�Ɠ����蔻��
struct POSTION
{
	int x = -1;				//X�ʒu
	int y = -1;				//Y�ʒu
	int width = -1;			//��
	int height = -1;		//����

	RECT coll;				//�����蔻��
	RECT margin;			//�����蔻��(�]��)
};

//�摜�\����
struct IMAGE
{
	int handle = -1;		//�摜�n���h��
	char path[PATH_MAX];	//�p�X
	
	POSTION pos;			//�ʒu�ƕ������A�����蔻��

	BOOL IsDraw = FALSE;	//�`��ł��邩�H
	BOOL IsCenter = FALSE;	//XY�ʒu�𒆐S�ɕ`�悷�邩�H	
};

//�A������摜�̍\����
struct DIVIMAGE
{
	int DivMax = IMAGE_DIV_MAX;		//������
	int handle[IMAGE_DIV_MAX];		//�摜�n���h��
	int nowIndex = 0;				//���݂̃n���h���z��̃C���f�b�N�X
	char path[PATH_MAX];			//�p�X

	POSTION pos;					//�ʒu�ƕ������A�����蔻��

	BOOL IsDraw = FALSE;			//�`��ł��邩�H
	BOOL IsCenter = FALSE;			//XY�ʒu�𒆐S�ɕ`�悷�邩�H

	int AnimCnt = 0;				//�A�j���[�V�����J�E���^
	int AnimCntMAX = 2;				//�A�j���[�V�����J�E���^MAX
	BOOL IsAnimLoop = FALSE;		//�A�j���[�V���������[�v�����邩�H
};

//########## �O���̃O���[�o���ϐ� ##########

//�摜�֘A
extern IMAGE sampleImage;		//�T���v���摜
extern DIVIMAGE sampleDivImage;	//�T���v�������摜

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL MY_IMAGE_LOAD(VOID);		//�摜���܂Ƃ߂ēǍ�
extern BOOL MY_IMAGE_LOAD_FILE(IMAGE* image, const char* path, int x, int y, BOOL IsCenter, RECT margin);	//�摜���P�ǂݍ���

extern BOOL MY_IMAGE_LOAD_DIV_FILE(
	DIVIMAGE* image, const char* path,
	int retu, int gyo, int width, int height,
	int x, int y, BOOL IsCenter, RECT margin);	//�摜�𕪊����ēǂݍ���

extern VOID ImageCollUpdate(POSTION* pos);	//�摜�̓����蔻��̈ʒu���X�V����
extern VOID DrawImage(IMAGE image);			//�摜�`��
extern VOID DrawDivImage(DIVIMAGE* image);	//�����摜�`��
extern VOID MY_IMAGE_DELETE(VOID);			//�摜���܂Ƃ߂č폜