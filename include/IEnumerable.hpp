#pragma once
#include <iterator>

template <typename T>
struct IEnumerator {
    virtual ~IEnumerator() = default;
    virtual bool MoveNext() = 0;
    virtual const T& Current() const = 0;
};

template <typename T>
struct IEnumerable {
    virtual ~IEnumerable() = default;
    virtual IEnumerator<T>* GetEnumerator() const = 0;
};
