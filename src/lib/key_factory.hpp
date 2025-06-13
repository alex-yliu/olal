#pragma once
#include "key_pair_ed25519.hpp"
#include "key_pair_dilithium.hpp"
#include <memory>

namespace olal
{

    class KeyFactory
    {
    public:
        static std::shared_ptr<KeyPair> createKeyPair(KeyType type);
    };

}
