#include "key_pair_ed25519.hpp"
#include "base58.hpp"
#include <stdexcept>
#include <sodium/utils.h>

namespace olal
{

    KeyPairEd25519::KeyPairEd25519()
    {
        publicKey_.resize(crypto_sign_PUBLICKEYBYTES);
        privateKey_.resize(crypto_sign_SECRETKEYBYTES);

        if (crypto_sign_keypair(publicKey_.data(), privateKey_.data()) != 0)
        {
            throw std::runtime_error("Failed to generate Ed25519 keypair");
        }
    }

    KeyPairEd25519::KeyPairEd25519(const std::vector<uint8_t> &pub, const std::vector<uint8_t> &priv)
        : publicKey_(pub), privateKey_(priv)
    {
        if (pub.size() != crypto_sign_PUBLICKEYBYTES || priv.size() != crypto_sign_SECRETKEYBYTES)
        {
            throw std::invalid_argument("Invalid key size for Ed25519");
        }
    }

    std::vector<uint8_t> KeyPairEd25519::sign(const std::vector<uint8_t> &message) const
    {
        std::vector<uint8_t> signature(crypto_sign_BYTES);
        unsigned long long sigLen;

        if (crypto_sign_detached(signature.data(), &sigLen, message.data(), message.size(), privateKey_.data()) != 0)
        {
            throw std::runtime_error("Ed25519 signing failed");
        }

        return signature;
    }

    bool KeyPairEd25519::verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const
    {
        if (signature.size() != crypto_sign_BYTES)
            return false;

        return crypto_sign_verify_detached(signature.data(), message.data(), message.size(), publicKey_.data()) == 0;
    }

    std::vector<uint8_t> KeyPairEd25519::getPublicKey() const
    {
        return publicKey_;
    }

    std::vector<uint8_t> KeyPairEd25519::getPrivateKey() const
    {
        return privateKey_;
    }

    std::string KeyPairEd25519::getPublicKeyBase58() const
    {
        return Base58::encode(publicKey_);
    }

    std::string KeyPairEd25519::getPrivateKeyBase58() const
    {
        return Base58::encode(privateKey_);
    }

} // namespace olal
