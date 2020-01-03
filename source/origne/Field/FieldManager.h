#pragma once

#include <core/Object/object.h>

namespace mslib {
namespace manager {
class FieldManagerGameObject:public object::GameObject  {
	BASE_CLASS_IS(object::GameObject)

	static constexpr const char* ObjectName= "FieldManager";
public:
	FieldManagerGameObject() = default;
	~FieldManagerGameObject() = default;

	void Initialize()override;

	void Update()override;
private:

};

}
}