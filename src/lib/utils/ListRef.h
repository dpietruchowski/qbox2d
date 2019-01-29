#ifndef LISTREF_H
#define LISTREF_H

#include <list>
#include <functional>

template<class T>
class ListRef: public std::list<std::reference_wrapper<T>>
{
public:
    using std::list<std::reference_wrapper<T>>::list;

    void Add(T& reference) {
        this->push_back(std::ref(reference));
    }

    void Remove(T& reference) {
        this->remove_if([&reference](T& lreference) { return &reference == &lreference; });
    }
};

#endif // LISTREF_H
