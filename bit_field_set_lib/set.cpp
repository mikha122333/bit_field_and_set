#include "set.h"

set set::operator+(size_t num)const {
    set res(*this);
    res += num;
    return res;
}

set set::operator-(size_t num)const {
    set res(*this);
    res -= num;
    return res;
}

set set::operator -(const set& other)const {
    set res(*this);
    res -= other;
    return res;
}

set set::operator +(const set& other)const {
    set res(*this);
    res += other;
    return res;
}

set set::operator *(const set& other)const {
    set res(*this);
    res *= other;
    return res;
}

std::ostream& operator<<(std::ostream& out, const set& other) {
    out << "{ ";
    size_t i = 0;
    bool is_first_found = 0;
    while (i < other._b_field.size() && !is_first_found) {
        if (other._b_field.get_bit(i)) {
            out << i;
            is_first_found = 1;
        }
        i++;
    }
    for (; i < other._b_field.size(); i++) {
        if (other._b_field.get_bit(i))
            out << ", "<<i;
    }
    out << " }";
    return out;
}
std::iostream& operator>>(std::iostream& in, set& other) {
    char tmp;
    size_t tmp_num=0;
    bit_field tmp_b_f(other._b_field.size());
    in >> tmp;
    if (tmp != '{') return in;
    in >> tmp;
    while (tmp != '}') {
        if (isdigit(tmp)) {
            tmp_num *= 10;
            tmp_num += static_cast<size_t>(tmp - '0');
        }
        else if (tmp == ',') {
            if (tmp_num >= tmp_b_f.size())
                return in;
            tmp_b_f.set_bit(tmp_num);
            tmp_num = 0;
        }
        in >> tmp;
    }
    if (tmp_num >= tmp_b_f.size())
        return in;
    tmp_b_f.set_bit(tmp_num);
    other._b_field = std::move(tmp_b_f);
    return in;
}

set simple_numbers(size_t size){
    bit_field tmp(size);
    tmp=~tmp;
    set res(tmp);
    if (res.size() >= 1)
        res.erase(0);
    if (res.size() >= 2)
        res.erase(1);
    for (size_t i = 2; i * i < res.size(); i++) {
        if(res.is_exist(i)){
            for (size_t i2 = i * i; i2 < res.size(); i2 += i) {
                res.erase(i2);
            }
        }
    }
    return res;
}