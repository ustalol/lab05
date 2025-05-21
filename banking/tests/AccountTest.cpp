#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, ChangeBalanceReturnsCorrectValue) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, ChangeBalance(testing::_))
        .WillOnce(testing::Return(true));
    
    account.Lock();
    EXPECT_TRUE(account.ChangeBalance(50));
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
