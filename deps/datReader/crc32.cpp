#include "crc32.h"

#include <mutex>
#include <vector>

#include <zlib/zlib.h>

namespace internal
{
    // Mutex to prevent two threads from concurrently trying to build the crc tables atthe same time
    std::mutex crc_creation_mutex;

    typedef std::vector<uint32_t> CrcTable;
    
    // Our crc/rev_crc tables
    CrcTable crc_table;
    CrcTable rev_crc_table;

    bool crc_tables_created = false;

    void build_crc_tables()
    {
        std::lock_guard<std::mutex> lock(crc_creation_mutex);
        if (!crc_tables_created)
        {
            crc_table.resize(0x100);
            rev_crc_table.resize(0x100);
            for (auto i = 0; i < 0x100; ++i)
            {
                uint32_t crc = i;
                for (auto j = 0; j < 8; ++j)
                {
                    if (crc & 1)
                    {
                        crc = 0xEDB88320 ^ (crc >> 1);
                    }
                    else
                    {
                        crc = crc >> 1;
                    }
                }
                crc_table[i] = crc;
                rev_crc_table[crc >> 24] = i + ((crc & 0xFFFFFF) << 8);
            }
        }
        crc_tables_created = true;
    }

    const CrcTable& get_crc_table()
    {
        if (!crc_tables_created)
        {
            build_crc_tables();
        }
        return crc_table;
    }

    const CrcTable& get_rev_crc_table()
    {
        if (!crc_tables_created)
        {
            build_crc_tables();
        }
        return rev_crc_table;
    }
}

namespace xiv
{
namespace utils
{
namespace crc32
{

uint32_t compute(const std::string& i_input, uint32_t init_crc)
{
    // Classical crc stuff
	auto& crc_table = internal::get_crc_table();
    auto crc = init_crc;
    for(std::size_t i = 0; i < i_input.size(); ++i)
    {
        crc = crc_table[(crc ^ i_input[i]) & 0xFF] ^ (crc >> 8);
    }
    return crc;
}

uint32_t rev_compute(const std::string& i_input, uint32_t init_crc)
{
	auto& rev_crc_table = internal::get_rev_crc_table();
    auto crc = init_crc;
    const auto input_size = i_input.size();
    // Reverse crc
    for(auto i = input_size; i > 0; --i)
    {
       crc = rev_crc_table[crc >> 24] ^ ((crc << 8) & 0xFFFFFF00) ^ i_input[input_size - i - 1];
    }
    // Compute the 4 bytes needed for this init_crc
    for (auto i = 0; i < 4; ++i)
    {
        crc = rev_crc_table[crc >> 24] ^ ((crc << 8) & 0xFFFFFF00);
    }
    return crc;
}

void generate_hashes_1(std::string& i_format, const uint32_t i_first_index, std::vector<uint32_t>& o_hashes)
{
	char* str = const_cast<char*>(i_format.data());
	const uint32_t str_size = i_format.size();

	o_hashes.resize(10000);

	uint32_t i = 0;
	for (char a = '0'; a <= '9'; ++a)
	{
		str[i_first_index] = a;
		for (char b = '0'; b <= '9'; ++b)
		{
			str[i_first_index + 1] = b;
			for (char c = '0'; c <= '9'; ++c)
			{
				str[i_first_index + 2] = c;
				for (char d = '0'; d <= '9'; ++d)
				{
					str[i_first_index + 3] = d;
					o_hashes[i] = ::crc32(0, reinterpret_cast<uint8_t*>(&(str[0])), str_size) ^ 0xFFFFFFFF;
					++i;
				}
			}
		}
	}
}

void generate_hashes_2(std::string& i_format, const uint32_t i_first_index, const uint32_t i_second_index, std::vector<uint32_t>& o_hashes)
{
	char* str = const_cast<char*>(i_format.data());
	const uint32_t str_size = i_format.size();

	o_hashes.resize(100000000);

	uint32_t i = 0;
	for (char a = '0'; a <= '9'; ++a)
	{
		str[i_first_index] = a;
		for (char b = '0'; b <= '9'; ++b)
		{
			str[i_first_index + 1] = b;
			for (char c = '0'; c <= '9'; ++c)
			{
				str[i_first_index + 2] = c;
				for (char d = '0'; d <= '9'; ++d)
				{
					str[i_first_index + 3] = d;
					for (char e = '0'; e <= '9'; ++e)
					{
						str[i_second_index] = e;
						for (char f = '0'; f <= '9'; ++f)
						{
							str[i_second_index + 1] = f;
							for (char g = '0'; g <= '9'; ++g)
							{
								str[i_second_index + 2] = g;
								for (char h = '0'; h <= '9'; ++h)
								{
									str[i_second_index + 3] = h;
									o_hashes[i] = ::crc32(0, reinterpret_cast<uint8_t*>(&(str[0])), str_size) ^ 0xFFFFFFFF;
									++i;
								}
							}
						}
					}
				}
			}
		}
	}
}


}
}
}
