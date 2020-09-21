#pragma once
#include "utils/hash.h"

namespace DeNgine {
namespace utils {

struct HashedString
{
    const std::uint32_t length;
    const std::uint32_t hashed;
    constexpr HashedString(std::string_view p_str)
        :length(p_str.length()),
         hashed(hash(p_str.data(), length))
    {}
    constexpr HashedString(const char* p_str)
        :length(std::char_traits<char>::length(p_str)),
         hashed(hash(p_str, length))
    {}
};

inline constexpr bool operator==(const HashedString& a, const HashedString& b)
{
    //Additional length check for better accuracy
    return (a.hashed == b.hashed) && (a.length == b.length);
}

inline constexpr bool operator!=(const HashedString& a, const HashedString& b)
{
    return !(a == b);
}

} // namespace utils
} // namespace DeNgine

namespace std {
template<>
class hash<DeNgine::utils::HashedString>
{
public:
    constexpr std::size_t operator()(const DeNgine::utils::HashedString &s) const
    { return s.hashed; }
};
} // namespace ::std
