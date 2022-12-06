#ifndef bigint_h
#define bigint_h

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

const int BIT_SIZE = 8;
const int BASE = 2;
const int MAX_NUMBER = 1000000000;
const int MAX_NUMBER_LENGTH = 9;

const char ONE_SIGN = '1';
const char ZERO_SIGN = '0';
//const char* ONE_LINE = "1";
//const char* ZERO_LINE = "1";

class BigInt
{
public:
    void setSign(int number);
    bool getSign();
    void setNumber(int number);
    void setNumber(std::string str);
    void setNumber(std::vector<int> digits);

    BigInt();
    BigInt(int number);
    BigInt(std::string str);
    BigInt(const BigInt &other);
    ~BigInt();

    BigInt& operator=(const BigInt &other);

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;

    operator int() const;
    operator std::string() const;
    std::string getString() const;

    size_t size() const;
private:
    std::vector<int> data;
    bool sign;
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream &operator<<(std::ostream &out, const BigInt &i);

#endif