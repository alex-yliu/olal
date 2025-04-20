#pragma once
#include "key_pair.hpp"
#include <sodium.h>
#include <array>

namespace olal
{

    class KeyPairEd25519 : public KeyPair
    {
    public:
        KeyPairEd25519(); // generate
        KeyPairEd25519(const std::vector<uint8_t> &priv);

        std::string getPublicKeyBase58() const override;
        std::vector<uint8_t> getRawPublicKey() const override;

        std::vector<uint8_t> sign(const std::string &message) const override;
        bool verify(const std::string &message, const std::vector<uint8_t> &signature) const override;

        std::string getKeyType() const override { return "ED25519"; }

    private:
        std::array<uint8_t, crypto_sign_PUBLICKEYBYTES> pubKey;
        std::array<uint8_t, crypto_sign_SECRETKEYBYTES> privKey;
    };

} // namespace olal
