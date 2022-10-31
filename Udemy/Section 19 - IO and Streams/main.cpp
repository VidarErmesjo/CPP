#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

void read_file(std::string name = "test.txt", bool once = false)
{
    std::ifstream file {name};
    std::string line {};

    if (!file)
    {
        std::cerr << "File not found" << std::endl;
        return;
    }
    
    if (!once)
    {
        // First way
        while (!file.eof())
        {
            std::getline(file, line);
            std::cout << line << std::endl;
        }

        std::cout << std::endl;

        // Clear state buffer and seek to start of file
        file.clear();
        file.seekg(0);

        // Second way
        while (std::getline(file, line))
            std::cout << line << std::endl;

        std::cout << std::endl;

        file.clear();
        file.seekg(0);

        // Third way
        char c {};
        while (file.get(c))
            std::cout << c;

        std::cout << std::endl;
    }
    else
    {
        std::cout << std::endl;
        char c {};

        // Unformated -- one character at a time
        while (file.get(c))
            std::cout << std::setw(2) << std::left << c;
    }

    file.close();
}

void create_file(std::string line, int num, double total)
{
    std::ofstream file {"created_file.txt"};

    if (file.is_open())
    {
        file << line << std::endl << num << std::endl << total << std::endl;
    }
    
    file.close();
}

void append_file(std::string line, int num, double total)
{
    std::fstream file {"created_file.txt", std::ios::app};
    // .. or
    // std::fstream file {"created_file.txt", std::fstream::in | std::fstream::out | std::fstream::app};

    if (file.is_open())
    {
        file << line << std::endl << num << std::endl << total << std::endl;
    }

    file.close();
}

int main()
{
    read_file();
    create_file("Hello", 100, 0.666);
    append_file("Hello again", 1000, 666.666);
    read_file("created_file.txt", true);
    return 0;
}