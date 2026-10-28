#pragma once
#include<stdexcept>
#include<iostream>

class bit_field {
    unsigned int* _data;
    size_t _size;
    size_t index(size_t pos)const;
    inline size_t int_amount()const noexcept { return (_size + sizeof(unsigned int) * 8 - 1) / (sizeof(unsigned int) * 8); }
    inline unsigned int mask(size_t pos)const noexcept { return 1 << pos % (sizeof(unsigned int) * 8); }
public:
    bit_field(size_t size);
    bit_field(const bit_field& other);
    bit_field(bit_field&& other);

    ~bit_field();

    bool get_bit(size_t pos)const;
    inline size_t size()const noexcept { return _size; }
    void set_bit(size_t pos);
    void reset_bit(size_t pos);

    bit_field& operator =(const bit_field& other);
    bit_field& operator =(bit_field&& other);

    bit_field& operator &=(const bit_field& other);
    bit_field& operator |= (const bit_field& other);

    bit_field operator &(const bit_field& other)const;
    bit_field operator |(const bit_field& other)const;
    bit_field operator ~();

    friend std::ostream& operator <<(std::ostream & out, const bit_field & other);
    friend std::iostream& operator >>(std::iostream& in, bit_field& other);
};