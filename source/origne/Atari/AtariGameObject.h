#pragma once

#include <./core/Object/object.h>
#include <./core/Component/Render/ModelRenderComponent.h>
#include <./DirectX/math/AABB.h>
#include <./core/Component/Collision/CollisionSphereComponent.h>

#include <./AssetManager/ModelLoader.h>

namespace mslib {
namespace component {
class AtariComponent;
}
namespace object {
class AtariGameObject :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
	static constexpr const char* TestUpdateName = "AtariUpdate";
	static constexpr const int HIT = 1;
	static constexpr const int NO_HIT= 0;
public:
	AtariGameObject() = default;
	~AtariGameObject() = default;

	void Initialize()override;
	//void Update()override;

	void AtariUpdate();

private:
	void ImGuiDraw()override;
	// �I�u�W�F�N�g�ň�x�����ʂ�
	// AssetManager�ɃA�V���v��o�^�ł���΂���͏�����
	static bool once;
	
	// ���f���f�[�^
	render::ModelData m_modelData;

	// ���f���f�[�^
	static render::ModelData m_baseModel;
	
	// �}�e���A���f�[�^
	static render::MaterialData m_materialDataHit;
	static render::MaterialData m_materialDataNoHit;
	
	
	// �����Ă�������x�N�g��
	math::Vector3 m_moveLook;

	// �ړ����x
	float m_speed;

	// CollisionComponent
	component::CollisionSphereComponentPtr m_colSphCom;
};
}
namespace component {
class AtariComponent :public Component{
	BASE_CLASS_IS(Component)
public:
	AtariComponent(const render::MaterialData& _matData, const render::MaterialData& _matDataNohit, render::ModelData&_baseModel):
		m_materialDataHit(_matData),m_materialDataNoHit(_matDataNohit), m_baseModel(_baseModel){
	};
	~AtariComponent() = default;


	void Initialize() override;
	void Update()override;
	void FixedUpdate()override;
	void HitTriggerStay() override;
private:
	const render::MaterialData& m_materialDataHit;
	const render::MaterialData& m_materialDataNoHit;
	render::ModelData &m_baseModel;

	bool m_hitFlag;
};
}
}