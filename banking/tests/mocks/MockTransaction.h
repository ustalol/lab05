#include <gtest/gtest.h>
#include "../../Transaction.h"
#include "mocks/MockAccount.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class TransactionTest : public ::testing::Test {
protected:
    NiceMock<MockAccount> acc1{1, 1000};
    NiceMock<MockAccount> acc2{2, 500};
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
    EXPECT_CALL(acc1, ChangeBalance(-101)).Times(1).WillOnce(Return());
    
   
    EXPECT_CALL(acc2, ChangeBalance(100)).Times(1).WillOnce(Return());
    
   
    EXPECT_CALL(acc1, Unlock()).Times(1);
    EXPECT_CALL(acc2, Unlock()).Times(1);

    EXPECT_TRUE(tr.Make(acc1, acc2, 100));
}

TEST_F(TransactionTest, FeeAffectsTransaction) {
    tr.set_fee(10);
    
    EXPECT_CALL(acc1, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(acc1, ChangeBalance(-110)).Times(1).WillOnce(Return());
    EXPECT_CALL(acc2, ChangeBalance(100)).Times(1).WillOnce(Return());
    
    EXPECT_TRUE(tr.Make(acc1, acc2, 100));
}

TEST_F(TransactionTest, FeeAffectsTransaction) {
    tr.set_fee(10);
    
    EXPECT_CALL(acc1, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(acc1, ChangeBalance(-110)).Times(1); // 100 + 10 комиссия
    EXPECT_CALL(acc2, ChangeBalance(100)).Times(1);
    
    EXPECT_TRUE(tr.Make(acc1, acc2, 100));
}
