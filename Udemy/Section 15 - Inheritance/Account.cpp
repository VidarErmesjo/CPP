#include <iostream>
#include "Account.h"

Account::Account(std::string name, double balance)
    : name{name}, balance{balance}
{
}

Account::~Account()
{
}

bool Account::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
        std::cout << "You deposited: " << amount << std::endl;
        return true;
    }
    else
        return false;
}

bool Account::withdraw(double amount)
{
    if (balance - amount >= 0)
    {
        balance -= amount;
        std::cout << "You withdrew: " << amount << std::endl;
        return true;
    }
    else
    {
        std::cout << "Insufficient funds for amount of: " << amount << " Your balance: " << balance << std::endl;
        return false;
    }
}

std::ostream &operator<<(std::ostream &output, const Account &account)
{
    return output << "Account balance: " << account.balance;
}