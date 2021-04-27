//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"  //DxLib���g�����͕K�v

//�}�N����`
#define GAME_TITLE "�Q�[���^�C�g��"
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720
#define GAME_COLOR 32

#define GAME_ICON_ID  333
// �v���O������ �� ����n�܂�܂�
//Windows�̃v���O�������@ = (WinAPI)�œ����Ă���
//DxLib�́ADirectx �Ƃ����A�Q�[���v���O�������ȒP�Ɏg����d�g��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetMainWindowText(GAME_TITLE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	SetBackgroundColor(255, 255, 255);


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�������[�v
	while (1)
	{
		if (CheckHitKeyAll() != 0)
		{
			break;  //�������[�v�𔲂���
		}

		//���b�Z�[�W���󂯎�葱����
		if (ProcessMessage() != 0)
		{
			break;  //�������[�v�𔲂���
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}