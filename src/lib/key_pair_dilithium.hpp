#pragma once

#include "key_pair.hpp"
#include <oqs/oqs.h>
#include <string>
#include <vector>
#include <memory>

namespace olal
{

    class KeyPairDilithium : public KeyPair
    {
    public:
        KeyPairDilithium();
        KeyPairDilithium(const std::vector<uint8_t> &publicKey, const std::vector<uint8_t> &privateKey);
        ~KeyPairDilithium();

        std::vector<uint8_t> sign(const std::vector<uint8_t> &message) const override;
        bool verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const override;

        std::vector<uint8_t> getPublicKey() const override;
        std::vector<uint8_t> getPrivateKey() const override;

        std::string getPublicKeyBase58() const override;
        std::string getPrivateKeyBase58() const override;

    private:
        std::unique_ptr<OQS_SIG> sigAlg;
        std::vector<uint8_t> publicKey_;
        std::vector<uint8_t> privateKey_;
    };

} // namespace olal
