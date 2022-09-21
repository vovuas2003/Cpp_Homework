#include <iostream>
#include <iomanip>
#include <cstring>
#include "number.h"
#include <cstdio>
#include <cstdlib>

Number::Number(int a)
{
    // Находим размер необходимой памяти под это число
    int temp = a;
    capacity = 0;
    while (temp != 0) {
	temp /= base;
	capacity += 1;
    }

    // Отдельно обрабатываем случай, когда число равно 0
    if (capacity == 0)
	capacity = 1;

    // Выделяем память и записывем число a в массив data
    // Например, число 12345678 представится в виде массива [78, 56, 34, 12]
    data = new char[capacity];

    for (int i = 0; i < capacity; ++i) {
	data[i] = a % base;
	a /= base;
    }

    // В данном случае размер будет равен вместимости
    size = capacity;
}

// Конструктор по умолчанию      
Number::Number():Number(0){}

// Конструктор копирования
Number::Number(const Number & n)
{
    size = n.size;
    capacity = n.capacity;
    data = new char[capacity];
    for (int i = 0; i < size; i++) {
	data[i] = n.data[i];
    }
}

Number::Number(const char *str)
{
    int len = std::strlen(str);
    size = (len + len % 2) / 2;
    capacity = size;
    data = new char[capacity];
    char buf[2];
    for (int i = 0; i < size; i++) {
	buf[1] = str[len - 2 * i - 1];
	if (len - 2 * i - 1 > 0) {
	    buf[0] = str[len - 2 * i - 2];
	} else {
	    buf[0] = '0';
	}
	sscanf(buf, "%d", &data[i]);
    }
}

Number::~Number()
{
    delete[]data;
}

Number & Number::operator=(const Number & right)
{
    capacity = right.capacity;
    size = right.size;
    data = new char[capacity];
    for (int i = 0; i < size; i++) {
	data[i] = right.data[i];
    }
    return *this;
}

Number Number::operator+(Number a)
{
    Number result;
    Number temp;
    int i;
    int carry = 0;
    if (size < a.size) {
	temp = *this;
	*this = a;
	a = temp;
    }
    result.capacity = size + 1;
    result.data = (char *) calloc(result.capacity, sizeof(char));
    for (i = 0; i < a.size; ++i) {
	result.data[i] = (data[i] + a.data[i] + carry) % base;
	carry = (data[i] + a.data[i] + carry) / base;
    }
    for (; i < size; ++i) {
	result.data[i] = (data[i] + carry) % base;
	carry = (data[i] + carry) / base;
    }
    if (carry) {
	result.data[i] = carry;
	result.size = size + 1;
    } else {
	result.size = size;
    }
    return result;
}

void Number::operator+=(const Number & a)
{
    *this = *this + a;
}

bool Number::isEven() const
{
    if (data[0] % 2) {
	return false;
    }
    return true;
}

Number Number::operator*(const Number & right) const
{
    int i, j, temp;
    Number result;
    result.capacity = capacity + right.capacity;
    int *carry = (int *) calloc(result.capacity, sizeof(int));
    result.data = (char *) calloc(result.capacity, sizeof(char));
    for (i = 0; i < size; ++i) {
	for (j = 0; j < right.size; ++j) {
	    temp = (result.data[i + j] + data[i] * right.data[j] + carry[i + j]);
	    result.data[i + j] = temp % base;
	    carry[i + j + 1] += temp / base;
	    carry[i + j] = 0;
	}
    }
    if (carry[i + j - 1]) {
	result.data[i + j - 1] = carry[i + j - 1];
	result.size = i + j;
    } else {
	result.size = i + j - 1;
    }
    free(carry);
    return result;
}

void Number::operator*=(const Number & a)
{
    *this = *this * a;
}

bool Number::operator==(const Number & a) const
{
    if (size != a.size) {
	return false;
    }
    for (int i = 0; i < size; ++i) {
	if (data[i] != a.data[i]) {
	    return false;
	}
    }
    return true;
}

bool Number::operator!=(const Number & a) const
{
    return not(*this == a);
}

bool Number::operator>(const Number & a) const
{
    if (size > a.size) {
	return true;
    }
    if (size < a.size) {
	return false;
    }
    for (int i = size - 1; i >= 0; --i) {
	if (data[i] > a.data[i]) {
	    return true;
	}
	if (data[i] < a.data[i]) {
	    return false;
	}

    }
    return false;
}

bool Number::operator<(const Number & a) const
{
    return not(*this > a) and(*this != a);
}

void Number::div2()
{
    int carry = 0;
    int temp;
    for (int i = size - 1; i >= 0; --i) {
	temp = data[i] + carry * base;
	data[i] = temp / 2;
	carry = temp % 2;
    }
    if (data[size - 1] == 0) {
	size -= 1;
    }
}


std::ostream & operator<<(std::ostream & stream, const Number & right)
{

    // Печатаем самый большой разряд
    stream << (int) right.data[right.size - 1];

    // Печатаем остальные разряды с заполнением нулями до 2-х цифр
    // setfill и setw это то же самое, что и в языке C спецификатор %02d
    for (std::size_t i = 0; i < right.size - 1; ++i)
	stream << std::setfill('0') << std::setw(2) << (int) right.
	    data[right.size - 2 - i];
    return stream;
}