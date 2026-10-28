#pragma once
#include "bit_field.h"

class set {
    bit_field _b_field;
public:
    inline set(size_t size = 1) :_b_field(size) {}
    inline set(const set& other) :_b_field(other._b_field) {}
    inline set(set&& other) :_b_field(std::move(other._b_field)) {}
    inline set(const bit_field& other) :_b_field(other) {}

    inline operator bit_field() const noexcept { return _b_field; }

    inline void insert(size_t num) { _b_field.set_bit(num); }
    inline void erase(size_t num) { _b_field.reset_bit(num); }

    inline bool is_exist(size_t num)const noexcept {if (num >= _b_field.size()) return 0;return _b_field.get_bit(num);}
    inline size_t size()const noexcept { return _b_field.size(); }

    inline set& operator+=(size_t num) { insert(num); return (*this); }
    inline set& operator-=(size_t num) { erase(num); return(*this); }

    set operator+(size_t num)const;
    set operator-(size_t num)const;

    inline set& operator -=(const set& other) { _b_field &= ~(other._b_field); return (*this); }
    inline set& operator +=(const set& other) { _b_field |= other._b_field; return (*this); }
    inline set& operator *=(const set& other) { _b_field &= other._b_field; return (*this); }

    set operator -(const set& other)const;
    set operator +(const set& other)const;
    set operator *(const set& other)const;

    inline set& operator= (const set& other)noexcept { _b_field = other._b_field; return (*this); }
    inline set& operator= (set&& other)noexcept { _b_field = std::move(other._b_field); return (*this); }

    inline bool operator ==(const set& other)const noexcept { return _b_field == other._b_field; }
    inline bool operator !=(const set& other)const { return !((*this) == other); }

    friend std::ostream& operator<<(std::ostream& out, const set& other);
    friend std::iostream& operator>>(std::iostream& in, set& other);

};

set simple_numbers(size_t size);