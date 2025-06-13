#include "key_factory.hpp"
// #include "key_pair.hpp"

namespace olal
{

    std::shared_ptr<KeyPair> KeyFactory::createKeyPair(KeyType type)
    {
        switch (type)
        {
        case KeyType::ED25519:
            return std::make_shared<KeyPairEd25519>();
        case KeyType::DILITHIUM2:
            return std::make_shared<KeyPairDilithium>();
        default:
            throw std::runtime_error("Unsupported key type");
        }
    }

}
