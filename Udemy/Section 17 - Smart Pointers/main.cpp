#include <iostream>
#include <memory>
#include <vector>

#include "IPrintable.h"

class Test: public IPrintable
{
private:
    int data;
public:
    Test(): Test{0} {}
    Test(int data): data{data} { std::cout << "\tTest constructor(" << data << ")" << std::endl; }
    virtual ~Test() { std::cout << "\tTest destructor(" << data << ")" << std::endl; }

    int get_data() const { return data; }
    void set_data(const int &data) { this->data = data; }
    virtual void print(std::ostream &os) const override { os << "Data: " << data; }
};

// Weak pointers
class B;

class A
{
private:
    std::shared_ptr<B> b_ptr;
public:
    A() { std::cout << "A constructor" << std::endl; }
    ~A() { std::cout << "A destructor" << std::endl; }

    void set_b(std::shared_ptr<B> &b) { b_ptr = b; }
};

class B
{
private:
    std::weak_ptr<A> a_ptr; // Change to std::weak_ptr (from std::shared_pointer) to avoid circular reference
public:
    B() { std::cout << "B constructor" << std::endl; }
    ~B() { std::cout << "B destructor" << std::endl; }

    void set_a(std::shared_ptr<A> &a) { a_ptr = a; }
};

// Custom deleter
void deleter_function(Test *raw_ptr)
{
    std::cout << "Using my custom deleter function" << std::endl;
    delete raw_ptr;
}

// Helper
void new_line(int n = 1) { for (int i{0}; i < n; ++i) std::cout << std::endl; }

// SECTION CHALLENGE
auto make() // std::unique_ptr<std::vector<std::shared_ptr<Test>>>
{
    return std::make_unique<std::vector<std::shared_ptr<Test>>>();
}

void fill(std::vector<std::shared_ptr<Test>> &vector, int num)
{
    for (int i {0}; i < num; ++i)
    {
        int in;
        std::cout << "Enter data point [" << i + 1 << "] : ";
        std::cin >> in;
        vector.push_back(std::make_shared<Test>(in));   // r-value semantics (move)
    }
    std::cout << std::endl;
}

void display(const std::vector<std::shared_ptr<Test>> &vector)
{
    std::cout << "Displaying vector data" << std::endl;
    std::cout << "=======================" << std::endl;

    for (const auto &data : vector)
        std::cout << *data << std::endl;

    std::cout << "=======================" << std::endl;
}

int main()
{
    {
        std::cout << "=== Stack allocated object" << std::endl;
        Test test{1000};
        test.set_data(100);
        std::cout << test << std::endl;
    }
    new_line(1);

    {
        std::cout << "=== Raw pointer" << std::endl;
        Test *test = new Test{100};
        test->set_data(1000);
        std::cout << *test << std::endl;
        delete test;
    }
    new_line(1);

    {
        std::cout << "=== Unique pointer (using 'new' - pre C++14)" << std::endl;
        std::unique_ptr<Test> test {new Test{666}};
        test->set_data(999);
        std::cout << *test << std::endl;
    }
    new_line(1);

    {
        std::cout << "=== Unique pointer (C++14)" << std::endl;
        auto test = std::make_unique<Test>(999);
        test->set_data(666);
        std::cout << *test << std::endl;

        std::unique_ptr<Test> other;

        other = std::move(test);

        if (!test)
            std::cout << "test is nullptr" << std::endl;

        other->set_data(100);
        std::cout << *other << std::endl;
    }
    new_line(1);

    {
        std::cout << "Vector" << std::endl;
        std::vector<std::unique_ptr<Test>> vector;
        vector.push_back(std::make_unique<Test>(1));
        vector.push_back(std::make_unique<Test>(2));
        vector.push_back(std::make_unique<Test>(3));

        for (const auto &element : vector)
            std::cout << *element << std::endl;
    }
    new_line(1);

    {
        std::cout << "=== Shared pointer" << std::endl;
        {
            std::shared_ptr<int> p1 {new int {100}};
            std::cout << p1.use_count() << std::endl;
            std::shared_ptr<int> p2 {p1};
            std::cout << p1.use_count() << std::endl;
            {
                std::shared_ptr<int> p3 {p1};
                std::cout << p1.use_count() << std::endl;
                *p3 = 200;
            }
            std::cout << p1.use_count() << std::endl;
            p1.reset();
            std::cout << p2.use_count() << std::endl;
            std::cout << *p2 << std::endl;

            new_line(1);
            std::vector<std::shared_ptr<int>> vector;
            std::shared_ptr<int> ptr {new int{666}};
            vector.push_back(ptr);
            std::cout << ptr.use_count() << std::endl;  // 2 - ptr has been copied
        }
        new_line(1);

        // Most efficient!
        auto p1 = std::make_shared<int>(100);
        auto p2 {p1};
        std::shared_ptr<int> p3;
        p3 = p1;
        *p3 = 666;

        // All pointers point to the same heap object
        std::cout << "use_count: "<< p1.use_count() << ", p1: " << *p1 << ", p2: " << *p2 << ", p3: " << *p3 << std::endl;
        
        new_line(1);
        std::cout << "Vector" << std::endl;

        std::vector<std::shared_ptr<Test>> vector;
        auto external_ptr = std::make_shared<Test>(111);
        vector.push_back(external_ptr);
        vector.push_back(std::make_shared<Test>(333));
        vector.push_back(std::make_shared<Test>(666));
        vector.push_back(std::make_shared<Test>(999));
        vector.push_back(vector.at(2));

        for (const auto &element : vector)
            std::cout << "data: " << *element << ", use_count: " << element.use_count() << std::endl;
    }
    new_line();

    {
        std::cout << "=== Weak pointer" << std::endl;
        // BEWARE! This will cause a memory leak without using a std::weak_ptr!!!
        auto a = std::make_shared<A>();
        auto b = std::make_shared<B>();
        a->set_b(b);
        b->set_a(a);
    }
    new_line();

    {
        std::cout << "=== Custom deleters" << std::endl;
        {
            // Using custom deleter function
            std::shared_ptr<Test> ptr {new Test{333}, deleter_function};
        }
        {
            // ... or using Lambda
            std::shared_ptr<Test> ptr {new Test{666},
                [] (Test *ptr)
                {
                    std::cout << "Using my custom Lambda deleter function" << std::endl;
                    delete ptr;
                }};
        }
        new_line();
    }
    new_line();
    std::cout << "=== SECTION CHALLENGE ===" << std::endl;

    std::unique_ptr<std::vector<std::shared_ptr<Test>>> vector_ptr;
    vector_ptr = make();
    std::cout << "How may data points do you want to enter? ";
    int num;
    std::cin >> num;
    fill(*vector_ptr, num);
    display(*vector_ptr);

    return 0;
}