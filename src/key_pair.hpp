
#pragma once
#include <string>
#include <vector>

namespace olal
{

    class KeyPair
    {
    public:
        virtual ~KeyPair() = default;

        virtual std::string getPublicKeyBase58() const = 0;
        virtual std::vector<uint8_t> getRawPublicKey() const = 0;

        virtual std::vector<uint8_t> sign(const std::string &message) const = 0;
        virtual bool verify(const std::string &message, const std::vector<uint8_t> &signature) const = 0;

        virtual std::string getKeyType() const = 0;
    };

} // namespace olal
