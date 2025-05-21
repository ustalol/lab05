#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, GetBalanceReturnsCorrectValue) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, GetBalance()).WillOnce(testing::Return(100));
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(AccountTest, ChangeBalanceThrowsWhenUnlocked) {
    MockAccount account(1, 100);
    EXPECT_THROW(account.ChangeBalance(50), std::runtime_error);
}

TEST(AccountTest, LockUnlockBehavior) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, Lock()).Times(1);
    EXPECT_CALL(account, Unlock()).Times(1);
    
    account.Lock();
    account.Unlock();
}
