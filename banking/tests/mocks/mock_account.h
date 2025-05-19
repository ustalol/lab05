#pragma once
#include "account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MOCK_METHOD(double, GetBalance, (), (override));
    MOCK_METHOD(bool, Deposit, (double amount), (override));
    MOCK_METHOD(bool, Withdraw, (double amount), (override));
};
