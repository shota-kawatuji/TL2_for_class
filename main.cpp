#include "stdio.h"
#include "stdlib.h"
#include <DirectXTex.h>
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
	assert(argc >= NumArgument);

	// COM ライブラリ
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// テクスチャコンバータ
	TextureConverter converter;

	// テクスチャ変換
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	// COM ライブラリの終了
	CoUninitialize();

	system("pause");
	return 0;
}
