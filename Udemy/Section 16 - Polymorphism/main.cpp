#include <iostream>
#include <vector>

class IPrintable
{
    friend std::ostream &operator<<(std::ostream &os, const IPrintable &obj);
public:
    //virtual ~IPrintable() {};
    virtual void print(std::ostream &os) const = 0;
};

std::ostream &operator<<(std::ostream &os, const IPrintable &obj)
{
    obj.print(os);
    return os;
}

class Account: public IPrintable
{
public:
    virtual ~Account() { std::cout << "Account destructor" << std::endl; }
    virtual void withdraw(double amount) { std::cout << "Accounts::withdraw" << std::endl; }
    //virtual void print() const final { std::cout << "I am immutable!" << std::endl ; }
    virtual void print(std::ostream &os) const override { os << "I am Account"; }
};

class Checking final: public Account
{
public:
    virtual ~Checking() { std::cout << "Checking destructor" << std::endl; }
    virtual void withdraw(double amount) override { std::cout << "Checking::withdraw" << std::endl; }
    // virtual void print() const {} // Compiler error
    virtual void print(std::ostream &os) const override { os << "I am Checking"; }
};

class Savings final: public Account
{
public:
    virtual ~Savings() { std::cout << "Savings destructor " << std::endl; }
    virtual void withdraw(double amount) override { std::cout << "Savings::withdraw" << std::endl; }
    virtual void print(std::ostream &os) const override { os << "I am Savings"; }
};

class Trust final: public Account
{
public:
    virtual ~Trust() { std::cout << "Trust destructor " << std::endl; }
    virtual void withdraw(double amount) override { std::cout << "Trust::withdraw" << std::endl; }
    virtual void print(std::ostream &os) const override { os << "I am Trust"; }
};

// Abstract ("interface") class
class Shape
{
private:
public:
    virtual ~Shape() { std::cout << "Shape destructor" << std::endl; };
    virtual void draw() = 0;
    virtual void rotate() = 0;
};

// Concrete class
class Circle: public Shape
{
private:
public:
    virtual ~Circle() { std::cout << "Circle destructor" << std::endl; };
    virtual void draw() override { std::cout << "Circle::draw" << std::endl; };
    virtual void rotate() override { std::cout << "Circle::rotate" << std::endl; }
};

// Base class reference
void do_withdraw(Account &account, double amount)
{
    account.withdraw(amount);
}

void print(const IPrintable &obj)
{
    std::cout << obj << std::endl;
}

int main()
{
    std::cout << "\n === Pointers ==== " << std::endl;
    Account *p1 = new Account();
    Account *p2 = new Checking();
    Account *p3 = new Savings();
    Account *p4 = new Trust();

    std::vector<Account *> accounts {p1, p2, p3, p4};

    for (const auto &account : accounts)
        account->withdraw(666);

    // IPrintable
    for (const auto &account : accounts)
        print(*account);

    std::cout << "\n === Clean up ==== " << std::endl;

    // WARNING:
    // Classes with virtual functions (like when implementing polymorphism)
    // must also have virtual destructors (virtual ~Class()) !!!
    delete p1;
    delete p2;
    delete p3;
    delete p4;

    std::cout << "\n === Base class reference ==== " << std::endl;
    {
        Account account;
        Account &ref = account;
        ref.withdraw(1000);
        do_withdraw(account, 1000);
        std::cout << ref;
    }
    {
        Trust trust;
        Account &ref = trust;
        ref.withdraw(1000);
        do_withdraw(trust, 1000);
        std::cout << ref;
    }

    std::cout << "\n === Abstract and concrete class ==== " << std::endl;
    // Abstract and concrete class
    //Shape shape; // Compiler error
    Shape *circle = new Circle();
    circle->draw();
    circle->rotate();
    
    delete circle;

    return 0;
}