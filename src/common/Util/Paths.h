#pragma once

#include <filesystem>

namespace Sapphire::Common::Util
{
  std::filesystem::path executablePath();
  std::filesystem::path executableDir();
}// namespace Sapphire::Common::Util
