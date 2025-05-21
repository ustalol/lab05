#pragma once
#include "../../Account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}
    
    bool ChangeBalance(int diff) override {
        ChangeBalanceProxy(diff);
        return true;
    }
    
    MOCK_METHOD1(ChangeBalanceProxy, void(int));
    MOCK_CONST_METHOD0(GetBalance, int());
    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
};
