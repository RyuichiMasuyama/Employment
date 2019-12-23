#pragma once
#include <string>
#include <assimp/cimport.h>

namespace mslib {
namespace assimp {

// �݌v�~�X�AAsset�N���X�������virtual�Ŏ����Ƃ����ق����悩����
class AssimpScene {
public:
	// �f�t�H���g�R���X�g���N�^�E�f�X�g���N�^
	AssimpScene() = default;
	~AssimpScene();

	// Scene�擾
	const aiScene* GetScene();

	// �������E���[�h
	bool Init(std::string _fileName);

	// �I������
	void Exit();

	// �A�j���[�V�����f�[�^��ێ����Ă��邩�H
	bool HasAnimationData();
private:
	const aiScene * m_scene = nullptr;
};

}  // namespace assimp
}  // namespace mslib