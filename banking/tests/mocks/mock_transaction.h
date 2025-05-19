#pragma once

#include "../transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
   
    MockTransaction() : Transaction() {}
    
   
    virtual ~MockTransaction() = default;
    
  
    MOCK_METHOD(bool, Make, (Account& from, Account& to, int sum), (override));
    
  
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));

    MOCK_METHOD(int, fee, (), (const));
    MOCK_METHOD(void, set_fee, (int fee));
    
    MOCK_METHOD(void, CreditMock, (Account& account, int sum));
    MOCK_METHOD(bool, DebitMock, (Account& account, int sum));
    

private:
    void Credit(Account& account, int sum) override {
        CreditMock(account, sum);
    }
    
    bool Debit(Account& account, int sum) override {
        return DebitMock(account, sum);
    }
};
