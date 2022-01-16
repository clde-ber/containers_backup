#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
#include <cstddef>

#define TRUE 1
#define FALSE 0

namespace ft
{
    template< typename T >
    class vector
    {
        private:
            size_t _n;
            T* _p;
            size_t _capacity;
        public:
            typedef int size_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef pointer iterator;
            typedef pointer reverse_iterator;
            typedef pointer const_iterator;
            typedef pointer const_reverse_iterator;

            vector( void ) : _n(0), _p(0), _capacity(0)
            {
                //std::allocator< T > alloc;
                //_p = alloc.allocate(_capacity, this);
            }
            vector( unsigned long n ) : _n(n), _p(0), _capacity(n)
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(_capacity, this);
            }
            vector( const vector & rhs )
            {
                *this = rhs;
            }
            template< typename U >
            vector(U it, U ite) : _n(0), _p(0), _capacity(0)
            {
                assign(it, ite);
            }
            vector & operator=( vector const & rhs )
            {
                std::allocator< T > alloc;
                _p = alloc.allocate(rhs._capacity, this);
                _n = rhs._n;
                _capacity = rhs._capacity;
                for (unsigned long i = 0; i < _capacity; i++)
                    _p[i] = rhs._p[i];
                return *this;
            }
            virtual ~vector( void )
            {
                if (_p)
                {
                    std::allocator< T > alloc;
                    alloc.deallocate(_p, _capacity);
                }
                _capacity = 0;
                _n = 0;
                _p = 0;
            }
            unsigned long size() const
            {
                return _n;
            }
            const_iterator begin() const
            {
                return &_p[0];
            }
            const_iterator end() const
            {
                return &_p[_n];
            }
            const_reverse_iterator rbegin() const
            {
                return &_p[_n];
            }
            const_reverse_iterator rend() const
            {
                return &_p[0];
            }
            pointer operator++(int inc) {return (this < this + inc) ? this + inc : this - inc;}
            T operator++() {T tmp = *this; if (this < this + 1) this++; else this--; return tmp;}
            pointer operator--(int inc) {return (this < this + inc) ? this - inc : this + inc;}
            T operator--() {T tmp = *this; if (this < this + 1) this--; else this++; return tmp;}
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            T & operator[](unsigned long n)
            {
                if (n < 0 or n >= _capacity)
                    throw std::exception();
                return _p[n];
            }
            T & back() const
            {
                if (!empty())
                    return _p[_n - 1];
                throw std::exception();
            }
            T & front() const
            {
                if (!empty())
                    return _p[0];
                throw std::exception();
            }
            T * data()
            {
                if (!empty())
                    return &_p[0];
                throw std::exception();
            }
            T & at(size_t pos) const
            {
                if (!(pos < size()))
                    throw std::out_of_range("");
                return _p[pos];
            }
            void push_back(T const & val)
            {
                resize(_capacity + 1, val);
            }
            void pop_back()
            {
                if (!_n)
                    throw std::exception();
               resize(_capacity - 1);
            }
            void reserve( size_t new_cap )
            {
                ft::vector< T > newV(new_cap);
                this->~vector();
                *this = newV;
                newV.~vector();
            }
            size_t capacity() const
            {
                return _capacity;
            }
            size_t ft_pow(size_t n, size_t pow) const
            {
                size_t i = 0;
                size_t res = 1;

                while (i < pow)
                {
                    res = res * n;
                    i++;
                }
                return res;
            }
            size_t max_size() const
            {
                return (ft_pow(2, 32) / sizeof(T)) * ft_pow(2, 32) - 1;
            }
            void resize (size_t n, T value = 0)
            {
                unsigned long i = 0;
                if (n < _capacity)
                {
                    ft::vector< T > tmp(n);
                    while (i < tmp.size())
                    {
                        tmp._p[i] = _p[i];
                        i++;
                    }
                    this->~vector();
                    *this = tmp;
                }
                else if (n > _capacity)
                {
                    ft::vector< T > tmp(n);
                    while (i < size())
                    {
                        tmp._p[i] = _p[i];
                        i++;
                    }
                    while (i <  tmp.size())
                        tmp._p[i++] = value;
                    this->~vector();
                    *this = tmp;
                }
            }
            template< typename U >
            void assign(U first, U last)
            {
               size_t i = 0;
               size_t len = 0;
                while(first != last)
                {
                    first++;
                    i++;
                }
                len = i;
                while (i--)
                    first--;
                insert(begin(), first, last);
                resize(len);
            }
            void assign(size_type n, T const & value)
            {
                insert(begin(), n, value);
                resize(n);
            }
            void insert(const_iterator pos, size_type const n, const T & val)
            {
                if (n < 0)
                    throw std::exception();
                size_type i = 0;
                size_type x = 0;
                size_type len = _capacity;
                while (pos != begin())
                {
                    pos--;
                    i++;
                }
                ft::vector< T > copy(*this);
                ft::vector< T > res(_n + n);
                for (x = 0; x < i; x++)
                    res._p[x] = copy._p[x];
                for (size_type y = 0; y < n; y++)
                    res._p[x++] = val;
                while (i < len)
                    res._p[x++] = copy._p[i++];
                this->~vector();
                *this = res;
                copy.~vector();
            }
            template< typename U >
            void insert(iterator pos, U first, U last)
            {
                size_type i = 0;
                size_type ct = 0;
                size_type x = 0;
                size_type y = 0;
                size_type len = size();
                while (pos != begin())
                {
                    pos--;
                    i++;
                }
                while (first != last)
                {
                    ct++;
                    first++;
                    y++;
                }
                while (y--)
                    first--;
                ft::vector< T > copy(*this);
                ft::vector< T > res(_n + ct);
                for (x = 0; x < i; x++)
                    res._p[x] = copy._p[x];
                for (size_type y = 0; y < ct; y++)
                    res._p[x++] = *(first++);
                while (i < len)
                    res._p[x++] = copy._p[i++];
                this->~vector();
                *this = res;
                copy.~vector();
            }
            iterator insert (const_iterator position, const T & val)
            {
                unsigned long i = 0;
                iterator it = begin();
                iterator ite = end();
                if (_n + 1 > _capacity)
                {
                    ft::vector<T> res(_n + 1);
                    while (it != position && it != ite)
                    {
                        res._p[i] = *it;
                        it++;
                        i++;
                    }
                    res._p[i++] = val;
                    while (it != ite)
                    {
                        res._p[i] = *it;
                        it++;
                        i++;
                    }
                    this->~vector();
                    *this = res;
                    res.~vector();
                }
                else
                {
                    while (it != position && it != ite)
                    {
                        _p[i] = *it;
                        it++;
                        i++;
                    }
                    _p[i++] = val;
                    while (it != ite)
                    {
                        _p[i] = *it;
                        it++;
                        i++;
                    }
                }
                return position;
            }
            iterator erase(const_iterator position)
            {
                unsigned long i = 0;
                unsigned long len = 0;
                iterator it = begin();
                iterator ite = end();
                if (!(position >= it && position < ite))
                    throw std::exception();
                ft::vector< T > tmp(*this);
                while (it != ite)
                {
                    if (it == position)
                        len = i;
                    it++;
                }
                resize(i, 0);
                it = begin();
                ite = end();
                i = 0;
                while (i < tmp.size())
                {
                    if (i != len)
                    {
                        *it = tmp._p[i];
                        it++;
                    }
                    i++;
                }
                return it;
            }
            iterator erase(const_iterator first, const_iterator last)
            {
                unsigned long i = 0;
                unsigned long len = 0;
                unsigned long pos = 0;
                iterator it = begin();
                iterator ite = end();
                if (!(first >= it &&  first < ite && last >= it && last < ite))
                    throw std::exception();
                ft::vector< T > tmp(*this);
                while (it != first)
                {
                    i++;
                    first++;
                }
                pos = i;
                while (it != last)
                {
                    i++;
                    first++;
                }
                len = i;
                resize(len - pos);
                it = begin();
                ite = end();
                i = 0;
                while (i < tmp.size())
                {
                    if (i < pos || i > len)
                    {
                        *it = tmp._p[i];
                        it++;
                    }
                    i++;
                }
                return it;
            }
            void swap(ft::vector< T > & x)
            {
                ft::vector< T > tmp;

                tmp = *this;
                *this = x;
                x = tmp;
            }
            void clear()
            {
                this->~vector();
                vector< T > tmp;
                *this = tmp;
            }
    };
};
// this x
// a    b

// tmp = this
// this = x
// x = tmp
#endif
/*
begin
    Return iterator to beginning (public member function )

end
    Return iterator to end (public member function )

rbegin
    Return reverse iterator to reverse beginning (public member function )

rend
    Return reverse iterator to reverse end (public member function )

size
    Return size (public member function ) OK

max_size
    Return maximum size (public member function )

resize
    Change size (public member function )

capacity
    Return size of allocated storage capacity (public member function )

empty
    Test whether vector is empty (public member function ) OK

reserve
    Request a change in capacity (public member function )

operator[]
    Access element (public member function )

at
    Access element (public member function )

front
    Access first element (public member function )

back
    Access last element (public member function )

assign
    Assign vector content (public member function )

push_back
    Add element at the end (public member function )

pop_back
    Delete last element (public member function )

insert
    Insert elements (public member function )

erase
    Erase elements (public member function )

swap
    Swap content (public member function )

clear
    Clear content (public member function )

get_allocator
    Get allocator (public member function )

*/
