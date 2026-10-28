#pragma once
#include "bit_field.h"

class set {
    bit_field _b_field;
public:
    set(size_t size);
    set(const set& other);
    set(set&& other);
    set(const bit_field& other);

    operator bit_field() const;

    void insert(size_t num);
    void erase(size_t num);

    set& operator+=(size_t num);
    set& operator-=(size_t num);

    set operator+(size_t num)const;
    set operator-(size_t num)const;

    set& operator -=(const set& other);
    set& operator +=(const set& other);
    set& operator *=(const set& other);

    set& operator -(const set& other)const;
    set& operator +(const set& other)const;
    set& operator *(const set& other)const;

    set& operator= (const set& other);
    set& operator= (set&& other);

    bool operator ==(const set& other)const;
    inline bool operator !=(const set& other)const { return !((*this) == other); }

    friend std::ostream& operator>>(std::ostream& out, const set& other);
    friend std::iostream& operator<<(std::iostream& in, set& other);
};