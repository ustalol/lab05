#include <gtest/gtest.h>
#include "../Account.h"
#include "mocks/mock_account.h"

TEST(AccountTest, ConstructorInitializesValues) {
    Account acc(123, 1000);
    
    EXPECT_EQ(acc.id(), 123);
    EXPECT_EQ(acc.GetBalance(), 1000);
}

TEST(AccountTest, GetBalanceReturnsCorrectValue) {
    Account acc(1, 500);
    EXPECT_EQ(acc.GetBalance(), 500);
}

TEST(AccountTest, ChangeBalanceThrowsWhenUnlocked) {
    Account acc(1, 200);
    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
}

TEST(AccountTest, ChangeBalanceModifiesBalanceWhenLocked) {
    Account acc(1, 200);
    
    acc.Lock();
    acc.ChangeBalance(100);
    
    EXPECT_EQ(acc.GetBalance(), 300);
    
    acc.ChangeBalance(-50);
    EXPECT_EQ(acc.GetBalance(), 250);
    
    acc.Unlock();
    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
}

TEST(AccountTest, LockUnlockBehavior) {
    Account acc(1, 100);
    

    EXPECT_NO_THROW(acc.Lock());
    
    EXPECT_THROW(acc.Lock(), std::runtime_error);
    
    EXPECT_NO_THROW(acc.Unlock());
    

    EXPECT_NO_THROW(acc.Lock());
}

TEST(AccountTest, NegativeBalanceAllowed) {
    Account acc(1, 100);
    acc.Lock();
    
    acc.ChangeBalance(-150);
    EXPECT_EQ(acc.GetBalance(), -50);
}

TEST(AccountTest, SequenceOfOperations) {
    Account acc(1, 1000);
    

    acc.Lock();
    

    acc.ChangeBalance(-200);
    EXPECT_EQ(acc.GetBalance(), 800);
    
  
    acc.Unlock();
    

    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
    

    acc.Lock();
    acc.ChangeBalance(300);
    EXPECT_EQ(acc.GetBalance(), 1100);
}
