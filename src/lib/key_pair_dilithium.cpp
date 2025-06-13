#include "key_pair_dilithium.hpp"
#include <stdexcept>
#include <cstring>
#include <sodium/utils.h> // Optional if you want to wipe secrets securely
#include "base58.hpp"     // Assuming you have a base58 utility

namespace olal
{

    KeyPairDilithium::KeyPairDilithium() : sigAlg(OQS_SIG_new(OQS_SIG_alg_dilithium_2))
    {
        if (!sigAlg)
        {
            throw std::runtime_error("Failed to initialize Dilithium2 signature algorithm");
        }

        publicKey_.resize(sigAlg->length_public_key);
        privateKey_.resize(sigAlg->length_secret_key);

        if (OQS_SIG_keypair(sigAlg.get(), publicKey_.data(), privateKey_.data()) != OQS_SUCCESS)
        {
            throw std::runtime_error("Failed to generate Dilithium keypair");
        }
    }

    KeyPairDilithium::KeyPairDilithium(const std::vector<uint8_t> &pub, const std::vector<uint8_t> &priv)
        : publicKey_(pub), privateKey_(priv)
    {
        sigAlg.reset(OQS_SIG_new(OQS_SIG_alg_dilithium_2));
        if (!sigAlg)
        {
            throw std::runtime_error("Failed to initialize Dilithium2 signature algorithm");
        }
        if (publicKey_.size() != sigAlg->length_public_key || privateKey_.size() != sigAlg->length_secret_key)
        {
            throw std::invalid_argument("Invalid key size");
        }
    }

    KeyPairDilithium::~KeyPairDilithium()
    {
        sodium_memzero(privateKey_.data(), privateKey_.size());
    }

    std::vector<uint8_t> KeyPairDilithium::sign(const std::vector<uint8_t> &message) const
    {
        std::vector<uint8_t> signature(sigAlg->length_signature);
        size_t signatureLen = 0;

        if (OQS_SIG_sign(sigAlg.get(),
                         signature.data(), &signatureLen,
                         message.data(), message.size(),
                         privateKey_.data()) != OQS_SUCCESS)
        {
            throw std::runtime_error("Signing failed");
        }

        signature.resize(signatureLen);
        return signature;
    }

    bool KeyPairDilithium::verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const
    {
        return OQS_SIG_verify(sigAlg.get(),
                              message.data(), message.size(),
                              signature.data(), signature.size(),
                              publicKey_.data()) == OQS_SUCCESS;
    }

    std::vector<uint8_t> KeyPairDilithium::getPublicKey() const
    {
        return publicKey_;
    }

    std::vector<uint8_t> KeyPairDilithium::getPrivateKey() const
    {
        return privateKey_;
    }

    std::string KeyPairDilithium::getPublicKeyBase58() const
    {
        return Base58::encode(publicKey_);
    }
    std::string KeyPairDilithium::getPrivateKeyBase58() const
    {
        return Base58::encode(privateKey_);
    }

} // namespace olal
