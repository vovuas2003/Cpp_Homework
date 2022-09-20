#pragma once
/*
    Класс Number -- класс положительных больших чисел
    Большое число будет храниться в динамическом массиве data
    Каждый элемент этого массива содержит разряд числа в 100-ричной системе счисления
    (так как base = 100)
    По сути, каждый элемент data хранит две цифры числа в десятичной записи
    Значение 100 для системы счисления выбрано как компромис между
    эффективностью и удобством написания программы.
    Если выбрать значения базы 10 - то программа будет не так эффективна по памяти
    Если выбрать значения базы 256 (максимально эффективное использование памяти для типа char),
    то алгоритм печати на экран сильно усложнится
    В качестве альтернативы, можно было выбрать базу 1e9, 
    изменив при этом тип элементов c char на int
    capacity - размер массива data
    size - сколько ячеек занимет число в массиве data
    size <= capacity
    Для удобства разряды числа хранятся в обратном порядке
    Например, число 12345678 соответствует массиву
    data = {78, 56, 34, 12}
    (это упрощает многие алгоритмы с такими числами)
*/

class Number {
  private:
    static const int base = 100;
     std::size_t size;
     std::size_t capacity;
    char *data;

  public:

     Number(int a);
     Number();
    // Конструктор копирования
     Number(const Number & n);
     Number(const char *str);
    ~Number();
     Number & operator=(const Number & right);

    Number operator+(Number a);
    void operator+=(const Number & a);

    bool isEven() const;

    Number operator*(const Number & right) const;
    void operator*=(const Number & a);

    bool operator==(const Number & a) const;
    bool operator!=(const Number & a) const;
    bool operator>(const Number & a) const;
    bool operator<(const Number & a) const;
    void div2();

    friend std::ostream & operator<<(std::ostream & stream, const Number & right);
};

std::ostream & operator<<(std::ostream & stream, const Number & right);
