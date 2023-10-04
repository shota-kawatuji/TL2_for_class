#pragma once
#include "DirectXTex.h"
#include <string>
using namespace std;

class TextureConverter
{
public: // メンバ関数
	/// <summary>
	/// テクスチャをWICからDDSに変換する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void ConvertTextureWICToDDS(const string& filePath);

private: // 静的メンバ関数
	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadWICTextureFromFile(const string& filePath);

	/// <summary>
	/// フォルダパスとファイル名を分解する
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void SeparateFilePath(const wstring& filePath);

	/// <summary>
	/// DDSテクスチャとしてファイル書き出し
	/// </summary>
	void SaveDDSTextureToFile();

private:
	/// <summary>
	/// マルチバイト文字列をワイド文字列に変換
	/// </summary>
	/// <param name="mString">マルチバイト文字列</param>
	/// <returns>ワイド文字列</returns>
	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

private: // メンバ変数
	// 画像の情報
	DirectX::TexMetadata metadata_;
	// 画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;
	// ディレクトリパス
	wstring directrtPath_;
	// ファイル名
	wstring fileName_;
	// ファイル拡張子
	wstring fileExt_;
};
