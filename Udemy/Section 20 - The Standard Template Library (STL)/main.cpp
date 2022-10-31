#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <tuple>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <deque>
#include <stack>
#include <queue>

#include "Array.h"

// Generic function
template <typename T>    // ... or template <class T>
T max(T &a, T &b)
{
    return (a > b) ? a : b;
}

// Generic class
template <typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
};

struct Person
{
    std::string name;
    int age;

    Person() = default;
    Person(std::string name, int age) : name {name}, age {age} {}

    bool operator>(const Person &rhs) const { return this->age > rhs.age; }
    bool operator<(const Person &rhs) const { return this->age < rhs.age; }
};

std::ostream &operator<<(std::ostream &os, const Person &obj)
{
    os << obj.name << ":" << obj.age;
    return os;
}

void algorithms()
{
    {
        std::vector<int> vector {1,5,3};
        std::sort(vector.begin(), vector.end());

        for (const auto &element : vector)
            std::cout << element << std::endl;

        int sum {};
        sum = std::accumulate(vector.begin(), vector.end(), 0);
        std::cout << sum << std::endl;
    }

    std::string string {"i was initialized as lower case. i am transformed."};
    // ::xxxxx <-- global scope
    std::transform(string.begin(), string.end(), string.begin(), ::toupper);
    std::cout << string << std::endl;
}

void templates()
{
    int a {10};
    int b {20};
    double c {666.0};
    double d {0.666};
    char e {'A'};
    char f {'C'};

    Person p1 {"Curly", 50};
    Person p2 {"Moe", 20};
    Person p3 = max(p1, p2);

    std::cout << max<int>(a, b) << std::endl;
    std::cout << max<double>(c, d) << std::endl;
    std::cout << max<char>(e, f) << std::endl;
    std::cout << p3 << std::endl;

    // Tuple test
    Pair<std::string, int> my_pair {"My little pair", 666};
    std::pair<std::string, int> pair {"Their little pair", 666};
    std::tuple<int, double, char> tuple {1, 1.666, 'A'};
    std::cout << my_pair.first << " " << my_pair.second << std::endl;
    std::cout << pair.first << " " << pair.second << std::endl;
}

void my_custom_array()
{
    {
        Array<int, 10> array {666};
        array[3] = 3;
        std::cout << array << std::endl;
    }
    {
        Array<std::string, 2> array {"Hello"};
        array[1] = std::string{"World"};    // Must be of type, not literal
        std::cout << array;
    }
}

template <typename T>
void display(const std::vector<T> &vector)
{
    std::cout << "[ ";
    std::for_each(vector.begin(), vector.end(), [](T element) { std::cout << element << " "; });
    std::cout << "]" << std::endl;
}

template <typename T>
void display(const std::deque<T> &deque)
{
    std::cout << "[ ";
    std::for_each(deque.begin(), deque.end(), [](T element) { std::cout << element << " "; });
    std::cout << "]" << std::endl;
}

template <typename T>
void display(const std::list<T> &list)
{
    std::cout << "[ ";
    std::for_each(list.begin(), list.end(), [](T element) { std::cout << element << " "; });
    std::cout << "]" << std::endl;
}

template <typename T>
void display(const std::set<T> &set)
{
    std::cout << "[ ";
    std::for_each(set.begin(), set.end(), [](T element) { std::cout << element << " "; });
    std::cout << "]" << std::endl;
}

template <typename K, typename V>
void display(const std::unordered_map<K, V> &map)
{
    std::cout << "[ ";
    std::for_each(map.cbegin(), map.cend(), [](std::pair<K, V> element) // Return type of map is a std::pair
    {
        std::cout << element.first << ":" << element.second << " ";
    });
    std::cout << "]" << std::endl;
}

// Stack
template <typename T>
void display(std::stack<T> stack)    // By value = copy
{
    while (!stack.empty())
    {
        T element = stack.top();
        stack.pop();
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void display(std::stack<T, std::vector<T>> stack)    // By value = copy
{
    while (!stack.empty())
    {
        T element = stack.top();
        stack.pop();
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Stack helper
template <typename T>
auto vector_stack(typename std::vector<T>::size_type capacity)
{
    std::vector<T> vector;
    vector.reserve(capacity);
    return std::stack<T, std::vector<T>>{std::move(vector)};
}

void containers()
{
    // Iterator example
    {
        std::vector<char> vector {'V', 'E', 'C', 'T', 'O', 'R'};
        std::vector<char>::const_iterator it = vector.cbegin(); // ..or auto it = vector.cbegin();
        while (it != vector.cend())
        {
            // *it = '#' // Compiler error --> const iterator!
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;

        for (auto it = vector.rbegin(); it != vector.rend(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;

        std::vector<Person> persons {Person{"Frank", 10}, Person{"Joe", 40}, Person{"Satan", 666}};
        for (auto it = persons.begin(); it != persons.end(); ++it)
            std::cout << it->name << " " << it->age << std::endl;

        // Use std::transform for this instead!
        std::set<std::string> set {"Hello", "World"};
        for (auto it = set.begin(); it != set.end(); ++it)
            for (auto &c : *it)
                std::cout << static_cast<char>(std::toupper(c));

        std::cout << std::endl;

        std::list<std::string> list {"Fretex", "Helsfyr", "Ensjø"};

        std::map<std::string, int> map {{"Fretex", 1}, {"Helsfyr", 2}, {"Ensjø", 3}};
        std::cout << map.find("Fretex")->second << std::endl;
    }

    {
        std::vector<Person> persons;

        persons.push_back(Person{"Larry", 25});
        persons.emplace_back("Moe", 50);        // Most efficient! Needs a constructor to be defined!

        std::cout << std::endl;

        for (const auto &person : persons)
            std::cout << person << std::endl;
    }

    // Back inserter
    {
        std::vector<int> vec1 {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vec2 {10, 20, 30, 40, 50};
        display(vec1);
        display(vec2);
        std::copy_if(vec1.begin(), vec1.end(), std::back_inserter(vec2), [](int x) { return x % 2 == 0; });
        display(vec2);

        std::vector<int> vec3;

        std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(vec3),
            [](int x, int y)
            {
                return x * y;
            });
        display(vec3);
    
        std::vector<Person> vec4 {Person{"Curly", 666}};
        std::vector<Person> vec5 {vec4};
        for(int i {0}; i < 4; ++i)
        {

            std::cout << i << ": ";
            display(vec4);
            std::copy(vec4.begin(), vec4.end(), std::back_inserter(vec5));
            vec4 = vec5;
        }
        
    }

    // Deque
    {
        std::deque<char> deque {'C'};
        std::cout << "    "; display(deque);
        deque.emplace_front('B');
        deque.emplace_back('D');
        std::cout << "  "; display(deque);
        deque.emplace_front('A');
        deque.emplace_back('E');
        display(deque);
    }

    // List
    {
        std::list<int> list {1, 2, 3, 4, 5};
        display(list);
        auto it = std::find(list.begin(), list.end(), 4);
        auto temp {it};
        --temp;
        std::cout << *it << std::endl;
        list.erase(it);
        it = temp;
        std::cout << *it << std::endl;
        display(list);
    }

    // Set
    {
        std::set<Person> persons {{"One", 1}, {"Three", 3}};
        display(persons);
        auto result = persons.insert({"Two", 2});
        display(persons);
        std::cout << std::boolalpha << *result.first << " " << result.second << std::endl;    // True
        result = persons.insert({"Two", 2});
        std::cout << std::boolalpha << *result.first << " " << result.second << std::endl;    // False (exists)

        std::cout << "Before: " << persons.size() << " ";
        persons.clear();
        std::cout << "After: " << persons.size() << std::endl;
    }

    // Maps
    {
        std::unordered_map<std::string, int> map {{"One", 1}, {"Two", 2}, {"Three", 3}, {"Four", 4}, {"Five", 5}};
        display(map);
    }

    // Stack (FILO)
    {
        {
            std::stack<char> stack; // Defaults to std::deque as underlying container
            std::string string {"REVERSE ME"};

            std::cout << std::endl << "Presenting... The All Mighty Stack!" << std::endl;
            std::for_each(string.cbegin(), string.cend(), [](char character) { std::cout << character << " "; });
            std::cout << std::endl;

            for (const auto &element : string)
                stack.push(element);

            display(stack);

            std::cout << "Size: " << stack.size() << std::endl << std::endl;
        }

        // Different underlying container
        // Using helper function to allocate std::vector with known size (fast)
        {
            int max_size = 100;
            auto stack = vector_stack<int>(max_size);

            for (int i {0}; i < max_size; ++i)
            {
                std::cout << i << " ";   
                stack.push(i);
            }

            stack.pop();
            while (!stack.empty())
            {
                std::cout << stack.top() << " "; 
                stack.pop();
            }
            std::cout << std::endl << "Size: " << stack.size() << std::endl << std::endl;
        }
    }

    // Queue (FIFO)
    {
        std::string string {"NOT REVERSED?"};
        std::queue<char> queue;

        std::cout << "Introducing... The Mighty Queue!" << std::endl;
        auto it = string.begin();
        while (it != string.end())
        {
            std::cout << *it << " ";
            queue.push(*it);
            ++it;
        }
        std::cout << std::endl;

        while (!queue.empty())
        {
            std::cout << queue.front() << " ";
            queue.pop();
        }
        std::cout << std::endl << std::endl;
    }

    // Priority queue
    {
        //std::priority_queue<int> queue;
        //std::vector<int> vector {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::priority_queue<Person> queue;
        std::vector<Person> vector {{"Larry", 20}, {"Moe", 40}, {"Curly", 30}};

        std::cout << "And... The Mighty Priority Queue! (Larges comes first)" << std::endl;

        auto it = vector.begin();
        while (it != vector.end())
        {
            std::cout << *it << " ";
            queue.push(*it);
            ++it;
        }
        std::cout << std::endl;
        
        while (!queue.empty())
        {
            std::cout << queue.top() << " ";
            queue.pop();
        }
        std::cout << std::endl << std::endl;
    }
}

int main()
{

    algorithms();
    std::cout << std::endl;
    templates();
    std::cout << std::endl;
    my_custom_array();
    std::cout << std::endl;
    containers();

    std::vector<long double> vector {};
    std::cout << "vector.max_size() " << vector.max_size() << std::endl;    // Big number

    return 0;
}