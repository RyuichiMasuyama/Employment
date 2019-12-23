#include "AssimpAnimation.h"
#include <Windows.h>

namespace mslib {
namespace assimp {

bool AssimpAnimation::Init(std::string _fileNmae) {
	// �V�[�������[�h
	bool sts = m_assimpScene.Init(_fileNmae);

	// �V�[���̃��[�h�Ɏ��s���Ă���̂�false
	if (!sts) {
		return false;
	}

	if (m_assimpScene.HasAnimationData()) {
		MessageBox(nullptr, "This File is not have AnimationData", "error", MB_OK);
	}

	return true;
}

void AssimpAnimation::Exit() {
	// �I������(null�`�F�b�N�͓����ōs���Ă���)
	m_assimpScene.Exit();
}

const aiScene * AssimpAnimation::GetScene() {
	return m_assimpScene.GetScene();
}

}  // namespace assimp 
}  // namespace mslib