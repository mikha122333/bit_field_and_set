#include "bit_field.h"
size_t bit_field::index(size_t pos)const  {
    if (pos >= _size) throw std::out_of_range("tried get_index with wrong pos");
    return pos % (sizeof(unsigned int) * 8);
}

bit_field::bit_field(size_t size) {
    if (size == 0)throw  std::logic_error("size=0");
    _size = size;
    _data = new unsigned int[int_amount()];
    for (int i = 0; i < int_amount(); i++) {
        _data[i] = 0;
    }
}

bit_field::bit_field(const bit_field& other) {
    if(_data!=nullptr)
        delete[]_data;
    _size = other._size;
    _data = new unsigned int[int_amount()];
    for (int i = 0; i < int_amount(); i++) {
        _data[i] = other._data[i];
    }
}

bit_field::bit_field(bit_field&& other) {
    if(_data!=nullptr)
        delete[]_data;
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    other._size = 0;
}

bit_field::~bit_field() {
    if (_data != nullptr)
        delete[]_data;
}

bool bit_field::get_bit(size_t pos)const {
    if (pos >= _size)throw std::out_of_range("tried get_bit with too big pos");
    return _data[index(pos)] & mask(pos);
}

void bit_field::set_bit(size_t pos) {
    if (pos >= _size)throw std::out_of_range("tried set_bit with too big pos");
    _data[index(pos)] |= mask(pos);
}

void bit_field::reset_bit(size_t pos) {
    if (pos >= _size)throw std::out_of_range("tried reset_bit with too big pos");
    _data[index(pos)] & (~mask(pos));
}

bit_field& bit_field::operator=(const bit_field& other){
    if (this == &other) throw std::logic_error("tried =");
    if (_data != nullptr)
        delete[]_data;
    _size = other._size;
    _data = new unsigned int[int_amount()];
    for (int i = 0; i < int_amount(); i++) {
        _data[i] = other._data[i];
    }
    return (*this);
}

bit_field& bit_field::operator=(bit_field&& other) {
    if (this == &other) throw std::logic_error("tried =");
    if (_data != nullptr)
        delete[]_data;
    _size = other._size;
    _data = other._data;
    other._data = nullptr;
    other._size = 0;
    return (*this);
}

bit_field& bit_field::operator &=(const bit_field& other) {
    if (_size != other._size)throw std::logic_error("dif sizes");
    for (int i = 0; i < int_amount(); i++) {
        _data[i] &= other._data[i];
    }
    return(*this);
}

bit_field& bit_field::operator |=(const bit_field& other) {
    if (_size != other._size)throw std::logic_error("dif sizes");
    for (int i = 0; i < int_amount(); i++) {
        _data[i] |= other._data[i];
    }
    return(*this);
}

bit_field bit_field::operator &(const bit_field& other)const {
    bit_field res(*this);
    res &= other;
    return res;
}

bit_field bit_field::operator |(const bit_field& other)const {
    bit_field res(*this);
    res |= other;
    return res;
}

bit_field bit_field::operator ~() {
    for (int i = 0; i < int_amount(); i++) {
        _data[i] = ~_data[i];
    }
}

std::ostream& operator<<(std::ostream& out, const bit_field& other) {
    for (size_t i = 0; i < other._size; i++) {
        out << other.get_bit(i);
    }
    return out;
}

std::iostream& operator>>(std::iostream& in, bit_field& other) {
    bit_field tmp(other._size);
    char c;
    for (int i = 0; i < other._size; i++) {
        in >> c;
        if (c == '0') {
            tmp.reset_bit(i);
        }
        else if (c == '1') {
            tmp.set_bit(i);
        }
        else { return in; }
    }
    other = std::move(tmp);
    return (in);
}