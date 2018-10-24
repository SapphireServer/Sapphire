#ifndef XIV_UTILS_ZLIB_H
#define XIV_UTILS_ZLIB_H

#include <cstdint>
#include <vector>

namespace xiv
{
namespace utils
{
namespace zlib
{

void compress(const std::vector<char>& in, std::vector<char>& out);
void no_header_decompress(uint8_t* in, uint32_t in_size, uint8_t* out, uint32_t out_size);

}
}
}

#endif // XIV_UTILS_ZLIB_H
