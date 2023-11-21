#include "stdio.h"
#include "stdlib.h"
#include "TextureConverter.h"

// コマンドライン引数
enum Argument {
	kApplicationPath,	// アプリケーションのパス
	kFilePath,			// 渡されたファイルのパス

	NumArgument
};

int main(int argc, char* argv[]) {
	// argcの数だけ繰り返す
	for (int i = 0; i < argc; i++) {
		// 文字列argvのi番を表示
		printf(argv[i]);
		// 改行
		printf("\n");
	}

	// コマンドライン引数指定なし
	if (argc < NumArgument) {
		// 使い方を表示する
		TextureConverter::OutputUsage();
		return 0;
	}

	// COM ライブラリ
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// テクスチャコンバータ
	TextureConverter converter;

	// オプションの数
	int numOptions = argc - NumArgument;
	// オプション配列（ダブルポインタ）
	char** options = argv + NumArgument;

	// テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	// COM ライブラリの終了
	CoUninitialize();

	//system("pause");
	return 0;
}
