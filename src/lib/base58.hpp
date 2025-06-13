#pragma once
#include <string>
#include <vector>

namespace olal
{

    class Base58
    {
    public:
        static std::string encode(const std::vector<uint8_t> &input);
    };

} // namespace olal
