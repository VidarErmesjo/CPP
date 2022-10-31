#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>

// Displayer function object
template <typename T>
struct Displayer { void operator() (const T &data) { std::cout << data << " "; }};

// Old style function object
template <typename T>
class Multiplier
{
private:
    T number {};

public:
    Multiplier(T number) : number{number} {}
    T operator() (const T &number) const { return this->number * number; }

    void operator= (const T &number) { this->number = number; }
    void operator+= (const T &number) { this->number += number; }
    void operator-= (const T &number) { this->number -= number; }
    void operator*= (const T &number) { this->number *= number; }
    void operator/= (const T &number) { this->number /= number; }
    void operator%= (const T &number) { this->number %= number; }

    // Capture ALL within object
    void Test() { [this]() { std::cout << "Multiplier.Test(): " << number << std::endl; }(); }
};

template <typename T>
void display(const std::vector<T> &vector, const std::string &header = "")
{
    if (!header.empty())
        std::cout << header;

    std::cout << "[ ";
    for (const auto &element : vector) { std::cout << element << " "; }
    std::cout << "]" << std::endl;
}

void old_style()
{
    std::vector<int> vector(20); // {1, 2, 3, 4};
    std::iota(vector.begin(), vector.end(), 1);

    Multiplier multiplier {10}; // Requires Multiplier object
    multiplier = 20;
    multiplier.Test();

    std::cout << "=== Using Function object (functor) ===" << std::endl;
    display(vector, "Before std::transform:\n");
    std::transform(vector.begin(), vector.end(), vector.begin(), multiplier);
    std::cout << std::endl;

    // ... or simply
    std::transform(vector.begin(), vector.end(), vector.begin(), Multiplier(6.66));

    // ... this time around using the Displayer function object
    std::cout << "After std::transform: (displayed using function object)" << std::endl << "[ ";
    std::for_each(vector.begin(), vector.end(), Displayer<int>());
    std::cout << "]" << std::endl << std::endl;
}

void stateless_lambda_style()
{
    std::vector<int> vector(20);
    std::iota(vector.begin(), vector.end(), 1);

    std::cout << "=== Using lambda expression ===" << std::endl;
    display(vector, "Before std::transform:\n");
    std::cout << std::endl;
    std::transform(vector.begin(), vector.end(), vector.begin(), [](double number) { return number * 20; });

    // ... or simply
    auto lambda = [](double number) { return number * 6.66; };
    std::transform(vector.begin(), vector.end(), vector.begin(), lambda);

    // .. this time around using a lambda expression
    std::cout << "After std::transform: (displayed using lambda expression)" << std::endl << "[ ";
    std::for_each(vector.begin(), vector.end(), [](int &data) { std::cout << data << " "; });
    std::cout << "]" << std::endl << std::endl;
}

void stateful_lambda_style()
{
    std::cout << "==== Stateful Lambdas ====" << std::endl;

    int x {100};
    [x]() { std::cout << "Capture by value (const): " << x << std::endl; }();
    [x]() mutable { x += 100; std::cout << "Capture by value (mutable): " << x << std::endl; }();
    [&x]() { x += 566; std::cout << "Capture by reference: " << x << std::endl; }();

    // Catch all
    x = 100;
    int y {200};
    int z {300};
    [=]() { std::cout << "Capture ALL by value (const): " << x << " " << y << " " << z << std::endl; }();
    [&]() { x += 6; y += 30; z += 30; std::cout << "Capture ALL by reference: " << x + y + z << std::endl; }();

    std::cout << std::endl;
}

// Function with predicate parameter
void print_if(const std::vector<int> &numbers, bool (*predicate)(int))
{
    for (const auto &number : numbers)
        if (predicate(number))
            std::cout << number << " ";
}

void lambda_expressions_as_predicates()
{
    auto print = [](const auto &input) { std::cout << input; };

    std::vector<int> vector {1, 2, 3, 4, 5, 6, 7, 8, 9};

    print("Even: ");
    print_if(vector, [](auto x) { return x % 2 == 0; });
    print("\nOdd: ");
    print_if(vector, [](auto x) { return x % 2 != 0; });
    print("\n\n");
}

auto complicated_function()
{
    return [](int x) { return x * x; };
}

int main()
{
    auto lambda = [](const auto &input) { std::cout << input; };
    lambda("Hello Fellow C++ Programmers! "); lambda(666); lambda("\n");

    Displayer<std::string> displayer;
    displayer("Lambda Expression Syntax: [] () -> return_type specifier {};\n\n");

    old_style();
    stateless_lambda_style();
    stateful_lambda_style();
    lambda_expressions_as_predicates();

    // Some fun ;)
    auto message = [](const auto &message) { return message; };
    auto square = complicated_function();
    auto number = square(64);
    std::cout << message(number);

    return 0;
}