#include "./AssimpSecen.h"

#include	<assimp/cimport.h>
#include	<assimp\postprocess.h>
#include	<assimp/cimport.h>
#include	<assimp\scene.h>

#include	<Windows.h>

namespace mslib {
namespace assimp {
AssimpScene::~AssimpScene() {
	Exit();
}
const aiScene* AssimpScene::GetScene()
{
	return m_scene;
}

bool AssimpScene::Init(std::string _fileName) {
	m_scene = aiImportFile(_fileName.c_str(),
		aiProcess_ConvertToLeftHanded |
		aiProcessPreset_TargetRealtime_MaxQuality);

	if (m_scene == nullptr) {
		std::string errorLog;
		errorLog = "Not Fount ModelData [" + _fileName + "] error";
		MessageBox(nullptr, errorLog.c_str(), "error", MB_OK);
		return false;
	}

	return true;
}

void AssimpScene::Exit() {
	// ‰Šú‰»‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î‚Í‚¶‚­
	if (m_scene != nullptr) {
		aiReleaseImport(m_scene);
		m_scene = nullptr;
	}
}

bool AssimpScene::HasAnimationData() {
	return m_scene->HasAnimations();
}

}  // namespace assimp
}  // namespace mslib