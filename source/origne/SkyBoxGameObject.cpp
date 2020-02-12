#include "SkyBoxGameObject.h"
#include<./core/Component/Render/QubeMapComponent.h>
namespace mslib {
namespace object {

void SkyBoxGameObject::Initialize() {
	base::Initialize();
	AddComponent<component::QubeMapComponent>("06b226d6-57f8-1694-2804-6d20015c1232_result.jpg");
}

}
}