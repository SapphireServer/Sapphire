#include "zlib.h"
#include <string>
#include <stdexcept>
#include <zlib/zlib.h>
#include <vector>

namespace xiv
{
namespace utils
{
namespace zlib
{

void compress(const std::vector<char>& in, std::vector<char>& out)
{
    // Fetching upper bound for out size
    auto out_size = compressBound(in.size());
    out.resize(out_size);

    auto ret = compress2(reinterpret_cast<uint8_t*>(out.data()), &out_size,
                          reinterpret_cast<const uint8_t*>(in.data()), in.size(), Z_BEST_COMPRESSION);

    if (ret != Z_OK)
    {
        throw std::runtime_error("Error at zlib uncompress: " + std::to_string(ret));
    }

    out.resize(out_size);
}

void no_header_decompress(uint8_t* in, uint32_t in_size, uint8_t* out, uint32_t out_size)
{
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = in_size;
    strm.next_in = Z_NULL;

    // Init with -15 because we do not have header in this compressed data
    auto ret = inflateInit2(&strm, -15);
    if (ret != Z_OK)
    {
        throw std::runtime_error("Error at zlib init: " + std::to_string(ret));
    }

    // Set pointers to the right addresses
    strm.next_in = in;
    strm.avail_out = out_size;
    strm.next_out = out;

    // Effectively decompress data
    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_STREAM_END)
    {
        throw std::runtime_error("Error at zlib inflate: " + std::to_string(ret));
    }

    // Clean up
    inflateEnd(&strm);
}

}
}
}
