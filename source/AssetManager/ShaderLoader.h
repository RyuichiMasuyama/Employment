#pragma once
#include <Singleton.h>
#include <unordered_map>

namespace mslib {
namespace assets {



class AssetsManager :public  pattern::Singleton<AssetsManager> {
public:

private:
	std::unordered_map<>m_textures;

};

}
}