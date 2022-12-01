#include "bigint.h"

std::vector<std::string> toBin(BigInt &number)
{
    std::vector<std::string> output;
    std::string result = "";

    while (number > BigInt(0))
    {
        result += (number % BigInt(2)).operator std::string();
        number /= BigInt(2);
    }

    if (result.length() % BIT_SIZE != 0)
    {
        int extraZerosCount = BIT_SIZE - (result.length() % BIT_SIZE);
        for (int i = 0; i < extraZerosCount; i++)
        {
            result += "0";
        }
    }

    reverse(result.begin(), result.end());

    for (int i = 0; i < result.length() / BIT_SIZE; i++)
    {
        output.push_back(result.substr(BIT_SIZE * i, BIT_SIZE));
    }

    return output;
}

BigInt toDec(std::vector<std::string> &number)
{
    BigInt result = 0;
    int factor = 1;

    for (int i = (int)number.size() - 1; i >= 0; i--)
    {
        for (int j = BIT_SIZE - 1; j >= 0; j--)
        {
            result += BigInt((number[i][j] - '0') * factor);
            factor *= BASE;
        }
    }
    return result;
}

void addZeroByte(std::vector<std::string> &result, int count)
{
    reverse(result.begin(), result.end());

    for (int i = 0; i < count; i++)
    {
        result.push_back(00000000);
    }
}

BigInt operatorAnd(BigInt &first, BigInt &second)
{
    std::vector<std::string> strFirst = toBin(first);
    std::vector<std::string> strSecond = toBin(second);
    std::vector<std::string> result;

    int minSize = std::min((int)strFirst.size(), (int)strSecond.size());
    int indexFirst = 0;
    int indexSecond = 0;

    for (int i = 0; i < minSize; i++)
    {
        std::string temp = "";
        for (int j = 0; j < BIT_SIZE; j++)
        {
            if (strFirst[indexFirst][j] != strSecond[indexSecond][j])
            {
                temp += "0";
            }
            else if (strFirst[indexFirst][j] == '1')
            {
                temp += "1";
            }
            else
            {
                temp += "0";
            }
        }
        indexFirst++;
        indexSecond++;

        result.push_back(temp);
    }
    return toDec(result);
}

BigInt operatorOr(BigInt &numberA, BigInt &numberB)
{
    std::vector<std::string> strFirst = toBin(numberA);
    std::vector<std::string> strSecond = toBin(numberB);
    std::vector<std::string> result;

    int maxSize = std::max((int)strFirst.size(), (int)strSecond.size());
    int indexA = 0;
    int indexB = 0;

    if (strFirst.size() != maxSize)
    {
        int count = maxSize - (int)strFirst.size();
        addZeroByte(strFirst, count);
    }
    else
    {
        int count = maxSize - (int)strSecond.size();
        addZeroByte(strSecond, count);
    }

    for (int i = 0; i < maxSize; i++)
    {
        std::string temp = "";
        for (int j = 0; j < BIT_SIZE; j++)
        {
            if (strFirst[indexA][j] != strSecond[indexB][j])
                temp += "1";

            else if (strFirst[indexA][j] == '0')
                temp += "0";

            else
                temp += "1";
        }

        indexA++;
        indexB++;

        result.push_back(temp);
    }

    return toDec(result);
}

bool isDigit(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] > '9' || str[i] < '0')
        {
            return false;
        }
    }
    return true;
}

void BigInt ::setSign(int number)
{
    if (number >= 0)
    {
        this->sign = false;
    }
    else
    {
        this->sign = true;
    }
}

bool BigInt ::getSign()
{
    return this->sign;
}

void BigInt::setNumber(int number)
{
    BigInt tmp(number);
    this->data = tmp.data;
    this->sign = tmp.sign;
}

void BigInt::setNumber(std::string str)
{
    BigInt tmp(str);
    this->data = tmp.data;
    this->sign = tmp.sign;
}

void BigInt::setNumber(std::vector<int> digits)
{
    this->data = digits;
}

BigInt ::BigInt()
{
    this->sign = false;
}

BigInt ::BigInt(int number)
{
    this->setSign(number);

    number = abs(number);

    if (number == 0)
    {
        data.push_back(number);
    }
    while (number > 0)
    {
        data.push_back(number % MAX_NUMBER);
        number /= MAX_NUMBER;
    }
}

BigInt ::BigInt(std::string str)
{
    this->sign = false;

    if (str[0] == '-')
    {
        this->sign = true;
        str.erase(0, 1);
    }
    if (!isDigit(str))
    {
        throw std::logic_error("invalid_argument");
    }

    reverse(str.begin(), str.end());

    int size = ((int)str.size() + MAX_NUMBER_LENGTH - 1) / MAX_NUMBER_LENGTH;
    for (int i = 0; i < size; i++)
    {
        std::string temp = str.substr(0, std::min(MAX_NUMBER_LENGTH, (int)str.size()));
        reverse(temp.begin(), temp.end());
        data.push_back(std::stoi(temp));
        str.erase(0, std::min(9, (int)str.size()));
    }
}

BigInt ::BigInt(const BigInt &other)
{
    this->data = other.data;
    this->sign = other.sign;
}

BigInt ::~BigInt()
{
    this->data.clear();
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->sign = other.sign;
    this->data.clear();
    for (size_t i = 0; i < other.data.size(); i++)
    {
        this->data.push_back(other.data[i]);
    }
    return *this;
}

BigInt BigInt::operator~() const
{
    BigInt thisCopy = *this;
    std::vector<std::string> str = toBin(thisCopy);
    std::vector<std::string> part;

    for (int i = 0; i < str.size(); i++)
    {
        std::string temp = "";

        for (int j = 0; j < BIT_SIZE; j++)
        {
            str[i][j] == '1' ? temp += "0" : temp += "1";
        }
        part.push_back(temp);
    }

    BigInt temp = toDec(part);

    if (this->sign == false)
    {
        temp.setSign(1);
    }
    else
    {
        temp.setSign(-1);
    }

    return temp;
}

BigInt& BigInt::operator++()
{
    *this += 1;
    return *this;
}

const BigInt BigInt::operator++(int)
{
    BigInt tempValue = *this;
    ++(*this);
    return tempValue;
}

BigInt& BigInt::operator--()
{
    *this -= 1;
    return *this;
}

const BigInt BigInt::operator--(int)
{
    BigInt tempValue = *this;
    --(*this);
    return tempValue;
}

BigInt &BigInt::operator+=(const BigInt &other)
{
    if (!this->sign && other.sign)
    {
        BigInt temp = other;
        temp.sign = false;

        *this -= temp;
        return *this;
    }

    if (this->sign && !other.sign)
    {

        BigInt temp = other;
        temp.sign = !other.sign;

        *this -= temp;

        return *this;
    }

    std::vector<int> firstDigit = this->data;
    std::vector<int> secondDigit = other.data;

    std::vector<int> result;

    bool carry = false;

    for (int i = 0; i < std::min(firstDigit.size(), secondDigit.size()); i++)
    {
        if (carry)
        {
            firstDigit[i] += 1;
            carry = false;
        }

        int temp = firstDigit[i] + secondDigit[i];
        result.push_back(temp % MAX_NUMBER);

        if (temp >= MAX_NUMBER)
        {
            carry = true;
        }
    }

    BigInt maxBigInt;
    if (*this > other)
    {
        maxBigInt = *this;
    }
    else
    {
        maxBigInt = other;
    }

    for (int i = std::min(firstDigit.size(), secondDigit.size()); i < std::max(firstDigit.size(), secondDigit.size()); i++)
    {
        if (carry)
        {
            maxBigInt.data[i] += 1;

            if (maxBigInt.data[i] < MAX_NUMBER)
            {
                carry = false;
            }
        }

        result.push_back(maxBigInt.data[i] % MAX_NUMBER);
    }

    this->data = result;
    return *this;
}

void addExtraZeros(std::string &number, int n)
{
    for (int i = 0; i < n; i++)
    {
        number += "0";
    }
}

int getFactorValue(int index, std::string strDigit)
{
    std::reverse(strDigit.begin(), strDigit.end());
    addExtraZeros(strDigit, MAX_NUMBER_LENGTH - strDigit.length());
    std::reverse(strDigit.begin(), strDigit.end());

    return strDigit[index] - '0';
}

void deleteExtraZeros(BigInt &result)
{
    std::string temp = result.operator std::string();
    if (result != BigInt(0))
    {
        while (temp[0] == '0')
        {
            temp.erase(0, 1);
        }
    }

    result.setNumber(temp);
}

BigInt &BigInt::operator*=(const BigInt &other)
{
    BigInt result(0);
    int realIndex = -1;

    for (int i = 0; i < other.data.size(); i++)
    {
        for (int j = MAX_NUMBER_LENGTH - 1; j >= 0; j--)
        {
            if (i == other.data.size() - 1)
            {
                if (MAX_NUMBER_LENGTH - (std::to_string(other.data[i])).length() - 1 == j)
                {
                    break;
                }
            }

            int factor = getFactorValue(j, std::to_string(other.data[i]));
            int carry = 0;
            realIndex++;

            std::string temp = "";

            for (int part = 0; part < this->data.size(); part++)
            {
                std::string currentDigit = std::to_string(this->data[part]);
                for (int index = MAX_NUMBER_LENGTH - 1; index >= 0; index--)
                {
                    int factor2 = getFactorValue(index, currentDigit);
                    temp += std::to_string((factor * factor2 + carry) % 10);
                    carry = (factor * factor2 + carry) / 10;
                }
            }

            if (carry != 0)
            {
                temp += std::to_string(carry);
            }

            std::reverse(temp.begin(), temp.end());
            addExtraZeros(temp, realIndex);
            result += BigInt(temp);
        }
    }

    deleteExtraZeros(result);

    if (this->sign != other.sign)
    {
        result.setSign(-1);
    }

    else
    {
        result.setSign(true);
    }

    *this = result;
    return *this;
}

BigInt &BigInt::operator-=(const BigInt &other)
{
    if (!this->sign && other.sign)
    {
        BigInt temp = other;
        temp.sign = false;

        *this += temp;
        return *this;
    }

    if (this->sign && !other.sign)
    {
        BigInt temp = other;
        temp.sign = true;

        *this += temp;
        return *this;
    }

    std::vector<int> reduced = this->data;
    std::vector<int> subtracted = other.data;
    std::vector<int> result;

    if (*this < other)
    {
        this->sign = true;
        reduced = other.data;
        subtracted = this->data;
    }

    bool carry = false;
    for (int i = 0; i < subtracted.size(); i++)
    {
        if (carry)
        {
            reduced[i] -= 1;
            carry = false;
        }

        if (reduced[i] < subtracted[i])
        {
            carry = true;
            reduced[i] += MAX_NUMBER;
        }

        result.push_back(reduced[i] - subtracted[i]);
    }

    for (int i = subtracted.size(); i < reduced.size(); i++)
    {
        if (carry)
        {
            if ((i == reduced.size() - 1) && reduced[i] == 1)
                break;

            if (reduced[i] > 0)
            {
                reduced[i] -= 1;
                carry = false;
            }
            else
            {
                reduced[i] = MAX_NUMBER - 1;
            }
        }

        result.push_back(reduced[i]);
    }
    this->data = result;
    
    return *this;
}

int getFactor(BigInt first, BigInt second)
{
    int factor = 0;

    for (int i = 1; i <= 10; i++)
    {
        BigInt subtractible = BigInt(second * BigInt(i));
        if (subtractible > first)
        {
            break;
        }

        factor = i;
    }

    return factor;
}

BigInt &BigInt::operator/=(const BigInt &other)
{
    if (other == BigInt(0))
        throw std::logic_error("division by zero");

    std::string firstDigit = this->operator std::string();
    std::string secondDigit = other.operator std::string();
    std::string result = "";

    BigInt divider = other;
    BigInt divisible = *this;
    divisible.setSign(false);

    if (divisible < divider)
    {
        this->setNumber(0);
        return *this;
    }

    divider.setSign(1);

    BigInt currentDecreasing = BigInt(firstDigit.substr(0, secondDigit.length()));

    int factor = 0;
    int index = 0;
    while (secondDigit.length() + index <= firstDigit.length())
    {
        if (divider > currentDecreasing)
        {
            if (index != 0)
            {
                result += "0";
            }

            std::string str1(1, firstDigit[secondDigit.length() + index]);

            currentDecreasing = currentDecreasing * BigInt(10) + BigInt(str1);
            index++;
        }

        factor = getFactor(currentDecreasing, divider);
        result += std::to_string(factor);

        if (secondDigit.length() + index >= firstDigit.length())
        {
            break;
        }

        std::string str(1, firstDigit[secondDigit.length() + index]);

        if (isDigit(str))
        {
            currentDecreasing = (currentDecreasing - divider * BigInt(factor)) * BigInt(10) + BigInt(str);
        }

        index++;
    }

    bool firstSign = this->sign;
    this->setNumber(result);

    if (firstSign != other.sign)
    {
        this->setSign(-1);
    }

    else
    {
        this->setSign(false);
    }

    return *this;
}

BigInt &BigInt::operator^=(const BigInt &other)
{
    BigInt thisCopy = *this;
    BigInt result = *this;

    for (BigInt temp = other - BigInt(1); temp > BigInt(0); temp--)
    {
        result *= thisCopy;
    }

    *this = result;
    return *this;
}


BigInt &BigInt::operator%=(const BigInt &other)
{
    if (*this < other)
    {
        return *this;
    }

    BigInt temp = (*this) / other;
    BigInt result = (*this) - other * temp;

    this->setNumber(result.data);
    return *this;
}

BigInt &BigInt::operator&=(const BigInt &other)
{
    BigInt number1 = *this;
    BigInt number2 = other;
    BigInt temp = operatorAnd(number1, number2);

    this->data = temp.data;

    return *this;
}

BigInt &BigInt::operator|=(const BigInt &other)
{
    BigInt number1 = *this;
    BigInt number2 = other;

    BigInt temp = operatorOr(number1, number2);

    this->data = temp.data;
    
    return *this;
}


BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    /*if (*this == 0)
    {
        return *this;
    }*/

    BigInt temp = *this;
    temp.sign = !temp.sign;
    return temp;
}

bool BigInt::operator==(const BigInt &other) const
{
    if (this->size() != other.size() || this->sign != other.sign)
    {
        return false;
    }

    for (size_t i = 0; i < this->data.size(); i++)
    {
        if (this->data[i] != other.data[i])
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}

bool BigInt::operator<(const BigInt &other) const
{
    if (*this == other)
    {
        return false;
    }

    if (this->sign != other.sign)
    {
        return this->sign == true;
    }

    return (this->data == min(this->data, other.data) && this->sign == false);
}

bool BigInt::operator>(const BigInt &other) const
{
    return (other < *this && *this != other);
}

bool BigInt::operator<=(const BigInt &other) const
{
    return (*this < other || *this == other);
}

bool BigInt::operator>=(const BigInt &other) const
{
    return (*this > other || *this == other);
}

std::string BigInt::getString() const
{
    std::string result = "";

    if (this->sign == true)
    {
        result += '-';
    }

    result += this->operator std::string();
    return result;
}

BigInt::operator int() const
{
    if (*this < BigInt(INT_MIN) || *this > BigInt(INT_MAX))
    {
        throw std::logic_error("int overflow");
    }

    else
    {
        return std::stoi(this->getString());
    }
}

std::string PrintPartNumber(int number)
{
    std::string result = "";
    if (number >= MAX_NUMBER / 10)
    {
        result += std::to_string(number);
    }

    else
    {
        int countExtraZeros = MAX_NUMBER_LENGTH - (std::to_string(number)).size();
        for (int i = 0; i < countExtraZeros; i++)
        {
            result += "0";
        }

        result += std::to_string(number);
    }

    return result;
}

BigInt::operator std::string() const
{
    std::string result = "";

    for (int i = this->data.size() - 1; i >= 0; i--)
    {
        if (i == this->data.size() - 1)
        {
            result += std::to_string(this->data[i]);
        }
        else
        {
            result += PrintPartNumber(this->data[i]);
        }
    }

    return result;
}

BigInt operator+(const BigInt &first, const BigInt &second)
{
    BigInt temp = first;
    temp += second;
    return temp;
}

BigInt operator-(const BigInt &first, const BigInt &second)
{
    BigInt temp = first;
    temp -= second;
    return temp;
}

BigInt operator*(const BigInt &first, const BigInt &second)
{
    BigInt temp = first;
    temp *= second;
    return temp;
}

BigInt operator/(const BigInt &first, const BigInt &second)
{
    BigInt temp = first;
    temp /= second;
    return temp;
}

BigInt operator^(const BigInt &first, const BigInt &second)
{
    BigInt temp = first;
    temp ^= second;
    return temp;
}

BigInt operator%(const BigInt &first, const BigInt &second)
{
    BigInt temp = first;
    temp %= second;
    return temp;
}

BigInt operator&(const BigInt &first, const BigInt &second)
{
    BigInt numberA = first;
    BigInt numberB = second;

    BigInt temp = operatorAnd(numberA, numberB);

    return temp;
}

BigInt operator|(const BigInt &first, const BigInt &second)
{
    BigInt numberA = first;
    BigInt numberB = second;

    BigInt temp = operatorOr(numberA, numberB);

    return temp;
}

std::ostream &operator<<(std::ostream &out, const BigInt &i)
{
    BigInt temp = i;
    if (temp.getSign() == 1)
    {
        out << "-";
    }

    deleteExtraZeros(temp);

    std::string result = temp.operator std::string();
    out << result;

    return out;
}

size_t BigInt::size() const
{
    return data.size();
}
