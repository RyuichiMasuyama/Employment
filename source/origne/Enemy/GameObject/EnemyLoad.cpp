#include "EnemyLoad.h"

#include <filesystem>
#include <array>
#include <fstream>

#define CHAR_PTR_CAST(t) reinterpret_cast<char*>(&t)

using fi = std::ifstream;

namespace fs = std::experimental::filesystem;

namespace mslib {
namespace loader {
}
}