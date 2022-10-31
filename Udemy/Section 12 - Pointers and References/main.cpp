#include <iostream>
#include <vector>

int *create_array(size_t size, int initial_value = 0)
{
    int *new_storage {nullptr};

    new_storage = new int[size];

    for (size_t i {0}; i < size; i++)
        new_storage[i] = initial_value;

    return new_storage;
}

void display(const int *const array, size_t size)
{
    for (size_t i {0}; i < size; i++)
        std::cout << array[i] << " ";

    std::cout << std::endl;
}

int main()
{
    int num {10};
    std::cout << num << std::endl;
    std::cout << sizeof num << std::endl;
    std::cout << &num << std::endl;

    int *int_ptr {&num};
    std::cout << int_ptr << std::endl;
    std::cout << sizeof int_ptr << std::endl;
    std::cout << &int_ptr << std::endl;
    std::cout << *int_ptr << std::endl;
    *int_ptr *= 2;
    std::cout << *int_ptr << std::endl;

    std::vector<int> vector;
    std::cout << vector.size() << std::endl;

    std::vector<int> *vector_ptr {&vector};
    vector_ptr->push_back(99);

    std::cout << vector.at(0) + vector_ptr->at(0) << std::endl;

    {
        int *int_ptr {nullptr};
        int_ptr = new int;
        *int_ptr = 666;
        std::cout << *int_ptr << std::endl;
        delete int_ptr;

        double *double_ptr {nullptr};
        size_t size {666};
        double_ptr = new double[size];
        double_ptr[0] = 0.666;
        *(double_ptr + 1) = 6.66;
        double_ptr[2] = 66.6;

        // Pointer subscript vs. offset notation (when dealing with raw arrays)
        std::cout << *double_ptr << " " << double_ptr[1] << " " << *(double_ptr + 2) << std::endl;
        delete [] double_ptr;
    }

    {
        size_t size {666};
        int *array_ptr = create_array(size, 666);
        display(array_ptr, size);
        delete [] array_ptr;
    }

    return 0;
}