#pragma once
#include <string>
#include <assimp/cimport.h>

namespace mslib {
namespace assimp {

// 設計ミス、Assetクラスを作ってvirtualで持っといたほうがよかった
class AssimpScene {
public:
	// デフォルトコンストラクタ・デストラクタ
	AssimpScene() = default;
	~AssimpScene();

	// Scene取得
	const aiScene* GetScene();

	// 初期化・ロード
	bool Init(std::string _fileName);

	// 終了処理
	void Exit();

	// アニメーションデータを保持しているか？
	bool HasAnimationData();
private:
	const aiScene * m_scene = nullptr;
};

}  // namespace assimp
}  // namespace mslib