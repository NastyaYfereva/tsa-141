#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
 * @brief считывает целое число с клавиатуры с проверкой ввода
 * @return считанное значение
 */
int getValue();

/**
 * @brief считывает вещественное число с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getDouble();

/**
 * @brief проверяет, что введенное значение удовлетворяет условию n >= 1
 * @param n считанное значение
 */
void checkN(const int n);

/**
 * @brief Рассчитывает сумму n первых членов ряда
 * @param n заданное число членов
 * @return сумму n первых членов ряда
 */
double sumN(const int n);

/**
 * @brief проверяет, что введенное значение удовлетворяет условию e > 0
 * @param e считанное значение
 */
void checkE(const double e);

/**
 * @brief Рассчитывает сумму первых членов ряда, не превышающих по модулю e
 * @param e заданная точность
 * @return сумму первых членов ряда, не превышающих по модулю e
 */
double sumE(const double e);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите число членов ряда для рассчета последовательности: ";
    int n = getValue();
    checkN(n);
    cout << "Сумма " << n << " членов ряда равна " << sumN(n) << endl;

    cout << "Введите погрешность для рассчета последовательности: ";
    double e = getDouble();
    checkE(e);
    cout << "Сумма членов ряда с точностью e равна " << sumE(e) << endl;

    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

double getDouble()
{
    double value = 0.0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

void checkN(const int n)
{
    if (n < 1)
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
}

double sumN(const int n)
{
    double result = 0.0;
    double k_fact = 1.0;      // k! (начинаем с 1! = 1)
    double k_plus_1_fact = 1.0; // (k+1)! (начинаем с 2! = 2, но инициализируем 1! = 1)

    for (int k = 1; k <= n; ++k)
    {
        // Обновляем факториалы:
        // k! = (k-1)! * k
        // (k+1)! = k! * (k+1)
        k_fact *= k;
        if (k >= 2)
            k_plus_1_fact = k_fact * (k + 1);
        else
            k_plus_1_fact = 2.0; // Для k=1: (1+1)! = 2! = 2

        // Вычисляем текущий член ряда: (-1)^k * k / ( (k!)^2 + (k+1)! )
        double denominator = k_fact * k_fact + k_plus_1_fact;
        double term = pow(-1, k) * k / denominator;

        result += term;
    }
    return result;
}

void checkE(const double e)
{
    if (!(e > 0))
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
}

double sumE(const double e)
{
    double result = 0.0;
    double k_fact = 1.0;      // k! (начинаем с 1! = 1)
    double k_plus_1_fact = 1.0; // (k+1)! (начинаем с 2! = 2, но инициализируем 1! = 1)

    int k = 1;
    while (true)
    {
        // Обновляем факториалы:
        k_fact *= k;
        if (k >= 2)
            k_plus_1_fact = k_fact * (k + 1);
        else
            k_plus_1_fact = 2.0; // Для k=1: (1+1)! = 2! = 2

        // Вычисляем текущий член ряда: (-1)^k * k / ( (k!)^2 + (k+1)! )
        double denominator = k_fact * k_fact + k_plus_1_fact;
        double term = pow(-1, k) * k / denominator;

        if (abs(term) <= e)
            break;

        result += term;
        ++k;
    }
    return result;
}