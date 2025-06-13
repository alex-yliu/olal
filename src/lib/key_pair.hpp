
#pragma once
#include <string>
#include <vector>

namespace olal
{
    enum class KeyType
    {
        ED25519,
        DILITHIUM2
        // Add more in future (e.g., Falcon, Kyber, etc.)
    };

    class KeyPair
    {
    public:
        virtual ~KeyPair() = default;

        virtual std::vector<uint8_t> sign(const std::vector<uint8_t> &message) const = 0;
        virtual bool verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const = 0;

        virtual std::vector<unsigned char> getPublicKey() const = 0;
        virtual std::vector<unsigned char> getPrivateKey() const = 0;

        virtual std::string getPublicKeyBase58() const = 0;
        virtual std::string getPrivateKeyBase58() const = 0;
    };

} // namespace olal
