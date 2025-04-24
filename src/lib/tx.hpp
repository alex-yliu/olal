#pragma once
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <sodium.h>

namespace olal
{

    class Transaction
    {
    public:
        Transaction(const std::string &senderPubKeyBase58,
                    const std::string &receiverPubKeyBase58,
                    uint64_t amount,
                    const std::string &memo = "");

        std::string getSender() const;
        std::string getReceiver() const;
        uint64_t getAmount() const;
        std::string getMemo() const;

        std::string getHash() const;
        void sign(const std::array<uint8_t, crypto_sign_SECRETKEYBYTES> &privKey);
        bool verifySignature() const;

        void setSignature(const std::array<uint8_t, crypto_sign_BYTES> &sig);
        std::array<uint8_t, crypto_sign_BYTES> getSignature() const;

    private:
        std::string sender;
        std::string receiver;
        uint64_t amount;
        std::string memo;

        std::array<uint8_t, crypto_sign_BYTES> signature{};

        std::string serialize() const;
    };

} // namespace olal
