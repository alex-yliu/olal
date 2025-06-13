#include "base58.hpp"

namespace olal
{

    static const char *BASE58_ALPHABET = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

    std::string Base58::encode(const std::vector<uint8_t> &input)
    {
        std::vector<uint8_t> digits;
        digits.reserve(input.size() * 2);

        for (auto byte : input)
        {
            int carry = byte;
            for (size_t j = 0; j < digits.size(); ++j)
            {
                carry += digits[j] << 8;
                digits[j] = carry % 58;
                carry /= 58;
            }
            while (carry)
            {
                digits.push_back(carry % 58);
                carry /= 58;
            }
        }

        std::string result;
        for (auto byte : input)
        {
            if (byte == 0)
                result += BASE58_ALPHABET[0];
            else
                break;
        }

        for (auto it = digits.rbegin(); it != digits.rend(); ++it)
        {
            result += BASE58_ALPHABET[*it];
        }

        return result;
    }

} // namespace olal
