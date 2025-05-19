#pragma once
#include "../Account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount() = default;
    MockAccount(int id, int balance) : Account(id, balance) {}
    
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    MOCK_METHOD(int, id, (), (const, override));
};
