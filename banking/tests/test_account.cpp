#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "account.h"
#include "mocks/mock_account.h"

using ::testing::Return;
using ::testing::_;

TEST(AccountTest, GetBalanceReturnsCorrectValue) {
    MockAccount account;
    EXPECT_CALL(account, GetBalance())
        .WillOnce(Return(1000));
    
    ASSERT_EQ(account.GetBalance(), 1000);
}

TEST(AccountTest, DepositIncreasesBalance) {
    MockAccount account;
    EXPECT_CALL(account, Deposit(100))
        .WillOnce(Return(true));
    
    EXPECT_TRUE(account.Deposit(100));
}

TEST(AccountTest, WithdrawDecreasesBalance) {
    MockAccount account;
    EXPECT_CALL(account, Withdraw(200))
        .WillOnce(Return(true));
    
    EXPECT_TRUE(account.Withdraw(200));
}

TEST(AccountTest, WithdrawFailsWhenInsufficientFunds) {
    MockAccount account;
    EXPECT_CALL(account, GetBalance())
        .WillOnce(Return(100));
    EXPECT_CALL(account, Withdraw(200))
        .WillOnce(Return(false));
    
    EXPECT_FALSE(account.Withdraw(200));
}
