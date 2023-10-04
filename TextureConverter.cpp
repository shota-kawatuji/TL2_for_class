#include "TextureConverter.h"
#include <WinNls.h>
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	// �e�N�X�`����ǂݍ���
	LoadWICTextureFromFile(filePath);

	// DDS�`���ɕϊ����ď����o��
	SaveDDSTextureToFile();
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

void TextureConverter::SaveDDSTextureToFile()
{
	// �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata_.format = MakeSRGB(metadata_.format);

	HRESULT result;

	// �o�̓t�@�C������ݒ肷��
	wstring filePath = directrtPath_ + fileName_ + L".dds";

	// DDS�t�@�C�������o��
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
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
