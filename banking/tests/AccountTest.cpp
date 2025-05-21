#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, ChangeBalanceCallsProxy) {
    MockAccount account(1, 100);
    
    EXPECT_CALL(account, ChangeBalanceProxy(50)).Times(1);
    
    account.Lock();
    account.ChangeBalance(50);
}

TEST(AccountTest, ChangeBalanceThrowsWhenUnlocked) {
    MockAccount account(1, 100);
    EXPECT_THROW(account.ChangeBalance(50), std::runtime_error);
}
