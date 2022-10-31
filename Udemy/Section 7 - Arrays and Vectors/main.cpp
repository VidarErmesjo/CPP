#include <iostream>
#include <vector>

// Coding Exercise 5
std::vector<int> use_array()
{
    int arr[10] {};
    arr[0] = 100;
    arr[9] = 1000;
    
    std::vector<int> vector(arr, arr + sizeof arr / sizeof arr[0]);
    return vector;
}

// Coding Exercise 6
std::vector<int> use_vector()
{
    std::vector<int> vector {10, 20, 30, 40, 50};
    vector.at(0) = 100;
    vector.at(4) = 1000;

    return vector;
}

int main()
{
    std::cout << "The size of use_array() is: " << use_array().size() << std::endl;

    std::cout << "The content of use_vector() is: " << std::endl;
    auto vector = use_vector();
    std::cout << vector.at(0) << std::endl;
    std::cout << vector.at(1) << std::endl;
    std::cout << vector.at(2) << std::endl;
    std::cout << vector.at(3) << std::endl;
    std::cout << vector.at(4) << std::endl;

    return 0;
}