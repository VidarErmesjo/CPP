#pragma once
#include <iostream>
#include <string>

class Account
{
    friend std::ostream &operator<<(std::ostream &output, const Account &account);

private:
    static constexpr const char *default_name = "Unnamed Account";
    static constexpr double default_balance = 0.0;

protected:
    std::string name;
    double balance;

public:
    Account(std::string name = default_name, double balance = default_balance);
    ~Account();

    bool deposit(double amount);
    bool withdraw(double amount);

    double get_balance() const { return balance; }
};