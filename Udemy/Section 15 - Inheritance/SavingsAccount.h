#pragma once
#include "Account.h"

class SavingsAccount: public Account
{
    friend std::ostream &operator<<(std::ostream &output, const SavingsAccount &account);
private:
    static constexpr const char *default_name = "Unnamed Savings Account";
    static constexpr double default_balance = 0.0;
    static constexpr double default_rate = 0.0;

protected:
    double interest_rate;

public:
    SavingsAccount(std::string name = default_name, double balance = default_balance, double interest_rate = default_rate);
    ~SavingsAccount();

    bool deposit(double amount);
};