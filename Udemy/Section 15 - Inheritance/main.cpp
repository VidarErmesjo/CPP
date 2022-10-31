#include <iostream>
#include <vector>
#include "SavingsAccount.h"

class Base
{
public:
    // Note: Friends of Base hav access to all
    int a {0};

    Base(): value{0} { std::cout << "Base no-args constructor" << std::endl; }
    Base(int x): value{x} { std::cout << "Base (int) overloaded constructor" << std::endl; }
    Base(const Base &source): value{source.value} { std::cout << "Base copy constructor" << std::endl; }
    Base(Base &&source) { std::cout << "Base move constructor" << std::endl; }
    Base &operator=(const Base &rhs) { if (this != &rhs) value = rhs.value; return *this; }
    ~Base() { std::cout << "Base destructor" << std::endl; }
    int get_value() { return value; }
    void display() { std::cout << a << ", " << b << ", " << c << std::endl; }   // Member method has access to all
protected:
    int b {0};
private:
    int c {0};

    int value;
};

class Derived: public Base
{
    // Note: Friends of Derived only has access to what Derived has access to

    // a will be public
    // b will be protected
    // c will not be accessible
public:
    Derived(): doubled_value{0} { std::cout << "Derived no-args constructor" << std::endl; }
    Derived(int x): Base{x}, doubled_value{x*2} { std::cout << "Derived (int) overloaded constructor" << std::endl; }
    Derived(const Derived &source): Base{source}, doubled_value{source.doubled_value} { std::cout << "Derived copy constructor" << std::endl; }
    Derived(Derived &&source): Base(source) { std::cout << "Derived move constructor" << std::endl; }
    Derived &operator=(const Derived &rhs) { if (this != &rhs) { Base::operator=(rhs); doubled_value = rhs.doubled_value; } return * this; }
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
    int get_doubled_value() { return doubled_value; }
    void access_base_members()
    {
        a = 100;    // OK
        b = 200;    // OK
        //c = 300;    // Compiler error
    }

private:
    int doubled_value;
};

int main()
{
    {
        Base base {666};
        base.a = 100;   // OK
        //base.b = 200;   // Compiler error
        //base.c = 300;   // Compiler error
        base.display();
        std::cout << "Value: " << base.get_value() << std::endl;
    }

        std::cout << std::endl;
    {
        Derived derived {Derived{666}};
        derived.a = 100;    // OK
        //derived.b = 200;    // Compiler error
        //derived.c = 300;    // Compiler error
        derived.display();  // OK
        derived.access_base_members();
        derived.display();
        std::cout << "Value: " << derived.get_value() << ", Doubled value: " << derived.get_doubled_value() << std::endl;
    }

    {
        std::cout << std::endl;
        std::vector<Derived> vector;
        vector.push_back(Derived{333});
        vector.push_back(Derived{666});
    }

    std::cout << "==============================" << std::endl;

    Account account {};
    account.deposit(1000.0);
    account.withdraw(500.0);

    std::cout << account << std::endl;

    Account *p_account {nullptr};
    p_account = new Account();
    p_account->deposit(1000.0);
    p_account->withdraw(1500.0);
    delete p_account;

    std::cout << std::endl;

    SavingsAccount savings_account {"My Savings Account", 100.0, 5.0};
    savings_account.deposit(66.6);
    savings_account.withdraw(6.66);

    std::cout << savings_account << std::endl;

    SavingsAccount *p_savings_account {nullptr};
    p_savings_account = new SavingsAccount();
    p_savings_account->deposit(66.6);
    p_savings_account->withdraw(6.66);
    delete p_savings_account;

    return 0;
}