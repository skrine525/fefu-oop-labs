#pragma once
#include <iterator>

template <typename T>
class Container
{
public:
    struct Node
    {
        Node* next = nullptr;
        Node* prev = nullptr;
        T* value;

        ~Node();
    };

    class Iterator
    {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator(Node* ptr, Node* head) : current(ptr), head(head) {}

        // Операторы сравнения
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        // Операторы инкремента и декремента
        Iterator& operator++() {
            if (current)
            {
                if (current->next == head)
                    current = nullptr;
                else
                    current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            if (current)
            {
                if (current->next == head)
                    current =  nullptr;
                else
                    current = current->next;
            }
            return temp;
        }

        Iterator& operator--() {
            if (current)
            {
                if (current->prev == head)
                    current = nullptr;
                else
                    current = current->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            if (current)
            {
                if (current->prev == head)
                    current = nullptr;
                else
                    current = current->prev;
            }
            return temp;
        }

        // Операторы разыменования
        reference operator*() const {
            return *current->value;
        }

        pointer operator->() const {
            return current->value;
        }

    private:
        Node* current;
        Node* head;
    };

    Container() : head(nullptr) {}
    ~Container();
    void insertNode(T* value);
    void deleteNode(const T& value);
    bool isEmpty();
    void clear();

    Iterator begin()
    {
        return Iterator(head, head);
    }

    Iterator end()
    {
        return Iterator(nullptr, head);
    }

private:
    Node* head;
};

template <typename T>
class ContainerBuilder
{

public:
    ContainerBuilder() {};

    void add(T* value);
    Container<T>* get();

private:
    Container<T> containter;
};

template <typename T>
void ContainerBuilder<T>::add(T* value)
{
    containter.insertNode(value);
}

template <typename T>
Container<T>* ContainerBuilder<T>::get()
{
    Container<T>* newContainer = new Container<T>;

    auto beg = containter.begin();
    auto end = containter.end();
    while (beg != end)
    {
        newContainer->insertNode(new T(*beg));
        beg++;
    }

    return newContainer;
}

template <typename T>
Container<T>::Node::~Node()
{
    delete this->value;
}

template <typename T>
Container<T>::~Container()
{
    this->clear();
}

template <typename T>
void Container<T>::clear()
{
    Node* curr = head;
    if (curr != nullptr)
    {
        do
        {
            Node* d = curr;
            curr = curr->next;
            delete d;
        } while (curr != head);
    }
    head = nullptr;
}

template <typename T>
bool Container<T>::isEmpty()
{
    return (head == nullptr);
}

template <typename T>
void Container<T>::deleteNode(const T& value)
{
    Node* curr = head;
    if (curr != nullptr)
    {
        do
        {
            if (*curr->value == value)
            {
                if (curr == head && curr->next == head)
                {
                    delete curr;
                    head = nullptr;
                }
                else
                {
                    Node* prev = curr->prev;
                    Node* next = curr->next;
                    prev->next = next;
                    next->prev = prev;
                    if (curr == head)
                        head = curr->next;
                    delete curr;
                    curr = nullptr;
                }
            }
            else
                curr = curr->next;
        } while (curr != head && curr != nullptr && head != nullptr);
    }
}

template <typename T>
void Container<T>::insertNode(T* value)
{
    if (head == nullptr)
    {
        head = new Node;
        head->next = head;
        head->prev = head;
        head->value = value;
    }
    else
    {
        bool canDeleteValue = true;
        Node* curr = head;
        do
        {
            if (*curr->value != *value && *value < *curr->value)
            {
                Node* ncurr = new Node;
                ncurr->value = value;
                if (curr == head)
                    head = ncurr;

                ncurr->next = curr;
                ncurr->prev = curr->prev;
                curr->prev->next = ncurr;
                curr->prev = ncurr;
                canDeleteValue = false;
            }
            else if (*curr->value != *value && curr->next == head)
            {
                Node* ncurr = new Node;
                ncurr->value = value;
                ncurr->next = curr->next;
                ncurr->prev = curr;
                curr->next->prev = ncurr;
                curr->next = ncurr;
                canDeleteValue = false;
            }
            else
                curr = curr->next;
        } while (*curr->prev->value < *value);

        if (canDeleteValue)
            delete value;
    }
}

//template <typename Type>
//class Container
//{
//public:
//    struct Iterator
//    {
//        using iterator_category = std::random_access_iterator_tag;
//        using difference_type = std::ptrdiff_t;
//        using value_type = Type;
//        using pointer = Type*;
//        using reference = Type&;
//
//        Iterator(Container::Iterator& o) : m_ptr(o.m_ptr) {}
//        Iterator(Container::Iterator&& o) noexcept : m_ptr(std::move(o.m_ptr))
//        {
//            o.m_ptr = nullptr;
//        }
//        Iterator(pointer ptr) : m_ptr(ptr) {}
//        ~Iterator() {}
//
//        reference operator*() const { return *m_ptr; }
//        pointer operator->() { return m_ptr; }
//        Iterator& operator++() { m_ptr++; return *this; }
//        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
//        Iterator& operator--() { m_ptr--; return *this; }
//        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
//        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
//        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
//        friend bool operator< (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr; };
//        friend bool operator> (const Iterator& a, const Iterator& b) { return a.m_ptr > b.m_ptr; };
//        friend bool operator>= (const Iterator& a, const Iterator& b) { return (a.m_ptr > b.m_ptr) || (a.m_ptr == b.m_ptr); };
//        friend bool operator<= (const Iterator& a, const Iterator& b) { return (a.m_ptr < b.m_ptr) || (a.m_ptr == b.m_ptr); };
//
//        Iterator& operator+(int n)
//        {
//            m_ptr = m_ptr + n;
//            return *this;
//        }
//        Iterator& operator-(int n)
//        {
//            m_ptr = m_ptr - n;
//            return *this;
//        }
//        Iterator& operator+=(int n)
//        {
//            m_ptr = m_ptr + n;
//            return *this;
//        }
//        Iterator& operator-=(int n)
//        {
//            m_ptr = m_ptr - n;
//            return *this;
//        }
//
//
//        // copy assignment
//        Iterator& operator=(const Container::Iterator& other)
//        {
//            // Guard self assignment
//            if (this == &other)
//                return *this;
//
//            *m_ptr = *other;
//            return *this;
//        }
//
//        // move assignment
//        Iterator& operator=(Iterator&& other) noexcept
//        {
//            // Guard self assignment
//            if (this == &other)
//                return *this;
//
//            m_ptr = std::move(other.m_ptr);
//            other.m_ptr = nullptr;
//
//            return *this;
//        }
//
//        void swap(Iterator& other) {
//            std::swap(*m_ptr, *other);
//        }
//
//    private:
//        pointer m_ptr;
//    };
//
//    Container() { currIndex = 0; }
//    //~Container() { delete[] m_data; } TODO падает деструктор
//    Iterator begin() { return Iterator(&m_data[0]); }
//    Iterator end() { return Iterator(&m_data[currIndex]); }
//    void add(const Type& value)
//    {
//        if (currIndex < size)
//        {
//            m_data[currIndex] = value;
//            currIndex++;
//        }
//    }
//    int getSize() { return size; }
//
//private:
//    Type m_data[255];
//    int size;
//    int currIndex;
//};