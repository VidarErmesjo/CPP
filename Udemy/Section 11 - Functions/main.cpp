#include <iostream>
#include <string>
#include <typeinfo>

// Coding Exercise 23
void print_grocery_list(int apples = 3, int oranges = 7, int mangos = 13);

void modify_grocery_list()
{
    // Default list
    print_grocery_list();

    // Next week
    print_grocery_list(5);

    // Final week
    print_grocery_list(7, 11);
}

void print_grocery_list(int apples, int oranges, int mangos)
{
    std::cout << apples << " apples" << "\n" << oranges << " oranges" << "\n" << mangos << " mangos" << std::endl;
}

// Coding Exercise 26
std::string print_guest_list(const std::string &guest_1, const std::string &guest_2, const std::string &guest_3);
void clear_guest_list(std::string &guest_1, std::string &guest_2, std::string &guest_3);

void event_guest_list()
{
    std::string guest_1 {"Larry"};
    std::string guest_2 {"Moe"};
    std::string guest_3 {"Curly"};

    print_guest_list(guest_1, guest_2, guest_3);
    clear_guest_list(guest_1, guest_2, guest_3);
    print_guest_list(guest_1, guest_2, guest_3);
}

std::string print_guest_list(const std::string &guest_1, const std::string &guest_2, const std::string &guest_3)
{
    std::cout << guest_1 << std::endl << guest_2 << std::endl << guest_3 << std::endl;

    std::string test_1 = typeid(guest_1).name(), test_2 = typeid(guest_2).name(), test_3 = typeid(guest_3).name();
    return test_1 + test_2 + test_3;
}

void clear_guest_list(std::string &guest_1, std::string &guest_2, std::string &guest_3)
{
    guest_1 = " ";
    guest_2 = " ";
    guest_3 = " ";
}

int main()
{
    modify_grocery_list();
    std::cout << std::endl;

    event_guest_list();

    return 0;
}