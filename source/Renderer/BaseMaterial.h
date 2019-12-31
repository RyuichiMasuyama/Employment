#pragma once

#include <string>
#include "./MaterialData.h"

namespace mslib {
namespace render {
class BaseMaterial {
public:
	// コンストラクタ・デストラクタ
	BaseMaterial() = default;
	~BaseMaterial() = default;

	// GPU送信
	virtual void Send() = 0;
	// ロード
	virtual void Load(std::string _fileName) = 0;

	// 実際のMaterialのデータ
	MaterialData materialData;
};
}
}

