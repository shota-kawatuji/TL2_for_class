#include "stdio.h"
#include "stdlib.h"
#include "TextureConverter.h"

// �R�}���h���C������
enum Argument {
	kApplicationPath,	// �A�v���P�[�V�����̃p�X
	kFilePath,			// �n���ꂽ�t�@�C���̃p�X

	NumArgument
};

int main(int argc, char* argv[]) {
	// argc�̐������J��Ԃ�
	for (int i = 0; i < argc; i++) {
		// ������argv��i�Ԃ�\��
		printf(argv[i]);
		// ���s
		printf("\n");
	}

	// �R�}���h���C�������w��Ȃ�
	if (argc < NumArgument) {
		// �g������\������
		TextureConverter::OutputUsage();
		return 0;
	}

	// COM ���C�u����
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// �e�N�X�`���R���o�[�^
	TextureConverter converter;

	// �I�v�V�����̐�
	int numOptions = argc - NumArgument;
	// �I�v�V�����z��i�_�u���|�C���^�j
	char** options = argv + NumArgument;

	// �e�N�X�`���ϊ�
	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	// COM ���C�u�����̏I��
	CoUninitialize();

	//system("pause");
	return 0;
}
