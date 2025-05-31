#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
 * @brief Считывает значения с клавиатуры с проверкой ввода
 * @return возвращает значение, если оно правильное, иначе завершает программу
 */
double getValue();

/**
 * @brief Функция для вычисления значения функции y = ln(1/(2x + x²))
 * @param x - аргумент функции
 * @return значение функции
 * @throws runtime_error если вычисление невозможно
 */
double calculateFunction(const double x);

/**
 * @brief Функция для проверки, что шаг положительный
 * @return шаг
 */
double getPositiveStep();

/**
 * @brief Точка входа в программу
 * @return 0 в случае успешного выполнения, 1 при ошибке
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Табулирование функции y = ln(1/(2x + x²))" << endl;
    cout << "Введите начальное значение x: ";
    double startX = getValue();
    
    cout << "Введите конечное значение x: ";
    double endX = getValue();
    
    double step = getPositiveStep();

    cout << "\nРезультаты табулирования:" << endl;
    cout << "x\t|\ty" << endl;
    cout << "-----------------------" << endl;

    for (double x = startX; x <= endX + numeric_limits<double>::epsilon(); x += step)
    {
        try {
            double y = calculateFunction(x);
            cout << x << "\t|\t" << y << endl;
        } 
        catch (const runtime_error& e) {
            cout << x << "\t|\t" << "Ошибка: " << e.what() << endl;
        }
    }

    return 0;
}

double getValue()
{
    double value = 0.0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Некорректное значение" << endl;
        exit(1);
    }
    return value;
}

double calculateFunction(const double x)
{
    double denominator = 2 * x + pow(x, 2);
    if (denominator >= 0 || abs(denominator) < numeric_limits<double>::epsilon()) {
        throw runtime_error("выражение (2x + x²) должно быть строго положительным");
    }
    return log(1.0 / denominator);
}

double getPositiveStep()
{
    double step = 0.0;
    cout << "Введите шаг: ";
    step = getValue();
    if (step <= 0)
    {
        cout << "Ошибка. Шаг должен быть положительным." << endl;
        exit(1);
    }
    return step;
}
