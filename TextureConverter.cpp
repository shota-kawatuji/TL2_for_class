#include "TextureConverter.h"
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath, int numOptions, char* options[])
{
	// �e�N�X�`����ǂݍ���
	LoadWICTextureFromFile(filePath);

	// DDS�`���ɕϊ����ď����o��
	SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::OutputUsage()
{
	printf("�摜�t�@�C������WIC�`������DDS�`���ɕϊ����܂��B\n");
	printf("\n");
	printf("TextureConverter[�h���C�u:][�p�X][�t�@�C����]\n");
	printf("\n");
	printf("[�h���C�u:][�p�X][�t�@�C����]:�ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂��B\n");
	printf("\n");
	printf("[-ml level]: �~�b�v���x�����w�肵�܂��B0���w�肷���1x1�܂ł̃t���}�b�v�`���[���𐶐����܂��B\n");
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	HRESULT result;
	// �t�@�C���p�X�����C�h������ɕϊ�
	std::wstring wfilePath = ConvertMultiByteStringToWideString(filePath);

	// �e�N�X�`����ǂݍ���
	result = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));

	// �t�H���_�p�X�ƃt�@�C�����𕪗�����
	SeparateFilePath(wfilePath);
}

void TextureConverter::SeparateFilePath(const wstring& filePath)
{
	size_t pos1;
	wstring exceptExt;

	// ��؂蕶�� '.' ���o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');
	// �������q�b�g������
	if (pos1 != wstring::npos) {
		// ��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		// ��؂蕶���̑O�܂ł𔲂��o��
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	// ��؂蕶�� '\\' ���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('\\');
	if (pos1 != wstring::npos) {
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directrtPath_ = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	// ��؂蕶�� '/' ���o�Ă����ԍŌ�̕���������
	pos1 = exceptExt.rfind('/');
	if (pos1 != wstring::npos) {
		// ��؂蕶���̑O�܂ł��f�B���N�g���p�X�Ƃ��ĕۑ�
		directrtPath_ = exceptExt.substr(0, pos1 + 1);
		// ��؂蕶���̌����t�@�C�����Ƃ��ĕۑ�
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	// ��؂蕶�����Ȃ��̂Ńt�@�C�����݂̂Ƃ��Ĉ���
	directrtPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile(int numOptions, char* options[])
{
	HRESULT result;
	ScratchImage mipChain;
	size_t mipLevel = 0;

	// �~�j�}�b�v����
	result = GenerateMipMaps(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(),
		TEX_FILTER_DEFAULT, mipLevel, mipChain);
	if (SUCCEEDED(result)) {
		// �C���[�W�ƃ��^�f�[�^���A�~�j�}�b�v�łŒu��������
		scratchImage_ = move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	// ���k�`���ɕϊ�
	ScratchImage converted;
	result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_,
		DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT |
		TEX_COMPRESS_PARALLEL, 1.0f, converted);
	if (SUCCEEDED(result))
	{
		scratchImage_ = move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	// �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata_.format = MakeSRGB(metadata_.format);

	// �o�̓t�@�C������ݒ肷��
	wstring filePath = directrtPath_ + fileName_ + L".dds";

	// DDS�t�@�C�������o��
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));

	// �~�b�v�}�b�v���x���w�������
	for (int i = 0; i < numOptions; i++) {
		if (string(options[i]) == "-ml") {
			// �~�b�v���x���w��
			mipLevel = stoi(options[i + 1]);
			break;
		}
	}
}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{
	// ���C�h������ɕϊ������ۂ̕�������v�Z
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	// ���C�h������
	std::wstring wString;
	wString.resize(filePathBufferSize);

	// ���C�h������ɕϊ�
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}
