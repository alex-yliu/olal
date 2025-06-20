#pragma once
#include "key_pair.hpp"
#include <sodium.h>
#include <array>

namespace olal
{

    class KeyPairEd25519 : public KeyPair
    {
    public:
        KeyPairEd25519();                                                                  // Generate new keypair
        KeyPairEd25519(const std::vector<uint8_t> &pub, const std::vector<uint8_t> &priv); // Load from data
        ~KeyPairEd25519() override = default;

        std::vector<uint8_t> sign(const std::vector<uint8_t> &message) const override;
        bool verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const override;

        std::vector<uint8_t> getPublicKey() const override;
        std::vector<uint8_t> getPrivateKey() const override;
        std::string getPublicKeyBase58() const override;
        std::string getPrivateKeyBase58() const override;

    private:
        std::vector<uint8_t> publicKey_;
        std::vector<uint8_t> privateKey_;
    };

} // namespace olal
