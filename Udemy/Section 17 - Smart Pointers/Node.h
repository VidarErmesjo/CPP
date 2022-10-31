#include <memory>

template<typename T>
struct Node
{
    T data;
    std::weak_ptr<Node> next;   // or raw pointer
    std::shared_ptr<Node> prev;
};

//std::shared_ptr<Node<T>> root; // inside list