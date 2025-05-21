#include "mocks/MockAccount.h"
#include "mocks/MockTransaction.h"
#include <gtest/gtest.h>

TEST(TransactionTest, MakeThrowsOnSameAccount) {
    MockAccount acc1(1, 100), acc2(1, 200);
    Transaction t;
    EXPECT_THROW(t.Make(acc1, acc2, 50), std::logic_error);
}

TEST(TransactionTest, MakeThrowsOnNegativeSum) {
    MockAccount acc1(1, 100), acc2(2, 200);
    Transaction t;
    EXPECT_THROW(t.Make(acc1, acc2, -50), std::invalid_argument);
}

TEST(TransactionTest, MakeReturnsFalseWhenFeeTooHigh) {
    MockAccount acc1(1, 100), acc2(2, 200);
    Transaction t;
    t.set_fee(60);
    EXPECT_FALSE(t.Make(acc1, acc2, 100));
}

TEST(TransactionTest, SaveToDataBaseIsCalled) {
    MockAccount acc1(1, 100), acc2(2, 200);
    MockTransaction t;
    
    EXPECT_CALL(t, SaveToDataBase(testing::_, testing::_, testing::_))
        .Times(1);
    
    t.Make(acc1, acc2, 150);
}
