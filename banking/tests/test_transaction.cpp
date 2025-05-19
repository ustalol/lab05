#include <gtest/gtest.h>
#include "Transaction.h"
#include "mocks/mock_account.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class TransactionTest : public ::testing::Test {
protected:
    void SetUp() override {
        ON_CALL(acc1, id()).WillByDefault(Return(1));
        ON_CALL(acc2, id()).WillByDefault(Return(2));
    }

    NiceMock<MockAccount> acc1;
    NiceMock<MockAccount> acc2;
    Transaction tr;
};

TEST_F(TransactionTest, MakeThrowsWhenSameAccount) {
    EXPECT_THROW(tr.Make(acc1, acc1, 100), std::logic_error);
}

TEST_F(TransactionTest, MakeThrowsWhenNegativeSum) {
    EXPECT_THROW(tr.Make(acc1, acc2, -50), std::invalid_argument);
}

TEST_F(TransactionTest, MakeSuccessWhenEnoughBalance) {
 
    EXPECT_CALL(acc1, Lock()).Times(1);
    EXPECT_CALL(acc2, Lock()).Times(1);
    
    EXPECT_CALL(acc1, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(acc1, ChangeBalance(-101)).Times(1); // сумма + комиссия
    EXPECT_CALL(acc2, ChangeBalance(100)).Times(1);  // зачисление
    
    EXPECT_CALL(acc1, Unlock()).Times(1);
    EXPECT_CALL(acc2, Unlock()).Times(1);

    EXPECT_TRUE(tr.Make(acc1, acc2, 100));
}

TEST_F(TransactionTest, MakeFailsWhenNotEnoughBalance) {
    EXPECT_CALL(acc1, GetBalance()).WillOnce(Return(50));
    
    EXPECT_CALL(acc2, ChangeBalance(100)).Times(1);
    EXPECT_CALL(acc2, ChangeBalance(-100)).Times(1);
    EXPECT_FALSE(tr.Make(acc1, acc2, 100));
}

TEST_F(TransactionTest, FeeAffectsTransaction) {
    tr.set_fee(10);
    
    EXPECT_CALL(acc1, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(acc1, ChangeBalance(-110)).Times(1);
    EXPECT_CALL(acc2, ChangeBalance(100)).Times(1);
    
    EXPECT_TRUE(tr.Make(acc1, acc2, 100));
}
