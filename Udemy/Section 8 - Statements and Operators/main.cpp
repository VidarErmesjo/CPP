#include <iostream>
#include <tuple>

// Coding Exercise 7
void assignment_operator()
{
    int num1 {13};
    int num2 {0};
    num1 = 5;
    num2 = num1;
      
   std::cout << num1 << " " << num2 << std::endl;
}

// Coding Exercise 8
int arithmetic_operators(int number)
{
    int original_number {number};    

    number = number * 2;
    number = number + 9;
    number = number - 3;
    number = number / 2;
    number = number - original_number;
    number = number % 3; 
    
    return number;
}

int main()
{
    assignment_operator();

    std::cout << arithmetic_operators(666) << std::endl;

    return 0;
}