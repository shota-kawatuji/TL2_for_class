#pragma once
#include "DirectXTex.h"
#include <string>
using namespace std;

class TextureConverter
{
public: // �����o�֐�
	/// <summary>
	/// �e�N�X�`����WIC����DDS�ɕϊ�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void ConvertTextureWICToDDS(const string& filePath);

private: // �ÓI�����o�֐�
	/// <summary>
	/// �e�N�X�`���t�@�C���ǂݍ���
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void LoadWICTextureFromFile(const string& filePath);

	/// <summary>
	/// �t�H���_�p�X�ƃt�@�C�����𕪉�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void SeparateFilePath(const wstring& filePath);

	/// <summary>
	/// DDS�e�N�X�`���Ƃ��ăt�@�C�������o��
	/// </summary>
	void SaveDDSTextureToFile();

private:
	/// <summary>
	/// �}���`�o�C�g����������C�h������ɕϊ�
	/// </summary>
	/// <param name="mString">�}���`�o�C�g������</param>
	/// <returns>���C�h������</returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private: // �����o�ϐ�
	// �摜�̏��
	DirectX::TexMetadata metadata_;
	// �摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scratchImage_;
	// �f�B���N�g���p�X
	wstring directrtPath_;
	// �t�@�C����
	wstring fileName_;
	// �t�@�C���g���q
	wstring fileExt_;
};
