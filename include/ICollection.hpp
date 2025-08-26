#pragma once
#include <cstddef>

template <typename T>
struct ICollection {
    virtual ~ICollection() = default;
    virtual void Add(const T& value) = 0;
    virtual bool Remove(const T& value) = 0;
    virtual bool contains(const T& value) const = 0;
    virtual std::size_t Size() const = 0;
    virtual bool Empty() const = 0;
    virtual void clear() = 0;
};
