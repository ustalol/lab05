#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "transaction.h"
#include "mocks/mock_account.h"

using ::testing::Return;
using ::testing::_;

TEST(TransactionTest, ExecuteTransfersFunds) {
    MockAccount from, to;
    
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000));
    EXPECT_CALL(from, Withdraw(500))
        .WillOnce(Return(true));
    EXPECT_CALL(to, Deposit(500))
        .WillOnce(Return(true));
    
    Transaction transaction(500);
    EXPECT_TRUE(transaction.Execute(from, to));
}

TEST(TransactionTest, ExecuteFailsWhenInsufficientFunds) {
    MockAccount from, to;
    
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(300));
    EXPECT_CALL(from, Withdraw(500))
        .WillOnce(Return(false));
    
    Transaction transaction(500);
    EXPECT_FALSE(transaction.Execute(from, to));
}
