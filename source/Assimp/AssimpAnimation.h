#pragma once

#include "./AssimpSecen.h"

namespace mslib {
namespace assimp {
class AssimpAnimation {
public:
	AssimpAnimation() = default;
	~AssimpAnimation() = default;

	// �������E���[�h
	bool Init(std::string _fileName);
	
	void Exit();

	const aiScene* GetScene();

private:
	AssimpScene m_assimpScene;
};
}
}