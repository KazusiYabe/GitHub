/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.
#pragma once

//���y�̃w�b�_�t�@�C��
//�����ӁI�I�t�H���_�\���͈ȉ��̒ʂ�ł��B�t�H���_��t�@�C���̏��������Ă�������
//���[�g�f�B���N�g��
// |-AUDIO
//    |-BGM
//       |-sampleBGM.mp3
//    |-SE
//       |-sampleSE.mp3

//�����ӁI
//PC�̃T�E���h�h���C�o���������Ȃ��Ƃ��́A(�X�s�[�J�[�ŉ����łȂ�)
//�ǂݍ��݃G���[����������ꍇ������܂��B�X�s�[�J�[�����特���ł邩�m�F�I

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include "game.h"

//########## �}�N����` ##########

//���y�n
#define BGM_TITLE_PATH		TEXT(".\\AUDIO\\BGM\\title.ogg")	
#define BGM_PLAY_PATH		TEXT(".\\AUDIO\\BGM\\play.ogg")	
#define BGM_END_CLEAR_PATH	TEXT(".\\AUDIO\\BGM\\battle.ogg")	
#define BGM_END_OVER_PATH	TEXT(".\\AUDIO\\BGM\\���̑ٓ�.ogg")	
#define SE_SAMPLE_PATH		TEXT(".\\AUDIO\\SE\\coin.ogg")		

//�֐��`���}�N��
#define GetVolume(volume)	(255 * volume / 100)					//�{�����[���̌v�Z��

//�G���[���b�Z�[�W
#define AUDIO_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//########## �\���� ##########

//���y�\����
struct AUDIO
{
	int handle = -1;		//�摜�n���h��
	char path[PATH_MAX];	//�p�X
	int volume = -1;		//����
	int playType = -1;		//�Đ��`��
	int fadeInCnt = 0;				//�t�F�[�h�C���J�E���^
	int fadeInCntMax = 0;			//�t�F�[�h�C���J�E���^MAX
	int fadeOutCnt = 0;				//�t�F�[�h�A�E�g�J�E���^
	int fadeOutCntMax = 0;			//�t�F�[�h�A�E�g�J�E���^MAX
};

//########## �O���̃O���[�o���ϐ� ##########

//���y�֘A
extern AUDIO NowPlayBGM;	//���ݗ��ꂢ��BGM
extern AUDIO TitleBGM;		//�^�C�g����BGM
extern AUDIO PlayBGM;		//�v���C��BGM
extern AUDIO EndClearBGM;	//�G���h�N���A��BGM
extern AUDIO EndOverBGM;	//�G���h�I�[�o�[��BGM
extern AUDIO sampleSE;		//�T���v��SE

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL MY_AUDIO_LOAD(VOID);		//���y���܂Ƃ߂ēǍ�
extern BOOL MY_AUDIO_LOAD_FILE(AUDIO* audio, const char* path, int volume, int playType);	//���y���P�ǂݍ���
extern VOID FadeInOutResetAudio(VOID);	//�t�F�[�h�C�� / �t�F�[�h�A�E�g���������Z�b�g����
extern VOID MY_AUDIO_DELETE(VOID);		//���y���܂Ƃ߂č폜

extern VOID PlayAudio(AUDIO audio);			//���y�Đ�
extern VOID StopAudio(AUDIO* audio);		//���y��~

extern int GetVolumeAudio(AUDIO audio);						//���y�̃{�����[���擾
extern VOID SetVolumeAudio(AUDIO* audio, int volume);		//���y�̃{�����[���ݒ�
extern VOID ChangeVolumeAudio(AUDIO* audio, int volume);	//���y�̃{�����[���ύX

extern VOID FadeInPlayAudio(AUDIO* audio, int milliTime);	//�t�F�[�h�C������
extern BOOL FadeOutPlayAudio(AUDIO* audio, int milliTime);	//�t�F�[�h�A�E�g����
