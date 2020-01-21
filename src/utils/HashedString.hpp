#ifndef __HASHEDSTRING_H_
#define __HASHEDSTRING_H_
#include "utils/hash.h"

namespace DeNgine {
namespace utils {

struct HashedString
{
    const char* str;
    const std::uint32_t length;
    const std::uint32_t hashed;
    virtual ~HashedString() = default;
    constexpr HashedString(const char* c_str)
        :str(c_str), length(std::char_traits<char>::length(c_str)),
         hashed(hash(c_str, length))
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
  constexpr std::size_t operator()(const DeNgine::utils::HashedString &s) const { return s.hashed; }
};
} // namespace ::std
#endif
