#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

class complex{
public:
    complex(double real = 0.0, double imag = 0.0): m_real(real), m_imag(imag){ };
public:
    friend complex operator+(const complex & A, const complex & B);
    friend complex operator-(const complex & A, const complex & B);
    friend complex operator*(const complex & A, const complex & B);
    friend complex operator/(const complex & A, const complex & B);
    friend istream & operator>>(istream & in, complex & A);
    friend ostream & operator<<(ostream & out, complex & A)
    {
        out << A.m_real <<" + "<< A.m_imag <<" i ";;
        return out;
    }
private:
    double m_real;  //实部
    double m_imag;  //虚部
};

//重载加法运算符
complex operator+(const complex & A, const complex &B){
    complex C;
    C.m_real = A.m_real + B.m_real;
    C.m_imag = A.m_imag + B.m_imag;
    return C;
}

//重载减法运算符
complex operator-(const complex & A, const complex &B){
    complex C;
    C.m_real = A.m_real - B.m_real;
    C.m_imag = A.m_imag - B.m_imag;
    return C;
}

//重载乘法运算符
complex operator*(const complex & A, const complex &B){
    complex C;
    C.m_real = A.m_real * B.m_real - A.m_imag * B.m_imag;
    C.m_imag = A.m_imag * B.m_real + A.m_real * B.m_imag;
    return C;
}

//重载除法运算符
complex operator/(const complex & A, const complex & B){
    complex C;
    double square = A.m_real * A.m_real + A.m_imag * A.m_imag;
    C.m_real = (A.m_real * B.m_real + A.m_imag * B.m_imag)/square;
    C.m_imag = (A.m_imag * B.m_real - A.m_real * B.m_imag)/square;
    return C;
}

//重载输入运算符
istream & operator>>(istream & in, complex & A){
    in >> A.m_real >> A.m_imag;
    return in;
}


class HashKey
{
public:
    HashKey() {}
    HashKey(int type, int64_t value):m_type(type), m_value(value) {}
    ~HashKey() {}

    bool operator < (const HashKey & key) const
    {
        return m_value < key.m_value;
    }
    bool operator <= (const HashKey & key) const
    {
        return m_value <= key.m_value;
    }
    bool operator > (const HashKey & key) const
    {
        return m_value > key.m_value;
    }
    bool operator >= (const HashKey & key) const
    {
        return m_value >= key.m_value;
    }
    bool operator == (const HashKey & key) const
    {
        return m_value == key.m_value;
    }
    bool operator != (const HashKey & key) const
    {
        return m_value != key.m_value;
    }
public:
    int m_type;
    uint64_t m_value;
};

class Hashable
{
public:
    virtual HashKey hash() = 0;
};


int main(){
    std::map<HashKey, int> m;
    auto h1 = new HashKey(1,114);
    auto h2 = new HashKey(2,114);


    m[*h1] = 1;
    m[*h2] = 2;
    for (auto &item:m)
    {
        printf("%d", item.second);
    }
    return 0;
}