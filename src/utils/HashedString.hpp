#pragma once

#include "utils/hash.h"

namespace DeNgine {
namespace utils {

struct HashedString
{
    const char* str;
    const unsigned int length;
    const unsigned int hashed;
    virtual ~HashedString() = default;
    constexpr HashedString(const char* c_str)
        :length(std::char_traits<char>::length(c_str)),
         hashed(hash(c_str, length)), str(c_str)
    {}


};

inline constexpr bool operator==(const HashedString& a, const HashedString& b)
{
    if (a.hashed != b.hashed || a.length != b.length)
        return false;
    for (int i = 0; i < a.length; ++i)
    {
        if(a.str[i] != b.str[i])
            return false;
    }
    return true;
}

} // namespace utils
} // namespace DeNgine

namespace std {
template<>
class hash<DeNgine::utils::HashedString>
{
public:
  constexpr size_t operator()(const DeNgine::utils::HashedString &s) const { return s.hashed; }
};
} // namespace ::std
