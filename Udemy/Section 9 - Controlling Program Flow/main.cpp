#include <iostream>
#include <vector>

// Coding Exercise 14
int calculate_sum()
{
    int odd_integers {};

    for (int i {1}; i < 16; i++ )
    {
        if (i % 2 != 0)
        {
            odd_integers += i;
            std::cout << i << " is odd" << std::endl;
        }
    }

    return odd_integers;
}

// Coding Exercise 15
int count_divisible()
{
    std::vector<int> vector {1,3,5,15,16,17,18,19,20,21,25,26,27,30,50,55,56,58,100,200,300,400,500,600,700};

    int count {};
    for (const auto& value : vector)
    {
        if (value % 3 == 0 || value % 5 == 0)
            count++;
    }

    return count;
}

// Coding Exercise 16
int count_numbers(const std::vector<int> &vector)
{
    std::cout << "Size of vector: " << vector.size() << std::endl;

    size_t count {}, index {};
    while (index < vector.size() && vector.at(index) != -99)
    {
        count++;
        index++;
    }

    return count;
}

int main()
{
    int odd_integers = calculate_sum();
    std::cout << "The sum of odd integers is: " << odd_integers << std::endl;

    int count = count_divisible();
    std::cout << "Count of elements evenly divisible by 3 and 5: " << count << std::endl;

    std::vector<int> vector {1,3,5,15,16,17,18,19,20,21,25,26,27,30,50,55,56,58,100,200,300,400,500,600,700,-99};
    count = count_numbers(vector);
    std::cout << "Count of elements present before value (-99): " << count << std::endl;

    return 0;
}