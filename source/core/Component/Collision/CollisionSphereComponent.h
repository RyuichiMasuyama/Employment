#pragma once

#include "./CollisionBaseComponent.h"

namespace mslib {
namespace component {

class CollisionSphereComponent;
using CollisionSphereComponentPtr = std::weak_ptr<CollisionSphereComponent>;
using CollisionSphereComponentSPtr = std::shared_ptr<CollisionSphereComponent>;

class CollisionSphereComponent :public CollisionBaseComponent, public std::enable_shared_from_this<CollisionSphereComponent> {
	BASE_CLASS_IS(CollisionBaseComponent)
public:
	// コンストラクタ・デストラクタ
	CollisionSphereComponent();
	~CollisionSphereComponent() = default;

	// 初期化
	void Initialize()override;

	// 更新処理
	void Update()override;

	const float& GetSize();
	void SetSize(float _size);
private:
	float m_size;
};

}
}