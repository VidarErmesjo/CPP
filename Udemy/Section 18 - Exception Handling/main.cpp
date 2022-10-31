#include <iostream>
#include <memory>
#include <string>

class DivideByZeroException
{};

class NegativeValueException
{};

class IllegalBalanceException: public std::exception
{
public:
    IllegalBalanceException() noexcept = default;
    ~IllegalBalanceException() = default;
    virtual const char *what() const noexcept { return "IllegalBallanceException()"; }
};

class UnknownException
{};

class Account
{
private:
    std::string name;
    double balance;
public:
    Account(std::string name = "No name", double balance = 0.0)
        : name{name}, balance{balance}
    {
        if (this->balance < 0.0)
            throw IllegalBalanceException();

        std::cout << "Account constructor" << std::endl;
    };
    ~Account() { std::cout << "Account destructor" << std::endl; };
};

double calculate_average(int sum, int total)
{
    if (total == 0)
        throw DivideByZeroException();
    if (sum == 0)
        throw UnknownException();
    if (sum < 0 || total < 0)
        throw NegativeValueException();

    return static_cast<double>(sum) / total;
}

void calculate()
{
    int sum {}, total {};

    std::cout << "Enter sum: ";
    std::cin >> sum;
    std::cout << "Enter total: ";
    std::cin >> total;

    try
    {
        double average = calculate_average(sum, total);
        std::cout << "Average: " << average << std::endl;
    }
    catch (const DivideByZeroException &ex)
    {
        std::cerr << "DivideByZeroException()" << std::endl;
    }
    catch (const NegativeValueException &ex)
    {
        std::cerr << "NegativeValueException()" << std::endl;
    }
    catch (...)  // Catch all
    {
        std::cerr << "UnknownException()" << std::endl;
    }
}

int main()
{
    //calculate();

    double balance {};
    std::cout << "Enter balance: ";
    std::cin >> balance;

    try
    {
        auto account = std::make_unique<Account>("Some account", balance);
    }
    catch(const IllegalBalanceException &ex)
    {
        std::cerr << ex.what() << std::endl;
    }    

    std::cout << "Bye!" << std::endl;

    return 0;
}