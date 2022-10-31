#include <iostream>
#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(std::string name, double balance, double interest_rate)
    : Account{name, balance}, interest_rate{interest_rate}
{
}

SavingsAccount::~SavingsAccount()
{
}

bool SavingsAccount::deposit(double amount)
{
    amount += interest_rate / 100;
    return Account::deposit(amount);
}

std::ostream &operator<<(std::ostream &output, const SavingsAccount &account)
{
    return output << "Savings Account balance: " << account.balance << " Interest rate: " << account.interest_rate << "%";
}
