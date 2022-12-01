#ifndef bigint_h
#define bigint_h

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define BIT_SIZE 8
#define BASE 2
#define MAX_NUMBER 1000000000
#define MAX_NUMBER_LENGTH 9

class BigInt
{
public:
    void SetSign(int number);
    bool GetSign();
    void SetNumber(int number);
    void SetNumber(std::string str);
    void SetNumber(std::vector<int> digits);

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
    std::string GetString() const;

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

#endif /* Header_h */
