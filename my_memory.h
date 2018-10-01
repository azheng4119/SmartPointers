//Andy Zheng Home Project # 1 CSCI 335 Septemeber 30th - Header File

#ifndef my_memory_h
#define my_memory_h

template<class type>
class my_unique_ptr{
private:
    type * ptr;
public:
    my_unique_ptr();
    my_unique_ptr(type * rhs);
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr(my_unique_ptr&& t);
    type* operator -> ();
    type& operator * ();
    my_unique_ptr & operator = (my_unique_ptr && rhs);
    my_unique_ptr & operator = (const my_unique_ptr&) = delete;
    ~my_unique_ptr();
};

template<class type>
class my_shared_ptr{
private:
    type * ptr;
    int * count;
public:
    my_shared_ptr();
    my_shared_ptr(type * t);
    my_shared_ptr(const my_shared_ptr &rhs);
    my_shared_ptr(my_shared_ptr&& rhs);
    type * operator -> () const;
    type & operator * () const;
    my_shared_ptr & operator = (my_shared_ptr && rhs);
    my_shared_ptr & operator = (const my_shared_ptr&);
    ~my_shared_ptr();
};

#endif
