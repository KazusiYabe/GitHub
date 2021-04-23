/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Copyright (c) 2020
//Hamamatsu Mirai Sougou Senmongakkou GameCreate Y.Suzuki
//All rights reserved.

//���y�̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "FPS.h"
#include "audio.h"

//########## �O���[�o���ϐ� ##########

//���y�Ǘ�
AUDIO NowPlayBGM;	//���ݗ��ꂢ��BGM
AUDIO TitleBGM;		//�^�C�g����BGM
AUDIO PlayBGM;		//�v���C��BGM
AUDIO EndClearBGM;	//�G���h�N���A��BGM
AUDIO EndOverBGM;	//�G���h�I�[�o�[��BGM

AUDIO sampleSE;			//�T���v��SE
AUDIO selectSE;			//�I��SE
AUDIO selectEnterSE;	//�I��SE

AUDIO wazaSE[WAZA_EFFECT_MAX];	//�Z�̃G�t�F�N�g��SE

AUDIO dragonSE;	//�h���S���̖���
AUDIO slimeSE;	//�X���C���̖���
AUDIO playerSE;	//�v���C���̖���

//########## �֐� ##########

/// <summary>
/// ���y���܂Ƃ߂ēǍ�
/// </summary>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL MY_AUDIO_LOAD(VOID)
{
	//BGM�̓ǂݍ���
	if (MY_AUDIO_LOAD_FILE(&TitleBGM, BGM_TITLE_PATH, 50, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&PlayBGM, BGM_PLAY_PATH, 25, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&EndClearBGM, BGM_END_CLEAR_PATH, 50, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&EndOverBGM, BGM_END_OVER_PATH, 50, DX_PLAYTYPE_LOOP) == FALSE) { return FALSE; }

	//�T���v�����y�̓ǂݍ���(�����͊֐��̐�����ǂ�łˁI)
	if (MY_AUDIO_LOAD_FILE(&sampleSE, SE_SAMPLE_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&selectSE, SE_SELECT_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&selectEnterSE, SE_SELECT_ENTER_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }

	//���̉��y���R�R�œǂݍ��ނ���
	if (MY_AUDIO_LOAD_FILE(&wazaSE[0], SE_WAZA0_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[1], SE_WAZA1_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[2], SE_WAZA2_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[3], SE_WAZA3_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[4], SE_WAZA4_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[5], SE_WAZA5_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[6], SE_WAZA6_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[7], SE_WAZA7_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[8], SE_WAZA8_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[9], SE_WAZA9_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[10], SE_WAZA10_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[11], SE_WAZA11_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[12], SE_WAZA12_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[13], SE_WAZA13_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&wazaSE[14], SE_WAZA14_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }

	if (MY_AUDIO_LOAD_FILE(&dragonSE, SE_DRAGON_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&slimeSE, SE_SLIME_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	if (MY_AUDIO_LOAD_FILE(&playerSE, SE_PLAYER_PATH, 100, DX_PLAYTYPE_BACK) == FALSE) { return FALSE; }
	
	return TRUE;
}

/// <summary>
/// ���y���܂Ƃ߂č폜
/// </summary>
/// <returns></returns>
VOID MY_AUDIO_DELETE(VOID)
{
	//�T���v�����y���폜
	DeleteSoundMem(TitleBGM.handle);
	DeleteSoundMem(PlayBGM.handle);
	DeleteSoundMem(EndClearBGM.handle);
	DeleteSoundMem(EndOverBGM.handle);

	DeleteSoundMem(sampleSE.handle);
	DeleteSoundMem(selectSE.handle);
	DeleteSoundMem(selectEnterSE.handle);

	DeleteSoundMem(dragonSE.handle);
	DeleteSoundMem(slimeSE.handle);
	DeleteSoundMem(playerSE.handle);

	//���̉��y���R�R�ō폜���邱��
	for (int cnt = 0; cnt < WAZA_EFFECT_MAX; cnt++)
	{
		DeleteSoundMem(wazaSE[cnt].handle);
	}

	return;
}

/// <summary>
/// ���y���P�ǂݍ���
/// </summary>
/// <param name = "audio">�ݒ肵�������y�\����</param>
/// <param name = "path">���y�̃t�@�C���p�X</param>
/// <param name = "volume">�{�����[��(0%�`100%)</param>
/// <param name = "playType">�Đ��`�� DX_PLAYTYPE_BACK / DX_PLAYTYPE_LOOP�Ȃ�</param>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL MY_AUDIO_LOAD_FILE(AUDIO* audio, const char* path, int volume, int playType)
{
	//�T���v�����y�̓ǂݍ���
	audio->handle = LoadSoundMem(path);
	if (audio->handle == -1)
	{
		//�ǂݍ��݃G���[
		MessageBox(GetMainWindowHandle(), path, AUDIO_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ʂ�ݒ�
	SetVolumeAudio(audio, GetVolume(volume));

	//�Đ��`����ݒ�
	audio->playType = playType;

	//���̑��ݒ�
	audio->fadeInCnt = 0;
	audio->fadeInCntMax = 0;
	audio->fadeOutCnt = 0;
	audio->fadeOutCntMax = 0;

	return TRUE;
}

/// <summary>
/// ���y�Đ�
/// </summary>
/// <param name="audio">�Đ����鉹�y�\����</param>
/// <returns></returns>
VOID PlayAudio(AUDIO audio)
{
	//���[�v�Đ��łȂ���΁A���̂܂܍Đ�����
	if (audio.playType == DX_PLAYTYPE_BACK)
	{
		PlaySoundMem(audio.handle, audio.playType);//���y�̍Đ�
	}
	//���[�v�Đ��̂Ƃ��́A���y���Đ�����Ă��Ȃ���΁A�Đ�����
	else if (audio.playType == DX_PLAYTYPE_LOOP)
	{
		if (CheckSoundMem(audio.handle) == 0)
		{
			PlaySoundMem(audio.handle, audio.playType);//���y�̍Đ�
		}
	}

	return;
}

/// <summary>
/// ���y�̃{�����[���擾
/// </summary>
/// <param name="audio">�擾���鉹�y�\����</param>
/// <param name = "volume">�{�����[��(0%�`100%)</param>
/// <returns></returns>
int GetVolumeAudio(AUDIO audio)
{
	//���ʂ��擾
	return audio.volume;
}

/// <summary>
/// ���y�̃{�����[���ݒ�
/// </summary>
/// <param name="audio">�ݒ肷�鉹�y�\����</param>
/// <param name = "volume">�{�����[��(0%�`100%)</param>
/// <returns></returns>
VOID SetVolumeAudio(AUDIO* audio, int volume)
{
	//���ʂ�ݒ�
	audio->volume = volume;
	ChangeVolumeSoundMem(audio->volume, audio->handle);

	return;
}

/// <summary>
/// ���y�̃{�����[���ύX
/// </summary>
/// <param name="audio">�ύX���鉹�y�\����</param>
/// <param name = "volume">�{�����[��(0%�`100%)</param>
/// <returns></returns>
VOID ChangeVolumeAudio(AUDIO* audio, int volume)
{
	//���ʂ�ݒ�i�\���̂̃{�����[���͕ύX���Ȃ��j
	ChangeVolumeSoundMem(volume, audio->handle);

	return;
}

/// <summary>
/// ���y��~
/// </summary>
/// <param name="audio">��~���鉹�y�\����</param>
/// <returns></returns>
VOID StopAudio(AUDIO* audio)
{
	//���y�̒�~
	StopSoundMem(audio->handle);

	//�t�F�[�h�n�J�E���^������
	audio->fadeInCnt = 0;
	audio->fadeOutCnt = 0;

	return;
}

/// <summary>
/// �t�F�[�h�C������
/// </summary>
/// <param name="audio">�t�F�[�h�C�����鉹�y�\����</param>
/// <param name="milliTime">�t�F�[�h�C�����鎞��(�~���b)</param>
/// <returns></returns>
VOID FadeInPlayAudio(AUDIO* audio, int milliTime)
{
	//�ŏ��̃t�F�[�h�C�������̂Ƃ�
	if (audio->fadeInCnt == 0)
	{
		float MilliSec = 1000.0f;	//�P�b��1000�~���b

		//���������鎞��=�b���~FPS�l
		//��j60FPS�̃Q�[���ŁA1�b�ԗ���������Ȃ�A1�b�~60FPS
		int UpdateTime = (milliTime / MilliSec) * GAME_FPS;	//���̎��Ԃ�MAX

		//�t�F�[�h�C���̃J�E���^�ݒ�
		audio->fadeInCnt = 0;
		audio->fadeInCntMax = UpdateTime;

		ChangeVolumeAudio(audio, 0);	//���ʂ�0�ɂ���

		//���y�Đ�
		if (CheckSoundMem(audio->handle) == 0) {
			PlayAudio(*(audio));
		}
	}

	//�t�F�[�h�C�����Ă���Ƃ�(�t�F�[�h�C����MAX�l�ȉ��Ȃ��)
	if (audio->fadeInCnt >= 0 && audio->fadeInCnt <= audio->fadeInCntMax)
	{
		//�J�E���^���グ��
		audio->fadeInCnt++;

		//���݂̃J�E���g���ԁ�MAX���ԂŁA���ʂ̑S�̊������v�Z��������~100���ĉ��ʂ�
		float CalcVolume = (float)audio->fadeInCnt / (float)audio->fadeInCntMax * 100;

		//�ǂݍ��ݎ��ɐݒ肵�����ʂ͒����Ȃ��悤�ɒ��ӂ��邱�ƁI
		if (CalcVolume >= GetVolumeAudio(*(audio))) {
			CalcVolume = GetVolumeAudio(*(audio));
		}

		//���ʂ��グ��
		ChangeVolumeAudio(audio, GetVolume(CalcVolume));
	}

	return;
}

/// <summary>
/// �t�F�[�h�A�E�g����
/// </summary>
/// <param name="audio">�t�F�[�h�A�E�g���鉹�y�\����</param>
/// <param name="milliTime">�t�F�[�h�A�E�g���鎞��(�~���b)</param>
/// <returns>�t�F�[�h�A�E�g����FALSE / �t�F�[�h�A�E�g�I����TRUE</returns>
BOOL FadeOutPlayAudio(AUDIO* audio, int milliTime)
{
	//�ŏ��̃t�F�[�h�A�E�g�����̂Ƃ�
	if (audio->fadeOutCnt == 0)
	{
		float MilliSec = 1000.0f;	//�P�b��1000�~���b

		//���������鎞��=�b���~FPS�l
		//��j60FPS�̃Q�[���ŁA1�b�ԗ���������Ȃ�A1�b�~60FPS
		int UpdateTime = (milliTime / MilliSec) * GAME_FPS;	//���̎��Ԃ�MAX

		//�t�F�[�h�A�E�g�̃J�E���^�ݒ�
		audio->fadeOutCnt = 0;
		audio->fadeOutCntMax = UpdateTime;

		ChangeVolumeAudio(audio, GetVolume(GetVolumeAudio(*(audio))));	//���ʂ�MAX�ɂ���

		//���y�Đ�
		if (CheckSoundMem(audio->handle) == 0) {
			PlayAudio(*(audio));
		}
	}

	//�t�F�[�h�A�E�g���Ă���Ƃ�(�t�F�[�h�A�E�g��MAX�l�ȉ��Ȃ��)
	if (audio->fadeOutCnt >= 0 && audio->fadeOutCnt <= audio->fadeOutCntMax)
	{
		//�J�E���^���グ��
		audio->fadeOutCnt++;

		//(MAX����-���݂̃J�E���g����)��MAX���ԂŁA���ʂ̑S�̊������v�Z��������~100���ĉ��ʂ�
		float CalcVolume = ((float)audio->fadeOutCntMax - (float)audio->fadeOutCnt) / (float)audio->fadeOutCntMax * 100;

		//�ǂݍ��ݎ��ɐݒ肵�����ʂ͒����Ȃ��悤�ɒ��ӂ��邱�ƁI
		if (CalcVolume >= GetVolumeAudio(*(audio))) { CalcVolume = GetVolumeAudio(*(audio)); }

		//���ʂ�������
		ChangeVolumeAudio(audio, GetVolume(CalcVolume));

		//�t�F�[�h�A�E�g��
		return FALSE;
	}
	else
	{
		return TRUE;
	}

	return FALSE;
}