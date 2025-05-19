#pragma once

#include "../account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
 
    MockAccount(int id, int balance) : Account(id, balance) {}
    
 
    virtual ~MockAccount() = default;
    

    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    
    MOCK_METHOD(int, id, (), (const));
    
    void DelegateToReal() {
    
        ON_CALL(*this, GetBalance).WillByDefault([this]() {
            return Account::GetBalance();
        });
        ON_CALL(*this, ChangeBalance).WillByDefault([this](int diff) {
            Account::ChangeBalance(diff);
        });
    }
};
