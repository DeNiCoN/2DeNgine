#pragma once
#include <string>

namespace DeNgine {
namespace utils {
constexpr std::uint32_t hash(const char * key, std::uint32_t len)
{
    const std::uint32_t m = 0x5bd1e995;
    const std::uint32_t seed = 0;
    const int r = 24;

    std::uint32_t h = seed ^ len;

    const auto * data = (const unsigned char *)key;
    std::uint32_t k = 0;

    while (len >= 4)
    {
        k = *((std::uint32_t*) data);

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

constexpr std::uint32_t hash(const char *key) {
  std::uint32_t len = std::char_traits<char>::length(key);
  return hash(key, len);
}
} // namespace utils
} // namespace DeNgine
