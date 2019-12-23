#include "AssimpAnimation.h"
#include <Windows.h>

namespace mslib {
namespace assimp {

bool AssimpAnimation::Init(std::string _fileNmae) {
	// シーンをロード
	bool sts = m_assimpScene.Init(_fileNmae);

	// シーンのロードに失敗しているのでfalse
	if (!sts) {
		return false;
	}

	if (m_assimpScene.HasAnimationData()) {
		MessageBox(nullptr, "This File is not have AnimationData", "error", MB_OK);
	}

	return true;
}

void AssimpAnimation::Exit() {
	// 終了処理(nullチェックは内部で行っている)
	m_assimpScene.Exit();
}

const aiScene * AssimpAnimation::GetScene() {
	return m_assimpScene.GetScene();
}

}  // namespace assimp 
}  // namespace mslib