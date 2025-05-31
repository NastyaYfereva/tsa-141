#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
 * @brief Считывает целое число с клавиатуры с проверкой корректности ввода.
 * @return Возвращает считанное целое число.
 * @note Прерывает программу при ошибке ввода.
 */
int getValue();

/**
 * @brief Считывает вещественное число с клавиатуры с проверкой корректности ввода.
 * @return Возвращает считанное вещественное число.
 * @note Прерывает программу при ошибке ввода.
 */
double getDouble();

/**
 * @brief Проверяет, что значение n удовлетворяет условию n >= 1.
 * @param n Проверяемое целое число.
 * @note Прерывает программу, если условие не выполняется.
 */
void checkN(const int n);

/**
 * @brief Вычисляет сумму первых n членов ряда с использованием рекуррентного соотношения.
 * @param n Количество членов ряда для суммирования.
 * @return Сумма первых n членов ряда.
 * @note Ряд: (-1)^k * k / ( (k!)^2 + (k+1)! )
 */
double sumN(const int n);

/**
 * @brief Проверяет, что значение e удовлетворяет условию e > 0.
 * @param e Проверяемое вещественное число.
 * @note Прерывает программу, если условие не выполняется.
 */
void checkE(const double e);

/**
 * @brief Вычисляет сумму членов ряда, пока их модуль превышает заданную точность e.
 * @param e Точность вычисления (положительное вещественное число).
 * @return Сумма членов ряда, удовлетворяющих условию |a_k| > e.
 * @note Использует рекуррентное соотношение для оптимизации вычислений.
 */
double sumE(const double e);

/**
 * @brief Точка входа в программу.
 * @return 0, если программа выполнена успешно.
 * @note Запрашивает у пользователя количество членов ряда и точность,
 *       затем выводит результаты вычислений.
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите число членов ряда для рассчета суммы: ";
    int n = getValue();
    checkN(n);
    cout << "Сумма " << n << " членов ряда равна " << sumN(n) << endl;

    cout << "Введите точность вычисления (e > 0): ";
    double e = getDouble();
    checkE(e);
    cout << "Сумма членов ряда с точностью " << e << " равна " << sumE(e) << endl;

    return 0;
}

// Реализации функций:

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода: требуется целое число." << endl;
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
        cout << "Ошибка ввода: требуется вещественное число." << endl;
        abort();
    }
    return value;
}

void checkN(const int n)
{
    if (n < 1)
    {
        cout << "Ошибка: количество членов ряда должно быть >= 1." << endl;
        abort();
    }
}

double sumN(const int n)
{
    double result = 0.0;
    double k_fact = 1.0;       // Текущее значение k!
    double k_plus_1_fact = 1.0; // Текущее значение (k+1)!
    int sign = -1;             // Знак текущего члена ряда: (-1)^k

    for (int k = 1; k <= n; ++k)
    {
        // Обновление факториалов:
        k_fact *= k;
        k_plus_1_fact = k_fact * (k + 1);

        // Вычисление текущего члена ряда:
        double term = sign * k / (k_fact * k_fact + k_plus_1_fact);
        result += term;

        // Подготовка к следующей итерации:
        sign *= -1;
    }
    return result;
}

void checkE(const double e)
{
    if (e <= 0.0)
    {
        cout << "Ошибка: точность вычисления должна быть > 0." << endl;
        abort();
    }
}

double sumE(const double e)
{
    double result = 0.0;
    double k_fact = 1.0;       // Текущее значение k!
    double k_plus_1_fact = 1.0; // Текущее значение (k+1)!
    int sign = -1;             // Знак текущего члена ряда: (-1)^k
    int k = 1;

    while (true)
    {
        // Обновление факториалов:
        k_fact *= k;
        k_plus_1_fact = k_fact * (k + 1);

        // Вычисление текущего члена ряда:
        double term = sign * k / (k_fact * k_fact + k_plus_1_fact);

        // Проверка условия выхода:
        if (abs(term) <= e)
            break;

        result += term;

        // Подготовка к следующей итерации:
        sign *= -1;
        ++k;
    }
    return result;
}
