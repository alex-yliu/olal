#pragma once

#include <memory>
#include <vector>
#include <string>
#include "key_pair.hpp"
#include "tx.hpp"

namespace olal
{

    class Account
    {
    public:
        Account(std::shared_ptr<KeyPair> mainKeyPair);

        std::shared_ptr<KeyPair> getMainKeyPair() const;

        // Delegate key management
        void addDelegateKey(std::shared_ptr<KeyPair> delegate);
        bool hasDelegateKey(const std::string &publicKeyBase58) const;
        std::vector<std::shared_ptr<KeyPair>> getDelegateKeys() const;

        // Transaction ledgers
        void addReceivedTransaction(const Transaction &tx);
        void addSpendingTransaction(const Transaction &tx);

        const std::vector<Transaction> &getReceivingLedger() const;
        const std::vector<Transaction> &getSpendingLedger() const;

    private:
        std::shared_ptr<KeyPair> mainKey;
        std::vector<std::shared_ptr<KeyPair>> delegateKeys;

        std::vector<Transaction> receivingLedger;
        std::vector<Transaction> spendingLedger;
    };

} // namespace olal
