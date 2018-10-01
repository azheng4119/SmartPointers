//Andy Zheng Home Project # 1 CSCI 335 Septemeber 30th - Implementation File

#include <iostream>
#include <string>
#include <utility>
#include "my_memory.h"

//UNIQUE POINTER IMPLEMENTATION

//Default constructor that initializes the object to point to nullptr.
template <class type>
my_unique_ptr<type>::my_unique_ptr() : ptr(nullptr){};

//Constructor that takes a pointer Type * as a parameter and sets the object to point there. We say that the newly created object takes ownership of the pointed memory.
template <class type>
my_unique_ptr<type>::my_unique_ptr(type * rhs) : ptr(std::move(rhs)){
    rhs = nullptr;
};

//Move constructor that takes my_unique_ptr object and constructs a new object from it.
template <class type>
my_unique_ptr<type>::my_unique_ptr(my_unique_ptr&& rhs) : ptr(std::move(rhs.ptr)){
    rhs.ptr = nullptr;
};

//Destructor that releases/deletes the block of memory pointed by the object.
template <class type>
my_unique_ptr<type>::~my_unique_ptr(){
    delete ptr;
    ptr = nullptr;
}

//Operator -> that returns the pointer to the object. It allows to use the my_unique_ptr object for class member access.
template <class type>
type* my_unique_ptr<type>::operator -> (){
    return ptr;
}

//Dereference operator * that returns a reference to the item pointed by the object.
template <class type>
type& my_unique_ptr<type>::operator * (){
    return *ptr;
}

//Move assignment operator.
template <class type>
my_unique_ptr<type> & my_unique_ptr<type>::operator = (my_unique_ptr<type> && rhs){
    ptr = std::move(rhs.ptr);
    rhs.ptr = nullptr;
    return *this;
}

//SHARED POINTER IMPLEMENTATION

//Default constructor that sets all inner pointers to nullptr.
template<class type>
my_shared_ptr<type>::my_shared_ptr() : count(nullptr) , ptr(nullptr){};

//Constructor that takes Type * as a parameter and sets the object to point there. The object considers itself to be the first my_shared_ptr object to point to that block of memory. So the counter should be set to 1.
template<class type>
my_shared_ptr<type>::my_shared_ptr(type * t) : ptr(std::move(t)) , count(new int {1}){};

//Copy constructor. Since the original object already points to the block of memory and now the newly created object points there too, you must increase the counter by 1.
template<class type>
my_shared_ptr<type>::my_shared_ptr(const my_shared_ptr& t) {
    if (t.ptr != nullptr && t.count != nullptr){
        count = std::move(t.count);
        (*t.count)++;
    }
    else{
    ptr = std::move (t.ptr);
    count = std::move (t.count);
    }
};

//Move constructor. Since the original rvalue wont point to the block of memory no more, the counter should remain the same.
template <class type>
my_shared_ptr<type>::my_shared_ptr(my_shared_ptr && t) {
    count = std::move(t.count);
    ptr = std::move(t.ptr);
    t.ptr = nullptr;
    t.count = nullptr;
}

//Dereference operator * that returns a reference to the item pointed by the object.
template <class type>
type & my_shared_ptr<type>::operator * () const{
    if (ptr == nullptr) std::cout << "PTR IS NULL." <<std::endl;
    return *ptr;
};

//Operator -> that returns the pointer to the object. It allows to use the my_shared_ptr object for class member access.
template<class type>
type * my_shared_ptr<type>::operator->() const{
    return ptr;
};

//Copy and move assignment operators. If prior to the assignment the my_shared_ptr object was already pointing somewhere, the counter for the old block of memory should be decreased by 1, and if it reaches 0, the old block of memory should be released/deleted. Copy assignment should also increase the counter for the newly pointed block of memory.
template<class type>
my_shared_ptr<type> & my_shared_ptr<type>::operator = (const my_shared_ptr<type> & rhs){
    if (ptr != nullptr && ptr != rhs.ptr){
        (*count)--;
        if (*count == 0){
            delete ptr;
            ptr = nullptr;
            delete count;
            count = nullptr;
        }
    }
    ptr = std::move(rhs.ptr);
    count = std::move(rhs.count);
    if (ptr != nullptr)(*count)++;
    return *this;
};

template<class type>
my_shared_ptr<type> & my_shared_ptr<type>::operator = (my_shared_ptr<type> && rhs){
    if (ptr != nullptr){
        (*count)--;
        if (*count == 0){
            delete count;
            delete ptr;
        }
    }
    ptr = std::move(rhs.ptr);
    count = std::move(rhs.count);
    rhs.count = nullptr;
    rhs.ptr = nullptr;
    return *this;
};

//Destructor that releases/deletes the block of memory and the counter if no other shared pointer points there.
template<class type>
my_shared_ptr<type>::~my_shared_ptr() {
    if (count != nullptr && ptr != nullptr){
        if (*count == 0){
            delete ptr;
            delete count;
        }
        (*count)--;
    }
    ptr = nullptr;
    count = nullptr;
};
